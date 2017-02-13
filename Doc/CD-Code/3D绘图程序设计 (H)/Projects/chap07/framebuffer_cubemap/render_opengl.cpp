#include <windows.h>

#include "glew.h" // OpenGL extension
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "GutWin32.h"
#include "GutModel_OpenGL.h"
#include "render_data.h"

static CGutModel_OpenGL g_Models_OpenGL[4];

static Matrix4x4 g_view_matrix;
static Matrix4x4 g_projection_matrix;
static Matrix4x4 g_mirror_view_matrix;

static GLuint g_texture = 0;
static GLuint g_depthtexture = 0;
static GLuint g_framebuffer = 0;
static GLuint g_depthbuffer = 0;

static GLuint g_framebuffers[6];
static GLuint g_textures[6];

bool InitResourceOpenGL(void)
{
	if ( glGenFramebuffersEXT==NULL )
	{
		printf("Could not create frame buffer object\n");
		return false;
	}

	// `�����һ������ת������ͷ����ϵ�ľ���`
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `ͶӰ����`
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFOV, 1.0f, 0.1f, 100.0f);
	// `�����ӽ�ת������`
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	glGenTextures(1, &g_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_texture);
	// `����`filter
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLuint cubemap_id[] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};


	// `����zbuffer��framebuffer objectʹ��`
	glGenRenderbuffersEXT(1, &g_depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, g_depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 512, 512);

	int fail = 0;
	for ( int i=0; i<6; i++ )
	{
		glGenFramebuffersEXT(1, &g_framebuffers[i]);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_framebuffers[i]);
		// `������ͼ��С����ʽ`
		GLuint tex_target = GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + i;
		glTexImage2D(tex_target, 0, GL_RGBA8,  512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		// `framebuffer��RGBA��ͼ`
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, tex_target, g_texture, 0);
		// `6����ͬ������Թ���ͬһ��depthbuffer`
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, g_depthbuffer);

		// `���framebuffer object�Ƿ����ɹ�`
		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if ( status!=GL_FRAMEBUFFER_COMPLETE_EXT )
		{
			fail++;
		}
	}

	// `���framebuffer object�Ƿ����ɹ�`
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if ( status!=GL_FRAMEBUFFER_COMPLETE_EXT )
	{
		return false;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	CGutModel::SetTexturePath("../../textures/");
	
	for ( int i=0; i<4; i++ )
	{
		g_Models_OpenGL[i].ConvertToOpenGLModel(&g_Models[i]);
	}

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

static void RenderSolarSystemOpenGL(Matrix4x4 &view_matrix)
{
	// ����Ҫ������ķ�ʽ���붥��λ�ú���ɫ
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_TEXTURE_2D);

	Matrix4x4 world_view_matrix;
	// ����
	world_view_matrix = g_earth_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	g_Models_OpenGL[1].Render();
	// ����
	world_view_matrix = g_moon_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	g_Models_OpenGL[2].Render();
	// ����
	world_view_matrix = g_mars_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	g_Models_OpenGL[3].Render();
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// `���¶�̬��ͼ`
	{
		Matrix4x4 cubemap_perspective_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 0.1f, 100.0f);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf( (float *)&cubemap_perspective_matrix);
		
		// `����cubemap����������ǰ��6����`
		for ( int i=0; i<6; i++ )
		{
			// `ʹ��`g_framebuffer framebuffer object	
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_framebuffers[i]);
			glViewport(0, 0, 512, 512);
			// `�������`
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// `��ͷҪ��Բ�ͬ�ķ���`
			Matrix4x4 cubemap_view = GutMatrixLookAtRH(g_vCubemap_Eye, g_vCubemap_Lookat[i], -g_vCubemap_Up[i]);
			// `��������`
			RenderSolarSystemOpenGL(cubemap_view);
		}
	}
	// `ʹ�ö�̬��ͼ`
	{
		// `ʹ����framebuffer object, Ҳ���Ǵ���.`
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		int w, h;
		GutGetWindowSize(w, h);
		glViewport(0, 0, w, h);
		// `�������`
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// `���Զ���������ķ�������ת������������ϵ`
		Matrix4x4 view_matrix = g_Control.GetViewMatrix();
		Matrix4x4 inv_view = g_Control.GetCameraMatrix();
		// `ֻ�����������ת����`
		inv_view.NoTranslate();
		// `������ͼת������`
		glActiveTexture(GL_TEXTURE1_ARB);
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf((float *)&inv_view);
		// `ͶӰ����`
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf( (float *) &g_projection_matrix);
		// `ת������`
		glMatrixMode(GL_MODELVIEW);
		Matrix4x4 world_view_matrix = g_sun_matrix * view_matrix;
		glLoadMatrixf( (float *) &world_view_matrix);
		// `��Model�ĵ�3����ͼǿ�ȸĳ�cubemap`
		CGutModel_OpenGL::SetTextureOverwrite(2, g_texture);
		CGutModel_OpenGL::SetMapOverwrite(2, MAP_CUBEMAP);
		//` ��̫��`
		g_Models_OpenGL[0].Render();
		// `��Model�ĵ�3����ͼ��ԭ��ģ��ԭʼ����`
		CGutModel_OpenGL::SetTextureOverwrite(2, 0);
		CGutModel_OpenGL::SetMapOverwrite(2, MAP_NOOVERWRITE);
		// `����������`
		RenderSolarSystemOpenGL(view_matrix);
	}

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
