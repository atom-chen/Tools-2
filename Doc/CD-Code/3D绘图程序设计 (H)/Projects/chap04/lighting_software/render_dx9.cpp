#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

void ResizeWindowDX9(int width, int height)
{
	GutResetGraphicsDeviceDX9();
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

// ʹ��DirectX 9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �������
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	// ��ʼ�»�ͼָ��
	device->BeginScene(); 
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);
	// �������ݸ�ʽ
	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	ConvertToDX9(g_pGridVertices, g_pGridVerticesDX9, g_iNumGridVertices);
	// ��������
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, g_iNumGridVertices, g_iNumGridTriangles, 
		g_pGridIndices, D3DFMT_INDEX16, g_pGridVerticesDX9, sizeof(Vertex_DX9) );
	// �������еĻ�ͼָ�������
	device->EndScene(); 
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
