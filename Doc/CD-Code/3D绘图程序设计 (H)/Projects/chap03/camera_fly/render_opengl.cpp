#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;

bool InitResourceOpenGL(void)
{
	// �����һ������ת������ͷ����ϵ�ľ���
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_CULL_FACE);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	// û���κ���
	return true;
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);

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
			Matrix4x4 object_matrix; object_matrix.Identity();
			
			if ( c==0 )
			{
				object_matrix = view_matrix;
				object_matrix.Translate(grid_position);
				glLoadMatrixf( (float *) &object_matrix);
				// `����GPUҪȥ�Ķ�ȡ������������`
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), &g_road_vertices[0].m_Position);
				// `����GPUҪȥ�Ķ�ȡ������ɫ����`
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), &g_road_vertices[0].m_RGBA);
				// `�����ذ�`
				glDrawElements(
					GL_TRIANGLE_STRIP, // `ָ����Ҫ���Ļ���ͼ������`
					4, // `�м�������ֵ`
					GL_UNSIGNED_SHORT, // `����ֵ������`
					g_road_trianglestrip_indices // `����ֵ����`
				);
			}
			else
			{
				// `���ý������ĸ߶�`
				object_matrix.Scale_Replace(1.0f, (float) c, 1.0f);
				object_matrix[3] = grid_position;
				Matrix4x4 world_view_matrix = object_matrix * view_matrix;
				glLoadMatrixf( (float *) &world_view_matrix);
				// `����GPUҪȥ�Ķ�ȡ������������`
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), &g_pyramid_vertices[0].m_Position);
				// `����GPUҪȥ�Ķ�ȡ������ɫ����`
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), &g_pyramid_vertices[0].m_RGBA);
				// `����������`
				glDrawElements(
					GL_TRIANGLE_FAN, // `ָ����Ҫ���Ļ���ͼ������`
					6, // `�м�������ֵ`
					GL_UNSIGNED_SHORT, // `����ֵ������`
					g_pyramid_trianglefan_indices // `����ֵ����`
				);
			}

			grid_position[2] += 1.0f;
		}

		grid_position[0] += 1.0f;
	}

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
