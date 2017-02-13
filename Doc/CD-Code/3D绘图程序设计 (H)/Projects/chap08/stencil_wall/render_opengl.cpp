#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"

#include "render_data.h"

static Matrix4x4 g_view_matrix;

GLuint g_Texture0_ID = 0;
GLuint g_Texture1_ID = 0;

bool InitResourceOpenGL(void)
{
	// ��ͷ����ϵת������
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixOrthoRH_OpenGL(g_fOrthoWidth, g_fOrthoHeight, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	// ������ͼ
	g_Texture0_ID = GutLoadTexture_OpenGL("../../textures/brickwall_broken.tga");
	// ʹ��Trilinear Filter
	glBindTexture(GL_TEXTURE_2D, g_Texture0_ID);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	// ������ͼ
	g_Texture1_ID = GutLoadTexture_OpenGL("../../textures/spotlight_effect.tga");
	// ʹ��Trilinear Filter
	glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);

	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);
	// ����2D��ͼ����
	glEnable(GL_TEXTURE_2D);
	// ����zbuffer����������
	glEnable(GL_DEPTH_TEST);

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
	g_fOrthoWidth = g_fOrthoSize;
	g_fOrthoHeight = g_fOrthoSize;
	if ( aspect > 1.0f )
		g_fOrthoHeight *= aspect;
	else
		g_fOrthoWidth /= aspect;

	Matrix4x4 projection_matrix = GutMatrixOrthoRH_OpenGL(g_fOrthoWidth, g_fOrthoHeight, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// `����Ҫ` zbuffer test
	glDisable(GL_DEPTH_TEST);
	
	{
		// `��modelview, projection������ɵ�λ����.`
		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix(); // `��projection��������stack��`
		glLoadIdentity();
		
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5f);

		if ( g_bStencil )
		{
			// `����` Stencil Buffer Test
			glEnable(GL_STENCIL_TEST);
			// `Stencil Test �ж��������ó���Զ����`
			// `Stencil �ο�ֵ����Ϊ 1`
			// `Stencil Mask ���ó� 0xff = 255`
			glStencilFunc(GL_ALWAYS, 1, 0xff);
			// `Stencil Test ����ʱ, �� Stencil �ο�ֵ���� Stencil Buffer ��.`
			// `ǰ���� GL_KEEP ��ָ�� Stencil �� ZBuffer Test ������ʱ, ��ȥ�ı� Stencil Buffer`
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		}
		else
		{
			glDisable(GL_STENCIL_TEST);
		}

		// `ʹ����ͼ`
		glBindTexture(GL_TEXTURE_2D, g_Texture0_ID);
		// `��������, ͬʱ�����ZBuffer.`
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Position);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// `�Ѵ����stack�е�projectionȡ����`
		glPopMatrix();
		glDepthFunc(GL_LESS);
		glDisable(GL_ALPHA_TEST);
	}

	{
		if ( g_bStencil )
		{
			// `ֻ���»�����StencilֵΪ1������`
			glStencilFunc(GL_EQUAL, 1, 0xff);
			// `��ȥ���� Stencil Buffer ��ֵ`
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		}

		// `�򿪻�Ϲ���`
		glEnable(GL_BLEND);
		// `��Ϲ�ʽ` = source_color * 1 + dest_color * 1
		glBlendFunc(GL_ONE, GL_ONE);
		// `ʹ����ͼ`
		glBindTexture(GL_TEXTURE_2D, g_Texture1_ID);
		// `����ת������`
		Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
		Matrix4x4 world_view_matrix = g_world_matrix * view_matrix;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf( (float *) &world_view_matrix);
		// `��������`
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Position);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), &g_Quad[0].m_Texcoord);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		// `�رջ�Ϲ���`		
		glDisable(GL_BLEND);
	}

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
