#include <windows.h>
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;

bool InitResourceOpenGL(void)
{
	// `�����һ������ת������ͷ����ϵ�ľ���`
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `ͶӰ����`
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(60.0f, 1.0f, 1.0f, 100.0f);
	// `�����ӽ�ת������`
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	// `û���κ���`
	return true;
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// `���ú�GPUҪȥ�Ķ�ȡ��������`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(Vector4), g_vertices);
	// `����Ҫ�ı�GL_MODELVIEW����`
	glMatrixMode(GL_MODELVIEW);	

	// `4����������λ��`
	Vector4 pos[4] = 
	{
		Vector4(-1.0f, -1.0f, 0.0f),
		Vector4( 1.0f, -1.0f, 0.0f),
		Vector4(-1.0f,  1.0f, 0.0f),
		Vector4( 1.0f,  1.0f, 0.0f),
	};

	Matrix4x4 world_matrix;
	Matrix4x4 world_view_matrix;

	for ( int i=0; i<4; i++ )
	{
		// `�õ�λ�ƾ���`
		world_matrix.Translate_Replace(pos[i]); 
		world_view_matrix = world_matrix * g_view_matrix;
		// `����ת������'
		glLoadMatrixf( (float *) &world_view_matrix);
		// `������������8������`
		glDrawArrays(GL_LINES, 0, 16);
	}

	// `�ѱ���backbuffer��ʾ����`
	GutSwapBuffersOpenGL();
}
