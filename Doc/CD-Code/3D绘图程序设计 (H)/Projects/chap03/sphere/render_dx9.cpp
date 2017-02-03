#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// ��RGBA�ĳ�BGRA
	for ( int i=0; i<g_iNumSphereVertices; i++ )
	{
		unsigned char temp = g_pSphereVertices[i].m_RGBA[0];
		g_pSphereVertices[i].m_RGBA[0] = g_pSphereVertices[i].m_RGBA[2];
		g_pSphereVertices[i].m_RGBA[2] = temp;
	}

	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	GutResetGraphicsDeviceDX9();

	// �����ӽ�ת������
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);

	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
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

	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);

	// �������ݸ�ʽ
	// D3DFVF_XYZ = ʹ��3������������¼λ��
	// D3DFVF_DIFFUSE = ʹ��32bits������������¼BGRA��ɫ
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 

	// ������
	device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST, // ָ����Ҫ���Ļ���ͼ������ 
		0, // ��ʹ�õ���С������, ��ʵ��û̫���ô�
		g_iNumSphereVertices, // �����������м�������
		g_iNumSphereTriangles, // Ҫ������������ͼ��
		g_pSphereIndices, // ��������
		D3DFMT_INDEX16, // �������������
		g_pSphereVertices, // ��������
		sizeof(Vertex_VC) // ����������ÿ������Ĵ�С
	);

	// �������еĻ�ͼָ�������
	device->EndScene(); 
	
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
