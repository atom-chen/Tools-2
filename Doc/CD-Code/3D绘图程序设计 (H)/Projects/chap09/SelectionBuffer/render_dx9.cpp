#include "Gut.h"
#include "render_data.h"

#include "GutWin32.h"

Matrix4x4 g_projection_matrix;
LPDIRECT3DQUERY9 g_pOcclusionQuery[2];

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//
	device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &g_pOcclusionQuery[0]);
	device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &g_pOcclusionQuery[1]);

	return true;
}

bool ReleaseResourceDX9(void)
{
	SAFE_RELEASE(g_pOcclusionQuery[0]);
	SAFE_RELEASE(g_pOcclusionQuery[1]);

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
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

static int g_FrameCount = 0;

void RenderSolarSystemDX9(void)
{
	int index = g_FrameCount % 2;
	LPDIRECT3DQUERY9 pQuery = g_pOcclusionQuery[index];

	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �������ݸ�ʽ
	// D3DFVF_XYZ = ʹ��3������������¼λ��
	// D3DFVF_DIFFUSE = ʹ��32bits������������¼BGRA��ɫ
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 
	// ̫��
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_sun_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, 
		g_pSphereIndices, D3DFMT_INDEX16, g_pSunVertices, sizeof(Vertex_VC) );
	// ����
	pQuery->Issue(D3DISSUE_BEGIN);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_earth_matrix);
		device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, 
			g_pSphereIndices, D3DFMT_INDEX16, g_pEarthVertices, sizeof(Vertex_VC) );
	pQuery->Issue(D3DISSUE_END);
	// ����
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_moon_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, 
		g_pSphereIndices, D3DFMT_INDEX16, g_pMoonVertices, sizeof(Vertex_VC) );

	if ( g_FrameCount )
	{
		int num_loops = 0;
		int num_samples_passed = 0;
		// ȥ���ǰһ�������Occlusion Query���
		pQuery = g_pOcclusionQuery[(index + 1) % 2];
		while( pQuery->GetData(&num_samples_passed, 4, D3DGETDATA_FLUSH)==S_FALSE  )
		{
			// ������ܻ�û����, Ҫ�ٲ�ѯһ��
			num_loops++;
		}

		printf("Earth %s, queried %05d times\r", num_samples_passed ? "visible" : "disapper", num_loops);
	}

	g_FrameCount++;
}
// ʹ��DirectX 9����ͼ
void RenderFrameDX9(void)
{
	// ��ô��ڴ�С
	int w, h;
	GutGetWindowSize(w, h);
	// �������
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 100, 100, 255), 1.0f, 0);
	// ��ʼ�»�ͼָ��
	device->BeginScene(); 
	// view matrix
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 object_matrix = g_Control.GetObjectMatrix();
	g_view_matrix = object_matrix * view_matrix;
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *)&g_view_matrix);
	// projection matrix
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *)&g_projection_matrix);
	// render objects
	RenderSolarSystemDX9();

	// �������еĻ�ͼָ�������
	device->EndScene(); 
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
