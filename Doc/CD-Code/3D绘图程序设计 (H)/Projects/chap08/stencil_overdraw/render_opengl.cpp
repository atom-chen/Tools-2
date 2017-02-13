#include <windows.h>

#include "glew.h" // OpenGL extension
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "GutWin32.h"
#include "GutModel_OpenGL.h"
#include "render_data.h"

static Matrix4x4 g_projection_matrix;

static CGutModel_OpenGL g_Model_OpenGL;

bool InitResourceOpenGL(void)
{
	// ͶӰ����
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFOV, 1.0f, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_DEPTH_TEST);

	CGutModel::SetTexturePath("../../textures/");

	g_Model_OpenGL.ConvertToOpenGLModel(&g_Model);

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
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFOV, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// `�������`
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 world_view_matrix = world_matrix * view_matrix;

	// `�������, ������ Stencil Buffer.`
	{
		// `�������`
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf( (float *) &g_projection_matrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf( (float *) &world_view_matrix);

		// `���� Stencil Test`
		glEnable(GL_STENCIL_TEST);
		// `���� Stencil Test ����, ������Զ����.`
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		// `���� Stencil Buffer ����`
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		// `�������`
		g_Model_OpenGL.Render();
		// `����ȥ�ı� Stencil Buffer ����`
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	sModelMaterial_OpenGL material;
	material.Submit(NULL);

	// `����������������, ����Ҫ����������.`
	glDepthFunc(GL_ALWAYS);

	// `���ö������ݸ�ʽ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_V), &g_Quad[0].m_Position);

	// `����ɫ��ʾֻ���¹�1�ε�����`
	{
		glStencilFunc(GL_EQUAL, 1, 0xff);
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	// `����ɫ��ʾ���¹�2�ε�����`
	{
		glStencilFunc(GL_EQUAL, 2, 0xff);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	// `�ú�ɫ����ʾ���³���3�����ϵ�����`
	{
		glStencilFunc(GL_EQUAL, 3, 0xff);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	// `�ú�ɫ����ʾ���³���3�����ϵ�����`
	{
		// `���3С��stencil buffer��ֵ, �����ų���. `
		// `Ҳ����stencil bufferֵҪ����3����˼`
		glStencilFunc(GL_LESS, 3, 0xff); 
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	// `��ԭ����`
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDepthFunc(GL_LESS);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
