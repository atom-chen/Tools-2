#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `�����һ������ת������ͷ����ϵ�ľ���`
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

	device->Clear(
		0, NULL, // `����������� `
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // `�����ɫ��Z Buffer`
		D3DCOLOR_ARGB(0, 0, 0, 0), // `����Ҫ����ɫ��ɺ�ɫ`
		1.0f, // `����Ҫ��Zֵ��Ϊ1, Ҳ�����뾵ͷ��Զ.`
		0 // `����Ҫ��Stencil buffer��Ϊ0, �����Ƿ�����û������.`
	);
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 
	// `�������ݸ�ʽ`
	device->SetFVF(D3DFVF_XYZ); 

	// `4���������Ļ���λ��`
	Vector4 pos[4] = 
	{
		Vector4(-1.0f, -1.0f, 0.0f),
		Vector4( 1.0f, -1.0f, 0.0f),
		Vector4(-1.0f,  1.0f, 0.0f),
		Vector4( 1.0f,  1.0f, 0.0f),
	};

	Matrix4x4 world_matrix;

	for ( int i=0; i<4; i++ )
	{
		// `����ת������`
		world_matrix.Translate_Replace(pos[i]);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &world_matrix);
		// `������������8������`
		device->DrawPrimitiveUP(D3DPT_LINELIST, 8, g_vertices, sizeof(Vector4)); 
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
