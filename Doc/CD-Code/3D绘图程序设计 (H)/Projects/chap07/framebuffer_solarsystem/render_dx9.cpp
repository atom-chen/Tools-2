#include "Gut.h"
#include "render_data.h"

LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DSURFACE9 g_pDepthStencil = NULL;

Matrix4x4 g_projection_matrix;

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFOV, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	device->CreateTexture(512, 512, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture, NULL);
	device->CreateDepthStencilSurface(512, 512, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &g_pDepthStencil, NULL);

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

	Vector4 eye(0.0f, 0.0f, 15.0f); 
	Vector4 lookat(0.0f, 0.0f, 0.0f); 
	Vector4 up(0.0f, 1.0f, 0.0f); 

	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(60.0f, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);

	Matrix4x4 view_matrix = GutMatrixLookAtRH(eye, lookat, up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);

	// `�������ݸ�ʽ`
	// D3DFVF_XYZ = `ʹ��3������������¼λ��`
	// D3DFVF_DIFFUSE = `ʹ��32bits������������¼BGRA��ɫ`
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 

	// `̫��`
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_sun_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, 
		g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pSunVertices, sizeof(Vertex_VC) );
	// `����`
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_earth_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, 
		g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pEarthVertices, sizeof(Vertex_VC) );
	// `����`
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_moon_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, 
		g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pMoonVertices, sizeof(Vertex_VC) );
}
// ʹ��Direct3D9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 

	// `��̫��ϵ���˶�������һ��render target��`
	{
		LPDIRECT3DSURFACE9 pFrameBufferBackup, pDepthBufferBackup;
		device->GetRenderTarget(0, &pFrameBufferBackup); pFrameBufferBackup->Release();
		device->GetDepthStencilSurface(&pDepthBufferBackup); pDepthBufferBackup->Release();

		LPDIRECT3DSURFACE9 pSurface;
		g_pTexture->GetSurfaceLevel(0, &pSurface); 

		device->SetRenderTarget(0, pSurface);
		device->SetDepthStencilSurface(g_pDepthStencil);

		device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 100, 100, 255), 1.0f, 0);

		RenderSolarSystemDX9();

		pSurface->Release();
		device->SetRenderTarget(0, pFrameBufferBackup);
		device->SetDepthStencilSurface(pDepthBufferBackup);
	}

	// `����һ������Ľ����Ϊ��ͼ��ʹ��`
	{
		// `�������`
		device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 128, 255), 1.0f, 0);
		// `ͶӰ����`
		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
		// `��ͷ����ϵת������`
		Matrix4x4 view_matrix = g_Control.GetViewMatrix();
		Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &world_matrix);
		// `ʹ�ö�̬��ͼ`
		device->SetTexture(0, g_pTexture);
		// `��������`
		device->SetFVF(D3DFVF_XYZ|D3DFVF_TEX1); 
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_VT));
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
