#include "Gut.h"
#include "render_data.h"
#include "GutModel_DX9.h"
#include "GutWin32.h"

static int g_iFrameBufferWidth = 1024;
static int g_iFrameBufferHeight = 1024;

LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DSURFACE9 g_pFrameBuffer = NULL;
LPDIRECT3DSURFACE9 g_pDepthStencil = NULL;

LPDIRECT3DSURFACE9 g_pMainFrameBuffer = NULL;
LPDIRECT3DSURFACE9 g_pMainDepthBuffer = NULL;

void InitStateDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ʹ��trilinear
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);

	device->GetRenderTarget(0, &g_pMainFrameBuffer);
	device->GetDepthStencilSurface(&g_pMainDepthBuffer);

	int width, height;
	GutGetWindowSize(width, height);
	
	g_iFrameBufferWidth = width * 2;
	g_iFrameBufferHeight = height * 2;

	device->CreateTexture(g_iFrameBufferWidth, g_iFrameBufferHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture, NULL);
	device->CreateDepthStencilSurface(g_iFrameBufferWidth, g_iFrameBufferHeight, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &g_pDepthStencil, NULL);
	g_pTexture->GetSurfaceLevel(0, &g_pFrameBuffer);
}

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	InitStateDX9();

	return true;
}

bool ReleaseResourceDX9(void)
{
	SAFE_RELEASE(g_pFrameBuffer);
	SAFE_RELEASE(g_pMainFrameBuffer);
	SAFE_RELEASE(g_pMainDepthBuffer);

	SAFE_RELEASE(g_pDepthStencil);
	SAFE_RELEASE(g_pTexture);

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	SAFE_RELEASE(g_pFrameBuffer);
	SAFE_RELEASE(g_pMainFrameBuffer);
	SAFE_RELEASE(g_pMainDepthBuffer);

	SAFE_RELEASE(g_pDepthStencil);
	SAFE_RELEASE(g_pTexture);

	// Reset Device
	GutResetGraphicsDeviceDX9();
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	InitStateDX9();
}

static void Antialiasing_None(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->BeginScene(); 

	// `����ת������`
	Matrix4x4 ident_matrix; ident_matrix.Identity();

	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &ident_matrix);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &ident_matrix);
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);

	device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// `�������`
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_RGBA(0,0,255,255), 1.0f, 0);
	// `����3����`
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
	device->SetRenderState(D3DRS_TEXTUREFACTOR, 0xffffffff);
	device->SetFVF(D3DFVF_XYZ);
	device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, g_Triangle, sizeof(Vector4));
	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}

static void Antialiasing_MultiSampling(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `��multisampling����`
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	// `��ͼ�ķ���û��ʲô��ͬ`
	Antialiasing_None();
	// `�ر�multisampling����`
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
}

static void Antialiasing_SuperSampling(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->BeginScene(); 

	Matrix4x4 ident_matrix; ident_matrix.Identity();

	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &ident_matrix);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &ident_matrix);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// `�Ȱѻ��滭��4�����Framebuffer��`
	{
		// `���û�ͼ���Ҫ���ڶ�̬��ͼ��`
		device->SetRenderTarget(0, g_pFrameBuffer);
		device->SetDepthStencilSurface(g_pDepthStencil);
		// `�������`
		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_RGBA(0,0,255,255), 1.0f, 0);
		// `����ת������`
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);
		// `��һƬ3����`
		device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
		device->SetRenderState(D3DRS_TEXTUREFACTOR, 0xffffffff);
		device->SetFVF(D3DFVF_XYZ);
		device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, g_Triangle, sizeof(Vector4));
	}

	// `�ٰѻ�����С�ŵ�ԭʼ��С�Ļ�����`
	{
		// `����ԭ����Framebuffer`
		device->SetRenderTarget(0, g_pMainFrameBuffer);
		device->SetDepthStencilSurface(g_pMainDepthBuffer);
		// `����Ҫ��ͼ���ڲ�`
		device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		// `ʹ�ö�̬��ͼ`
		device->SetTexture(0, g_pTexture);
		device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		// `����ת������`
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &ident_matrix);
		// `����ͼ�׵�����������`
		device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_VT));
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}

// ʹ��DirectX 9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	if ( g_bWireframe )
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	switch(g_iMode)
	{
	default:
	case 1:
		Antialiasing_None();
		break;
	case 2:
		Antialiasing_MultiSampling();
		break;
	case 3:
		Antialiasing_SuperSampling();
		break;
	}
}