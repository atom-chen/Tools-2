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
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 1.0f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

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
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ���ú�GPUҪȥ�Ķ�ȡ��������
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(Vector4), g_vertices);
	// ����Ҫ�ı�GL_MODELVIEW����
	glMatrixMode(GL_MODELVIEW);	

	for ( int i=0; i<4; i++ )
	{
		// `����ת������`
		Matrix4x4 world_matrix;
		world_matrix.Scale_Replace(g_scale[i]); // `�������ž���`
		world_matrix[3] = g_position[i]; // `ֱ�Ӱ�λ������������½�.`

		// `����ת������`
		Matrix4x4 world_view_matrix = world_matrix * g_view_matrix;
		glLoadMatrixf( (float *) &world_view_matrix);
		
		// ������������8������
		glDrawElements(
			GL_LINES, // ָ����Ҫ���Ļ���ͼ������
			16, // �м�������ֵ
			GL_UNSIGNED_SHORT, // ����ֵ������
			g_indices // ����ֵ����
		);
	}

	// �ѱ���backbuffer�Ļ�����ʾ����
	GutSwapBuffersOpenGL();
}
