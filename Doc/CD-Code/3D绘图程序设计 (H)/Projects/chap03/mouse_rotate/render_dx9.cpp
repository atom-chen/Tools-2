#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 1.0f, 100.0f);
	
	// �����ӽ�ת������
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// ���þ�ͷת������
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ر��ڲ�
	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

// ʹ��DirectX 9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->Clear(
		0, NULL, // ����������� 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����ɫ��Z buffer 
		D3DCOLOR_ARGB(0, 0, 0, 0), // ����Ҫ����ɫ��ɺ�ɫ
		1.0f, // ����Ҫ��Zֵ��Ϊ1, Ҳ�����뾵ͷ��Զ
		0 // ����Ҫ��Stencil buffer��Ϊ0, �����Ƿ�����û������.
	);
	
	// ��ʼ�»�ͼָ��
	device->BeginScene(); 

	// �������ݸ�ʽ
	// D3DFVF_XYZ = ʹ��4������������¼λ��
	// D3DFVF_DIFFUSE = ʹ��32bits������������¼BGRA��ɫ
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 

	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_object_matrix);

	// ������������8������
	device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST, // ָ����Ҫ���Ļ���ͼ������ 
		0, // ��ʹ�õ���С������, ��ʵ��û̫���ô�
		5, // �����������м�������
		6, // Ҫ������������ͼ��
		g_indices, // ��������
		D3DFMT_INDEX16, // �������������
		g_vertices, // ��������
		sizeof(Vertex_VC) // ����������ÿ������Ĵ�С
	); 

	// �������еĻ�ͼָ�������
	device->EndScene(); 
	
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
