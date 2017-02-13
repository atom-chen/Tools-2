#include "Gut.h"
#include "GutModel_DX9.h"
#include "render_data.h"

LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DSURFACE9 g_pDepthStencil = NULL;

LPDIRECT3DTEXTURE9 g_pBlurTextures[2];

Matrix4x4 g_projection_matrix;

const int g_framebuffer_w = 256;
const int g_framebuffer_h = 256;

static CGutModel_DX9 g_Models_DX9[4];

bool InitResourceDX9(void)
{
	// 获得Direct3D 9设备
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// 设置视角转换矩阵
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// 关闭光照
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 改变三角形正面的法线
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CGutModel::SetTexturePath("../../textures/");

	for ( int i=0; i<3; i++ )
	{
		g_Models_DX9[i].ConvertToDX9Model(&g_Models[i]);
	}

	{
		// source
		device->CreateTexture(g_framebuffer_w, g_framebuffer_h, 1, 
			D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, 
			D3DPOOL_DEFAULT, &g_pTexture, NULL);

		device->CreateDepthStencilSurface(g_framebuffer_w, g_framebuffer_h, 
			D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, 
			FALSE, &g_pDepthStencil, NULL);
	}

	{
		// blur effect workspace
		device->CreateTexture(g_framebuffer_w, g_framebuffer_h, 1, 
			D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, 
			D3DPOOL_DEFAULT, &g_pBlurTextures[0], NULL);

		device->CreateTexture(g_framebuffer_w, g_framebuffer_h, 1, 
			D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, 
			D3DPOOL_DEFAULT, &g_pBlurTextures[1], NULL);
	}

	device->SetSamplerState(0,  D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0,  D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0,  D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	device->SetSamplerState(0,  D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	device->SetSamplerState(0,  D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	return true;
}

bool ReleaseResourceDX9(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pDepthStencil);

	for ( int i=0; i<3; i++ )
	{
		g_Models_DX9[i].Release();
	}
	
	SAFE_RELEASE(g_pBlurTextures[0]);
	SAFE_RELEASE(g_pBlurTextures[1]);

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// Reset Device
	GutResetGraphicsDeviceDX9();
	// 获得Direct3D 9设备
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// 投影矩阵, 重设水平和垂直方向的视角.
	float aspect = (float) height / (float) width;
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// 关闭光照
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 改变三角形正面的法线
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

// Direct3D 7x7 blur
static LPDIRECT3DTEXTURE9 BlurTexture(LPDIRECT3DTEXTURE9 pSource)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	Matrix4x4 identiyMatrix = Matrix4x4::IdentityMatrix();
	// `把所有转换矩阵设置成单位矩阵`
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &identiyMatrix);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &identiyMatrix);
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &identiyMatrix);
	// `从动态贴图中取出Surface`
	LPDIRECT3DSURFACE9 pFrameBufferBackup, pDepthBufferBackup;
	device->GetRenderTarget(0, &pFrameBufferBackup); 
	pFrameBufferBackup->Release();
	device->GetDepthStencilSurface(&pDepthBufferBackup); 
	pDepthBufferBackup->Release();
	// `权重系数比, 越接近中央权重会越大.`
	float weight_table[7] = 
		{1.0f, 3.0f, 4.0f, 5.0f, 4.0f, 3.0f, 1.0f};
	// `图片的偏移量`
	float uv_offset_table[7] = 
		{-3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f, 3.0f};
	float sum = 0.0f;
	// `把权重系数对应到正确的0-1范围内`
	for ( int i=0; i<7; i++ )
	{
		sum += weight_table[i];
	}
	for ( int i=0; i<7; i++ )
	{
		weight_table[i] /= sum;
	}
	// 
	Vector4 vOneTexel_X(1.0f/(float)g_framebuffer_w, 0.0f, 0.0f, 0.0f);
	Vector4 vOneTexel_Y(0.0f, 1.0f/(float)g_framebuffer_h, 0.0f, 0.0f);
	Vertex_V3T2 temp_quad[4];

	LPDIRECT3DSURFACE9 pSurface;
	g_pBlurTextures[0]->GetSurfaceLevel(0, &pSurface); 

	device->SetRenderTarget(0, pSurface);
	device->SetDepthStencilSurface(NULL);

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	device->SetTexture(0, pSource);
	device->SetFVF(D3DFVF_XYZ|D3DFVF_TEX1); 

	// `设置颜色来源为` texture factor * texture
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// `水平方向模糊化`
	for ( int i=0; i<7; i++ )
	{
		Vector4 vOffset = uv_offset_table[i] * vOneTexel_X;

		for ( int p=0; p<4; p++ )
		{
			temp_quad[p] = g_Quad[p];
			temp_quad[p].m_Texcoord[0] += vOffset[0];
			temp_quad[p].m_Texcoord[1] += vOffset[1];
		}
		
		int weight = (int) (weight_table[i] * 255);
		device->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA(weight, weight, weight, weight));
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, temp_quad, sizeof(Vertex_V3T2));
	}
	
	pSurface->Release();

	g_pBlurTextures[1]->GetSurfaceLevel(0, &pSurface); 
	device->SetRenderTarget(0, pSurface);
	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	device->SetTexture(0, g_pBlurTextures[0]);

	// `垂直方向模糊化`
	for ( int i=0; i<7; i++ )
	{
		Vector4 vOffset = uv_offset_table[i] * vOneTexel_Y;

		for ( int p=0; p<4; p++ )
		{
			temp_quad[p] = g_Quad[p];
			temp_quad[p].m_Texcoord[0] += vOffset[0];
			temp_quad[p].m_Texcoord[1] += vOffset[1];
		}
		
		int weight = (int) (weight_table[i] * 255);
		device->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA(weight, weight, weight, weight));
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, temp_quad, sizeof(Vertex_V3T2));
	}

	pSurface->Release();

	device->SetRenderTarget(0, pFrameBufferBackup);
	device->SetDepthStencilSurface(pDepthBufferBackup);
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return g_pBlurTextures[1];
}

void RenderSolarSystemDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `投影矩阵`
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(60.0f, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// `镜头矩阵`
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	// `太阳`
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_sun_matrix);
	g_Models_DX9[0].Render();
	// `地球`
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_earth_matrix);
	g_Models_DX9[1].Render();
	// `月亮`
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_moon_matrix);
	g_Models_DX9[2].Render();
}

// `使用Direct3D9来绘图`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	LPDIRECT3DTEXTURE9 pBlurredTexture;
	// `开始下绘图指令`
	device->BeginScene(); 
	// `把太阳系的运动画到另一个render target中`
	{
		LPDIRECT3DSURFACE9 pFrameBufferBackup, pDepthBufferBackup;
		device->GetRenderTarget(0, &pFrameBufferBackup); pFrameBufferBackup->Release();
		device->GetDepthStencilSurface(&pDepthBufferBackup); pDepthBufferBackup->Release();

		LPDIRECT3DSURFACE9 pSurface;
		g_pTexture->GetSurfaceLevel(0, &pSurface); 

		device->SetRenderTarget(0, pSurface);
		device->SetDepthStencilSurface(g_pDepthStencil);

		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(50, 50, 50, 0), 1.0f, 0);

		RenderSolarSystemDX9();

		pSurface->Release();
		device->SetRenderTarget(0, pFrameBufferBackup);
		device->SetDepthStencilSurface(pDepthBufferBackup);
	}
	// `对贴图做模糊化处理`
	pBlurredTexture = BlurTexture(g_pTexture);
	// `把上一个步骤的结果作为贴图来使用`
	{
		// `清除画面`
		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 255, 255), 1.0f, 0);

		Matrix4x4 identMatrix = Matrix4x4::IdentityMatrix();

		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &identMatrix);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &identMatrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &identMatrix);
		
		if ( g_bBlur )
			device->SetTexture(0, pBlurredTexture);
		else
			device->SetTexture(0, g_pTexture);

		// `设置颜色来源为` texture factor * texture
		device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		// `画出矩形`
		device->SetFVF(D3DFVF_XYZ|D3DFVF_TEX1); 
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_V3T2));
	}
	// `声明所有的绘图指令都下完了`
	device->EndScene(); 
	// `把背景backbuffer的画面显示出来`
    device->Present( NULL, NULL, NULL, NULL );
}
