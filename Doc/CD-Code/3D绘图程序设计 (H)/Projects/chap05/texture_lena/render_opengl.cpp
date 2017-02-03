#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>
#include <GL/GLAux.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;
GLuint g_TextureID = 0;

bool InitResourceOpenGL(void)
{
	// `�����һ������ת������ͷ����ϵ�ľ���`
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `����ͶӰ����`
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	// `������ͼ`
	AUX_RGBImageRec *pTextureImage = auxDIBImageLoad( "../../textures/lena.bmp" );
	if ( pTextureImage==NULL )
		return false;
	for ( int i=0; i<4; i++ )
	{
		g_Quad[i].m_Texcoord[1] = 1.0f - g_Quad[i].m_Texcoord[1];
	}
	// `����һ����ͼ����`
	glGenTextures( 1, &g_TextureID );
	// `ʹ��g_TextureID��ͼ����`
	glBindTexture( GL_TEXTURE_2D, g_TextureID );
	// `������ͼ����`
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, 
		pTextureImage->sizeX, pTextureImage->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data );
	// `������ʾ��ͼ����Сʱʹ�������ڲ� `
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	// `������ʾ��ͼ���Ŵ�ʱʹ��������� `
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// `��������ͼ��, �Ϳ��԰�ԭʼ������ȥ.`
	if( pTextureImage->data )
		free( pTextureImage->data );

	free( pTextureImage );

	// `ʹ��2D��ͼ����`
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
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);
	// ����Ҫ������ķ�ʽ���붥��λ�ú���ɫ
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Position);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);
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
