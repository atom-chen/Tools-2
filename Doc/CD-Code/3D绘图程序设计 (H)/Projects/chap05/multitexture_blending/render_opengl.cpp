#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"

#include "render_data.h"

GLuint g_Texture0_ID = 0;
GLuint g_Texture1_ID = 0;

bool InitResourceOpenGL(void)
{
	// ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	// ������ͼ
	g_Texture0_ID = GutLoadTexture_OpenGL("../../textures/brickwall.tga");
	// ʹ��Trilinear Filter
	glBindTexture(GL_TEXTURE_2D, g_Texture0_ID);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	// ������ͼ
	g_Texture1_ID = GutLoadTexture_OpenGL("../../textures/graffiti_happy.tga");
	// ʹ��Trilinear Filter
	glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	if ( g_Texture0_ID )
	{
		// �ͷ���ͼ��Դ
		glDeleteTextures(1, &g_Texture0_ID);
		g_Texture0_ID = 0;
	}

	if ( g_Texture1_ID )
	{
		// �ͷ���ͼ��Դ
		glDeleteTextures(1, &g_Texture1_ID);
		g_Texture1_ID = 0;
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
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// `������ͷ�����涼������`
	glDisable(GL_CULL_FACE);
	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Position);

	// `�򿪵�0����ͼ`
	glActiveTexture(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_Texture0_ID);
	// `ָ����0����ͼ����ͼ����`
	glClientActiveTexture(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);
	// `�򿪵�1����ͼ`
	glActiveTexture(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);
	// `ָ����1����ͼ����ͼ����`
	glClientActiveTexture(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);

	switch(g_iMode)
	{
	case 1:
		// `����һ�����`
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		break;
	case 2:
		// `������ͼ Alpha ֵ����һ��ȡȨ�أ�Alpha ֵԽ���Խ�ӽ���һ�����ɫ��`
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		break;
	case 3:
		// `����һ�����`
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		break;
	}

	// `����ת������`
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 world_view_matrix = world_matrix * view_matrix;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &world_view_matrix);
	// `��������`
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
