#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"

#include "render_data.h"

GLuint g_TextureID = 0;

bool InitResourceOpenGL(void)
{
	// ����ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	// ������ͼ
	g_TextureID = GutLoadTexture_OpenGL("../../textures/checkerboard.tga");
	// ʹ��g_TextureID��ͼ����
	glBindTexture( GL_TEXTURE_2D, g_TextureID );
	// �ѳ���0-1��Χ�������ȡ������ΪREPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ʹ��2D��ͼ����
	glEnable(GL_TEXTURE_2D);

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
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// `������ͷ�����涼������`
	glDisable(GL_CULL_FACE);
	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Position);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);
	// `��ͼ���Ŵ�ʱ, ȡ��ӽ�4�������ڲ�.`
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	// `�����������ͼ����Сʱ������`
	switch(g_iFilterMode)
	{
	case 1: // None
		// `��ʹ��mipmap, ȡ���4������ƽ��.`
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// `�ر�anisotrophic filter`
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
		break;
	case 2: // Bilinear
		// `GL_LINEAR = ��ͼ��Сʱȡ4������ƽ��`
		// `MIPMAP_NEAREST = ʹ����ӽ���С��ͼ��`
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		// `�ر�anisotrophic filter`
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
		break;
	case 3: // Trilinear
		// `GL_LINEAR = ��ͼ��Сʱȡ4������ƽ��`
		// `MIPMAP_LINEAR = ʹ����ӽ���С������ͼ��, Ȼ�����ڲ�.`
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		// `�ر�anisotrophic filter`
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
		break;
	case 4: // Anisotropic filter
		// MIPMAP_LINEAR = `ʹ����ӽ���С������ͼ�� , Ȼ�����ڲ� .`
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		// `���� anisotrophic filter`
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);
		break;
	}

	// `�������`
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 object_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 world_view_matrix = object_matrix * view_matrix;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &world_view_matrix);
	// `��������`
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
