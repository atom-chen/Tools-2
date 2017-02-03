#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `�������ͷ����ϵ��ת������`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(60.0f, 1.0f, 1.0f, 100.0f);
	// `�����ӽ�ת������`
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// `���þ�ͷת������`
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	// `�رչ���`
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

// `ʹ��Direct3D9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 
	// `�������ݸ�ʽ`
	device->SetFVF(D3DFVF_XYZ); 

	// `��ת�Ƕ�`
	static float angle = 0.0f;
	angle += 0.01f;

	// `������ת����`
	Matrix4x4 world_matrix;
	world_matrix.RotateZ_Replace(angle);
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &world_matrix);

	// `������������8������`
	device->DrawIndexedPrimitiveUP(
		D3DPT_LINELIST, // `ָ����Ҫ���Ļ���ͼ������ `
		0, // `��ʹ�õ���С������, ��ʵ��û̫���ô�.`
		5, // `�����������м�������`
		8, // `Ҫ������������ͼ��`
		g_indices,		// `��������`
		D3DFMT_INDEX16, // `�������������`
		g_vertices,		// `��������`
		sizeof(Vector4)	// `����������ÿ������Ĵ�С`
	);

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer��ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
