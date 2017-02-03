#include "Gut.h"
#include "render_data.h"

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

bool InitResourceDX9(void)
{
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// `�����ӽ�ת������`
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// `�رչ���`
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// `�ı�����������ķ���`
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	for ( int i=0; i<g_iNumSphereVertices; i++ )
	{
		unsigned char temp = g_pSphereVertices[i].m_RGBA[0];
		g_pSphereVertices[i].m_RGBA[0] = g_pSphereVertices[i].m_RGBA[2];
		g_pSphereVertices[i].m_RGBA[2] = temp;
	}
	
	int vsize = g_iNumSphereVertices * sizeof(Vertex_VC);

	if ( D3D_OK!=device->CreateVertexBuffer(vsize, 0, 0, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL) )
	{
		return false;
	}

	Vertex_VC *pVertexArray = NULL;
	// `���Vertex Buffer���ڴ�λ��`
	g_pVertexBuffer->Lock(0, vsize, (void **)&pVertexArray, 0);
	memcpy(pVertexArray, g_pSphereVertices, vsize);
	g_pVertexBuffer->Unlock();

	int isize = g_iNumSphereIndices * sizeof(unsigned short);

	if ( D3D_OK!=device->CreateIndexBuffer(isize, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL) )
	{
		return false;
	}

	unsigned short *pIndexArray = NULL;
	// `���Index Buffer���ڴ�λ��`
	g_pIndexBuffer->Lock(0, isize, (void **)&pIndexArray, 0);
	memcpy(pIndexArray, g_pSphereIndices, isize);
	g_pIndexBuffer->Unlock();

	return true;
}

bool ReleaseResourceDX9(void)
{
	if ( g_pVertexBuffer )
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if ( g_pIndexBuffer )
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	GutResetGraphicsDeviceDX9();

	// `�����ӽ�ת������`
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);

	// `�رչ���`
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// `�ı�����������ķ���`
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}

// `ʹ��Direct3D9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 

	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);

	// `�������ݸ�ʽ`
	// D3DFVF_XYZ = `ʹ��3������������¼λ��`
	// D3DFVF_DIFFUSE = `ʹ��32bits������������¼BGRA��ɫ`
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 

	device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex_VC));
	device->SetIndices(g_pIndexBuffer);

	// `������`
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, // `ָ����Ҫ���Ļ���ͼ������`
		0, 
		0, // `��ʹ�õ���С������, ��ʵ��û̫���ô�.`
		g_iNumSphereVertices, // `�����������м�������`
		0, 
		g_iNumSphereTriangles // `Ҫ������������ͼ��`
	);

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
