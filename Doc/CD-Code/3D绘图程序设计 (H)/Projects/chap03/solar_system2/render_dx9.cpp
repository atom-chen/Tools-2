#include "Gut.h"
#include "render_data.h"
#include <d3dx9.h>
#include <d3dx9math.h>

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

	D3DPRESENT_PARAMETERS d3dpresent;
    
	ZeroMemory( &d3dpresent, sizeof(d3dpresent) );
    d3dpresent.Windowed = TRUE; // ʹ�ô���ģʽ
    d3dpresent.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpresent.BackBufferFormat = D3DFMT_UNKNOWN; // ʹ�ô���ģʽ���Բ�ȥ����
	d3dpresent.BackBufferCount = 1; // �ṩһ��backbuffer
	d3dpresent.EnableAutoDepthStencil = TRUE; // �Զ���DepthStencil Buffer
	d3dpresent.AutoDepthStencilFormat = D3DFMT_D24S8; // DepthStencil Bufferģʽ
	
	device->Reset(&d3dpresent);

	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
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
	// `�������`
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 
	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);

	// `�������ݸ�ʽ`
	// D3DFVF_XYZ = `ʹ��3������������¼λ��`
	// D3DFVF_DIFFUSE = `ʹ��32bits������������¼BGRA��ɫ`
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 

	D3DXMATRIX temp_matrix;
	// `̫��, ����������ת����`
	D3DXMATRIX sun_matrix, sun_ry, sun_rx;
	D3DXMatrixRotationX(&sun_rx, g_fRotate_X);		
	D3DXMatrixRotationY(&sun_ry, g_fRotate_Y);		
	D3DXMatrixMultiply(&sun_matrix, &sun_ry, &sun_rx);

	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &sun_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, 
		g_pSphereIndices, D3DFMT_INDEX16, g_pSunVertices, sizeof(Vertex_VC) );

	// `ˮ��`
	float mercury_rotate_y = 2.0f * MATH_PI * (g_simulation_days / days_a_year_mercury); 

	D3DXMATRIX mercury_matrix, mercury_translate, mercury_rotate;
	D3DXMatrixRotationY(&mercury_rotate, mercury_rotate_y);
	D3DXMatrixTranslation(&mercury_translate, mercury_to_sun_distance, 0.0f, 0.0f);
	D3DXMatrixMultiply(&temp_matrix, &mercury_translate, &mercury_rotate);
	D3DXMatrixMultiply(&mercury_matrix, &temp_matrix, &sun_matrix);

	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &mercury_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pMoonVertices, sizeof(Vertex_VC) );

	// `����`
	float venus_rotate_y = 2.0f * MATH_PI * (g_simulation_days / days_a_year_venus); 

	D3DXMATRIX venus_matrix, venus_rotate, venus_translate;
	D3DXMatrixRotationY(&venus_rotate, venus_rotate_y);
	D3DXMatrixTranslation(&venus_translate, venus_to_sun_distance, 0.0f, 0.0f);
	D3DXMatrixMultiply(&temp_matrix, &venus_translate, &venus_rotate);
	D3DXMatrixMultiply(&venus_matrix, &temp_matrix, &sun_matrix);

	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &venus_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pMoonVertices, sizeof(Vertex_VC) );

	// `����`
	float earth_rotate_y = 2.0f * MATH_PI * (g_simulation_days / days_a_year); 

	D3DXMATRIX earth_matrix, earth_rotate, earth_translate;
	D3DXMatrixRotationY(&earth_rotate, earth_rotate_y);
	D3DXMatrixTranslation(&earth_translate, earth_to_sun_distance, 0.0f, 0.0f);
	D3DXMatrixMultiply(&temp_matrix, &earth_translate, &earth_rotate);
	D3DXMatrixMultiply(&earth_matrix, &temp_matrix, &sun_matrix);

	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &earth_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pEarthVertices, sizeof(Vertex_VC) );
	
	// `����`
	float moon_rotate_y = 2.0f * MATH_PI * (g_simulation_days / days_a_month); 

	D3DXMATRIX moon_matrix, moon_rotate, moon_translate;
	D3DXMatrixRotationY(&moon_rotate, moon_rotate_y);
	D3DXMatrixTranslation(&moon_translate, moon_to_earth_distance, 0.0f, 0.0f);
	D3DXMatrixMultiply(&temp_matrix, &moon_translate, &moon_rotate);
	D3DXMatrixMultiply(&moon_matrix, &temp_matrix, &earth_matrix);

	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &moon_matrix);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, g_iNumSphereVertices, g_iNumSphereTriangles, g_pSphereIndices, D3DFMT_INDEX16, g_pMoonVertices, sizeof(Vertex_VC) );

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
