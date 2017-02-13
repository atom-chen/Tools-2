#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"
#include "GutModel_OpenGL.h"

#include "render_data.h"

static Matrix4x4 g_projection_matrix;

CGutModel_OpenGL g_Model_OpenGL;

bool InitResourceOpenGL(void)
{
	// ͶӰ����
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, g_fNear, g_fFar);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);

	g_Model_OpenGL.ConvertToOpenGLModel(&g_Model);

	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);
	// ����2D��ͼ����
	glEnable(GL_TEXTURE_2D);
	// ����zbuffer����������
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_NORMALIZE);

	return true;
}

bool ReleaseResourceOpenGL(void)
{

	return true;
}

// callback function. ���ڴ�С�ı�ʱ�ᱻ����, �������µĴ��ڴ�С.
void ResizeWindowOpenGL(int width, int height)
{
	// ʹ���µĴ��ڴ�С��Ϊ�µĻ�ͼ�ֱ���
	glViewport(0, 0, width, height);
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, aspect, g_fNear, g_fFar);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
}

void SetupLightingOpenGL(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	
	// �Ѽ��㹫ʽ�� (diffuse + specular ) * texture �ĳ� diffuse * texture + specular
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	GutSetupLightOpenGL(0, g_Lights[0]);
	GutSetupLightOpenGL(1, g_Lights[1]);
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����ת������
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 world_view_matrix = world_matrix * view_matrix;
	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf( (float *) &view_matrix);
	SetupLightingOpenGL();

	glLoadMatrixf( (float *) &world_view_matrix);
	g_Model_OpenGL.Render();

	// �ѱ���backbuffer�Ļ�����ʾ����
	GutSwapBuffersOpenGL();
}
