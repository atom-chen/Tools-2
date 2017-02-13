#include "Gut.h"
#include "render_data.h"

static LPDIRECT3DVERTEXDECLARATION9 g_pVertexDecl = NULL;

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
	// ���ö������ݸ�ʽ
	D3DVERTEXELEMENT9 decl[] = 
	{
		// float * 4 for position (x,y,z,w)
		{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		// float * 4 for color (r,g,b,a)
		{0, 16,D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(decl, &g_pVertexDecl);

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
	device->SetVertexDeclaration(g_pVertexDecl); 
	// ��������
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_VCN));
	// �������еĻ�ͼָ�������
	device->EndScene(); 
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
