#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"

#include "render_data.h"

static Matrix4x4 g_view_matrix;
GLuint g_TextureID = 0;

bool InitResourceOpenGL(void)
{
	// �����һ������ת������ͷ����ϵ�ľ���
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ����ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	// ������ͼ
	g_TextureID = GutLoadTexture_OpenGL("../../textures/brick.tga");
	glBindTexture( GL_TEXTURE_2D, g_TextureID );
	// ʹ��2D��ͼ����
	glEnable(GL_TEXTURE_2D);
	// �ѳ���0-1��Χ�������ȡ������ΪREPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ���Զ�������ͼ���깦��
	// S/T�ֱ������ͼ�����X/Y��
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// ���óɲο�����λ����������ͼ����
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	// ������ֵ�ֱ����a*x+b*y+c*z+d*w��a,b,c,dֵ
	// 1*x+0*y+0*z+0*w = x, ��ͼ����x��ֵ���ڶ���λ��xֵ
	float fvTexcoordScale_S[] = {1.0f, 0.0f, 0.0f, 0.0f};
	glTexGenfv(GL_S, GL_OBJECT_PLANE, fvTexcoordScale_S);
	// 0*x+1*y+0*z+0*w = x, ��ͼ����y��ֵ���ڶ���λ��yֵ
	float fvTexcoordScale_T[] = {0.0f, 1.0f, 0.0f, 0.0f};
	glTexGenfv(GL_T, GL_OBJECT_PLANE, fvTexcoordScale_T);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	if ( g_TextureID )
	{
		glDeleteTextures(1, &g_TextureID);
		g_TextureID = 0;
	}
	return true;
}

// callback function. ���ڴ�С�ı�ʱ�ᱻ����, �������µĴ��ڴ�С.
void ResizeWindowOpenGL(int width, int height)
{
	// ʹ���µĴ��ڴ�С��Ϊ�µĻ�ͼ�ֱ���
	glViewport(0, 0, width, height);
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);
	// ����Ҫ������ķ�ʽ���붥��λ�ú���ɫ
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_V), &g_Quad[0].m_Position);
	// Trilinear filter
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	Matrix4x4 world_view_matrix = g_world_matrix * view_matrix;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &world_view_matrix);
	// ��������
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// �ѱ���backbuffer�Ļ�����ʾ����
	GutSwapBuffersOpenGL();
}
