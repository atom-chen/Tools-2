#include "Gut.h"
#include "render_data.h"

static LPDIRECT3DVERTEXSHADER9 g_pVertexShaderDX9 = NULL;
static LPDIRECT3DPIXELSHADER9  g_pPixelShaderDX9 = NULL;
static LPDIRECT3DVERTEXDECLARATION9 g_pVertexShaderDecl = NULL;

bool InitResourceDX9(void)
{
	// `����Vertex Shader`
	g_pVertexShaderDX9 = GutLoadVertexShaderDX9_HLSL(
		"../../shaders/vertex_transform.shader", "VS", "vs_1_1");
	if ( g_pVertexShaderDX9==NULL )
		return false;
	// `����Pixel Shader`
	g_pPixelShaderDX9 = GutLoadPixelShaderDX9_HLSL(
		"../../shaders/vertex_transform.shader", "PS", "ps_2_0");
	if ( g_pPixelShaderDX9==NULL )
		return false;

	// `��ͷ����ϵת������`
	Matrix4x4 view_matrix = 
		GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `ͶӰת������`
	Matrix4x4 projection_matrix = 
		GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 1.0f, 100.0f);
	// `��ǰ�����������`
	Matrix4x4 view_projection_matrix = 
		view_matrix * projection_matrix;
	
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `�����ӽ�ת������`
	device->SetVertexShaderConstantF(0, (float *)&view_projection_matrix, 4);

	return true;
}

bool ReleaseResourceDX9(void)
{
	if ( g_pVertexShaderDX9 )
	{
		g_pVertexShaderDX9->Release();
		g_pVertexShaderDX9 = NULL;
	}

	if ( g_pPixelShaderDX9 )
	{
		g_pPixelShaderDX9->Release();
		g_pPixelShaderDX9 = NULL;
	}

	return true;
}

// `ʹ��DirectX9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
    device->Clear(
		0, NULL, // `�����������`
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // `�����ɫ��Z Buffer`
		D3DCOLOR_ARGB(0, 0, 0, 0), // `����Ҫ����ɫ��ɺ�ɫ`
		1.0f, // `����Ҫ��Zֵ��Ϊ1, Ҳ�����뾵ͷ��Զ.`
		0 // `����Ҫ��Stencil buffer��Ϊ0, �����Ƿ�����û������.`
	);
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 
	// `�������ݸ�ʽ`
	device->SetFVF(D3DFVF_XYZW); 
	// `����Vertex/Pixel Shader`
	device->SetVertexShader(g_pVertexShaderDX9);
	device->SetPixelShader(g_pPixelShaderDX9);
	// `������������8������`
	device->DrawPrimitiveUP(D3DPT_LINELIST, 8, g_vertices, sizeof(Vector4)); 
	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
