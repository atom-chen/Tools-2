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
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_FLAT); // �ر��ڲ�
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ʹ�������ģʽ
	// glEnable(GL_CULL_FACE); // ���Ա��Ծ�ͷ����
	return true;
}

bool ReleaseResourceOpenGL(void)
{
	// û���κ���
	return true;
}

void ResizeWindowOpenGL(int w, int h)
{
	glViewport(0, 0, w, h);
	float aspect = (float) h / (float) w;
	// ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, aspect, 1.0f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// `���ú�GPUҪȥ�Ķ�ȡ������������`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), &g_vertices[0].m_Position);
	// `���ú�GPUҪȥ�Ķ�ȡ������ɫ����`
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), &g_vertices[0].m_RGBA);
	// `����Ҫ�ı�GL_MODELVIEW����`
	glMatrixMode(GL_MODELVIEW);	

	static float angle = 0.0f;
	angle += 0.01f;

	// `����ת������`
	Matrix4x4 world_view_matrix = g_view_matrix;
	// `������ת����`
	world_view_matrix.RotateZ(angle); 
	glLoadMatrixf( (float *) &world_view_matrix);
	// `������������8������`
	glDrawElements(
		GL_TRIANGLES, // `ָ����Ҫ���Ļ���ͼ������`
		18, // `�м�������ֵ`
		GL_UNSIGNED_SHORT, // `����ֵ������`
		g_indices // `����ֵ����`
	);

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
