#include <d3dx9.h>

#include "Gut.h"
#include "GutWin32.h"
#include "GutTexture_DX9.h"
#include "GutModel_DX9.h"

#include "render_data.h"

static LPDIRECT3DCUBETEXTURE9 g_pTexture = NULL;
static LPDIRECT3DVERTEXDECLARATION9 g_pVertexDecl = NULL;
static CGutModel_DX9 g_Model_DX9;

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	int w, h;
	GutGetWindowSize(w, h);
	float aspect = (float) h / (float) w;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ������ͼ
	const char *texture_array[] = 
	{
		"../../textures/uffizi_right.tga",
		"../../textures/uffizi_left.tga",
		"../../textures/uffizi_top.tga",
		"../../textures/uffizi_bottom.tga",
		"../../textures/uffizi_back.tga", // `��������ϵ�� Z+ Ϊ��ͷ��.`
		"../../textures/uffizi_front.tga" // `��������ϵ�� Z- Ϊ��ͷǰ��.`
	};

	g_pTexture = GutLoadCubemapTexture_DX9(texture_array);
	if ( g_pTexture==NULL )
	{
		// ��Щ��Ӳ����֧�� mipmapped cubemap , ������ dds �İ汾.
		g_pTexture = GutLoadCubemapTexture_DX9("../../textures/uffizi_cubemap.dds");
		if ( g_pTexture==NULL )
			return false;
	}

	// ���ö������ݸ�ʽ
	D3DVERTEXELEMENT9 decl[] = 
	{
		// float*3 for position (x,y,z)
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		// float*3 for texcoord (x,y,z)
		{0,12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(decl, &g_pVertexDecl);

	return true;
}

bool ReleaseResourceDX9(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVertexDecl);

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// Reset Device
	GutResetGraphicsDeviceDX9();
	// �����ӽ�ת������
	int w, h;
	GutGetWindowSize(w, h);
	float aspect = (float) h / (float) w;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

// `ʹ��Direct3D9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `�������`
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 
	// `����ת������`
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &world_matrix);
	// `�������ݸ�ʽ`
	device->SetVertexDeclaration(g_pVertexDecl); 
	// `ʹ����ͼ`
	device->SetTexture(0, g_pTexture);
	// trilinear filter
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	// `����`
	device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,	// `ָ����Ҫ���Ļ���ͼ������` 
		0, // `��ʹ�õ���С������, ��ʵ��û̫���ô�.`
		g_iNumSphereVertices, // `�����������м�������`
		g_iNumSphereTriangles, // `Ҫ������������ͼ��`
		g_pSphereIndices, // `��������`
		D3DFMT_INDEX16, // `�������������`
		g_pSphereVertices, // `��������`
		sizeof(Vertex_VN) // `����������ÿ������Ĵ�С`
		);
	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
