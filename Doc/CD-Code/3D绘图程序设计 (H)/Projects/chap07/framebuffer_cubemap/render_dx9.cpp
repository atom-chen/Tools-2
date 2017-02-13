#include "Gut.h"
#include "GutModel_DX9.h"
#include "render_data.h"

LPDIRECT3DCUBETEXTURE9 g_pTexture = NULL;
LPDIRECT3DSURFACE9 g_pDepthStencil = NULL;

static Matrix4x4 g_projection_matrix;
static Matrix4x4 g_mirror_view_matrix;
static CGutModel_DX9 g_Models_DX9[4];

bool InitResourceDX9(void)
{
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `�����ӽ�ת������`

	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFOV, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// `�رչ���`
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// `�ı�����������ķ���`
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	device->CreateCubeTexture(512, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture, NULL);
	device->CreateDepthStencilSurface(512, 512, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &g_pDepthStencil, NULL);

	if ( g_pTexture==NULL || g_pDepthStencil==NULL )
		return false;

	CGutModel::SetTexturePath("../../textures/");

	for ( int i=0; i<4; i++ )
	{
		g_Models_DX9[i].ConvertToDX9Model(&g_Models[i]);
	}

	return true;
}

bool ReleaseResourceDX9(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pDepthStencil);

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// Reset Device
	GutResetGraphicsDeviceDX9();
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFOV, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void RenderSolarSystemDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// ����
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_earth_matrix);
	g_Models_DX9[1].Render();
	// ����
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_moon_matrix);
	g_Models_DX9[2].Render();
	// ����
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_mars_matrix);
	g_Models_DX9[3].Render();
}
// ʹ��Direct3D9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 

	// `����cubemap 6����`
	{
		// `��¼��`framebuffer
		LPDIRECT3DSURFACE9 pFrameBufferBackup, pDepthBufferBackup;
		device->GetRenderTarget(0, &pFrameBufferBackup); pFrameBufferBackup->Release();
		device->GetDepthStencilSurface(&pDepthBufferBackup); pDepthBufferBackup->Release();

		Matrix4x4 mirror_x; mirror_x.Scale_Replace(-1.0f, 1.0f, 1.0f);
		Matrix4x4 cubemap_projection_matrix = mirror_x * GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 0.1f, 100.0f);

		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &cubemap_projection_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);
		
		for ( int i=0; i<6; i++ )
		{
			// `ȡ��cubemap������һ����`
			LPDIRECT3DSURFACE9 pSurface;
			D3DCUBEMAP_FACES face = (D3DCUBEMAP_FACES) (D3DCUBEMAP_FACE_POSITIVE_X + i);
			g_pTexture->GetCubeMapSurface(face, 0, &pSurface); 
			// `�ѻ��滭��cubemap����һ����`
			device->SetRenderTarget(0, pSurface);
			device->SetDepthStencilSurface(g_pDepthStencil);
			// `�������`
			device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
			// `���¾�ͷ����`
			Matrix4x4 cubemap_view_matrix = GutMatrixLookAtRH(g_vCubemap_Eye, g_vCubemap_Lookat[i], g_vCubemap_Up[i]);
			device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &cubemap_view_matrix);
			// `������`
			RenderSolarSystemDX9();
			// `��֪d3d�豸���surfaceʹ�����, ����surface��reference count.`
			pSurface->Release();
		}

		// `��ԭ��ʹ����framebuffer`
		device->SetRenderTarget(0, pFrameBufferBackup);
		device->SetDepthStencilSurface(pDepthBufferBackup);
	}

	// `����һ������Ľ����Ϊ��ͼ��ʹ��`
	{
		// `�������`
		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
		// `ת������`
		Matrix4x4 view_matrix = g_Control.GetViewMatrix();
		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_sun_matrix);
		// `ʹ�þ���ѷ���ת������������ϵ`
		Matrix4x4 inv_view = g_Control.GetCameraMatrix();
		inv_view.NoTranslate();
		//inv_view.FastInvert();
		device->SetTransform(D3DTS_TEXTURE1, (D3DMATRIX *)&inv_view);
		// `��Model�ĵ�3����ͼǿ�ȸĳ�cubemap`
		CGutModel_DX9::SetTextureOverwrite(2, g_pTexture);
		CGutModel_DX9::SetUVMapOverwrite(2, MAP_CUBEMAP);
		// `̫��`
		g_Models_DX9[0].Render();
		// `��Model�ĵ�3����ͼ��ԭ��ģ��ԭʼ����`
		CGutModel_DX9::SetTextureOverwrite(2, NULL);
		CGutModel_DX9::SetUVMapOverwrite(2, 0xff);
		// `����`
		RenderSolarSystemDX9();
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
