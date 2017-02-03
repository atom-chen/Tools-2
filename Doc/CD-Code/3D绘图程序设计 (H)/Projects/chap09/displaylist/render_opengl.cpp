#include <windows.h>
#include "glew.h"
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"

#include "render_data.h"

static Matrix4x4 g_view_matrix;
static GLuint g_quad_list[4];

GLuint g_TextureID = 0;

bool InitResourceOpenGL(void)
{
	const char *extension = (const char *)glGetString(GL_EXTENSIONS);
	printf("OpenGL Extension : \n%s\n", extension);

	// �����һ������ת������ͷ����ϵ�ľ���
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ����ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	// ������ͼ
	g_TextureID = GutLoadTexture_OpenGL("../../textures/lena_rgba.tga");
	// ʹ��g_TextureID��ͼ����
	glBindTexture( GL_TEXTURE_2D, g_TextureID );
	// ������ʾ��ͼʱʹ�������ڲ�
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	// ������ʾ��ͼʱʹ���������
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	// ʹ��2D��ͼ����
	glEnable(GL_TEXTURE_2D);

	GLint modes[] = {
		GL_REPEAT,// ���½�
		GL_MIRRORED_REPEAT, // ���Ͻ�
		GL_CLAMP_TO_EDGE, // ���½�
		GL_CLAMP_TO_BORDER, // ���Ͻ�
	};

	float border_color[4] = {0.5f, 0.5f, 0.5f, 0.5f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

	Vertex_VT *vertex = NULL;

	for ( int i=0; i<4; i++ )
	{
		g_quad_list[i] = glGenLists(1);
		// `����һ���µ�Display List��¼`
		glNewList(g_quad_list[i], GL_COMPILE);
			// `ʹ����ͼ`
			glBindTexture( GL_TEXTURE_2D, g_TextureID );
			// `ʹ����ͼ�ڲ幦��`
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// `������ͼ����Ѱַģʽ`
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, modes[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, modes[i]);
			// `��������`
			glBegin(GL_QUADS);
				vertex = &g_Quads[i][0];
				glTexCoord2f(vertex->m_Texcoord[0], vertex->m_Texcoord[1]);
				glVertex3fv(vertex->m_Position);

				vertex = &g_Quads[i][1];
				glTexCoord2f(vertex->m_Texcoord[0], vertex->m_Texcoord[1]);
				glVertex3fv(vertex->m_Position);

				vertex = &g_Quads[i][2];
				glTexCoord2f(vertex->m_Texcoord[0], vertex->m_Texcoord[1]);
				glVertex3fv(vertex->m_Position);

				vertex = &g_Quads[i][3];
				glTexCoord2f(vertex->m_Texcoord[0], vertex->m_Texcoord[1]);
				glVertex3fv(vertex->m_Position);
			glEnd();

		glEndList();
	}

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
	// `��ͷ����ת������`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `ת������`
	Matrix4x4 world_view_matrix = g_world_matrix * view_matrix;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &world_view_matrix);

	for ( int i=0; i<4; i++ )
	{
		// `�ظ�Display List������¼�Ķ���`
		glCallList(g_quad_list[i]);
	}

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
