#include <windows.h>

#include "glew.h" // OpenGL extension
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "GutWin32.h"
#include "render_data.h"

static Matrix4x4 g_projection_matrix;

static GLuint g_texture = 0;
static GLuint g_depthtexture = 0;
static GLuint g_framebuffer = 0;
static GLuint g_depthbuffer = 0;

bool InitResourceOpenGL(void)
{
	if ( glGenFramebuffersEXT==NULL )
	{
		printf("Could not create frame buffer object\n");
		return false;
	}

	// ͶӰ����
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFOV, 1.0f, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// ��һ��framebuffer object
	glGenFramebuffersEXT(1, &g_framebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_framebuffer);

	// ����һ����ͼ�ռ��framebuffer object��ͼʹ�� 
	{
		glGenTextures(1, &g_texture);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		// ����filter
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// ������ͼ��С����ʽ
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		// framebuffer��RGBA��ͼ
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, g_texture, 0);
	}

	// ����zbuffer��framebuffer objectʹ��
	{
		glGenRenderbuffersEXT(1, &g_depthbuffer);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, g_depthbuffer);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 512, 512);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, g_depthbuffer);
	}

	// ���framebuffer object�Ƿ����ɹ�
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if ( status!=GL_FRAMEBUFFER_COMPLETE_EXT )
	{
		return false;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	if ( g_framebuffer )
	{
		glDeleteFramebuffersEXT(1, &g_framebuffer);
		g_framebuffer = 0;
	}

	if ( g_depthbuffer )
	{
		glDeleteRenderbuffersEXT(1, &g_depthbuffer);
		g_depthbuffer = 0;
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
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFOV, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
}

static void RenderSolarSystemOpenGL(void)
{
	Vector4 eye(0.0f, 0.0f, 15.0f); 
	Vector4 lookat(0.0f, 0.0f, 0.0f); 
	Vector4 up(0.0f, 1.0f, 0.0f); 

	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(60.0f, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	Matrix4x4 view_matrix = GutMatrixLookAtRH(eye, lookat, up);
	Matrix4x4 world_view_matrix;

	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_TEXTURE_2D);

	// `̫��`
	world_view_matrix = g_sun_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pSunVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pSunVertices[0].m_RGBA);
	glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
	// `����`
	world_view_matrix = g_earth_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pEarthVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pEarthVertices[0].m_RGBA);
	glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
	// `����`
	world_view_matrix = g_moon_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pMoonVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pMoonVertices[0].m_RGBA);
	glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	{
		// `ʹ��`g_framebuffer framebuffer object	
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_framebuffer);
		glViewport(0, 0, 512, 512);
		// `�������`
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//
		RenderSolarSystemOpenGL();
	}

	{
		// `ʹ����framebuffer object, Ҳ���Ǵ���.`
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		int w, h;
		GutGetWindowSize(w, h);
		glViewport(0, 0, w, h);

		//` �������`
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// `�����һ������ת������ͷ����ϵ�ľ���`
		Matrix4x4 view_matrix = g_Control.GetViewMatrix();
		Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
		Matrix4x4 world_view_matrix = world_matrix * view_matrix;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf( (float *) &world_view_matrix);
		// `���ö������ݸ�ʽ`
		glEnableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VT), g_Quad_Inv[0].m_Position);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex_VT), g_Quad_Inv[0].m_Texcoord);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
