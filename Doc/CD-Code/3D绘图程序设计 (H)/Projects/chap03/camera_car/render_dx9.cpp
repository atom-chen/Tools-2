#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 0.1f, 100.0f);
	// �����ӽ�ת������
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �ı�����������ķ���
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	int num_vertices = sizeof(g_pyramid_vertices)/sizeof(Vertex_VC);

	// ��RGBA����ɫ����ת����DX9 BGRA��ʽ
	for ( int i=0; i<num_vertices; i++ )
	{
		unsigned char temp = g_pyramid_vertices[i].m_RGBA[0];
		g_pyramid_vertices[i].m_RGBA[0] = g_pyramid_vertices[i].m_RGBA[2];
		g_pyramid_vertices[i].m_RGBA[2] = temp;
	}

	num_vertices = sizeof(g_road_vertices)/sizeof(Vertex_VC);
	for ( int i=0; i<num_vertices; i++ )
	{
		unsigned char temp = g_road_vertices[i].m_RGBA[0];
		g_road_vertices[i].m_RGBA[0] = g_road_vertices[i].m_RGBA[2];
		g_road_vertices[i].m_RGBA[2] = temp;
	}

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

	// `�������`
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 

	// `�������ݸ�ʽ`
	// `D3DFVF_XYZ = ʹ��3������������¼λ��`
	// `D3DFVF_DIFFUSE = ʹ��32bits������������¼BGRA��ɫ`
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE); 

	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);

	Vector4 border(-15.0f, 0.0f, -15.0f);
	Vector4 grid_position = border;

	const int grids_x = 30;
	const int grids_z = 30;

	for ( int x=0; x<grids_x; x++ )
	{
		int grid_x = x & 0x07;
		grid_position[2] = border[2];

		for ( int z=0; z<grids_z; z++ )
		{
			int grid_z = z & 0x07;
			char c = g_map[grid_x][grid_z];

			// `����ת������`
			Matrix4x4 object_matrix;
			object_matrix.Translate_Replace(grid_position);

			if ( c==0 ) // `��·`
			{
				device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &object_matrix);
				// `�����ذ�`
				device->DrawIndexedPrimitiveUP(
					D3DPT_TRIANGLESTRIP,
					0,
					4,
					2,
					g_road_trianglestrip_indices,
					D3DFMT_INDEX16,
					g_road_vertices,
					sizeof(Vertex_VC)
				);
			}
			else // `������`
			{
				// `���ý������ĸ߶�`
				object_matrix.Scale_Replace(1.0f, (float) c, 1.0f);
				object_matrix[3] = grid_position;
				device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &object_matrix);
				// `����������`
				device->DrawIndexedPrimitiveUP(
					D3DPT_TRIANGLEFAN, // `ָ����Ҫ���Ļ���ͼ������`
					0, // `��ʹ�õ���С������, ��ʵ��û̫���ô�.`
					5, // `�����������м�������`
					4, // `Ҫ������������ͼ��`
					g_pyramid_trianglefan_indices,	// `��������`
					D3DFMT_INDEX16,		// `�������������`
					g_pyramid_vertices,	// `��������`
					sizeof(Vertex_VC)	// `����������ÿ������Ĵ�С`
				);
			}

			grid_position[2] += 1.0f;
		}

		grid_position[0] += 1.0f;
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
