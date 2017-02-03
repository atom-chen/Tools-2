#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"
#include "GutModel_OpenGL.h"

#include "render_data.h"

GLuint g_TextureID = 0;

bool InitResourceOpenGL(void)
{
	// ����ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	// ������ͼ
	const char *texture_array[] = 
	{
		"../../textures/uffizi_right.tga",
		"../../textures/uffizi_left.tga",
		"../../textures/uffizi_top.tga",
		"../../textures/uffizi_bottom.tga",
		"../../textures/uffizi_back.tga", // `��������ϵ�� Z+ Ϊ��ͷ��.`
		"../../textures/uffizi_front.tga" // `��������ϵ�� Z- Ϊ��ͷǰ��.`
	};

	g_TextureID = GutLoadCubemapTexture_OpenGL(texture_array);

	// ʹ��CUBEMAP��ͼ����
	glEnable(GL_TEXTURE_CUBE_MAP);
	// ʹ��CUBEMAP��ͼ
	glBindTexture( GL_TEXTURE_CUBE_MAP, g_TextureID );

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
	// `ʹ��CUBEMAP��ͼ����`
	glEnable(GL_TEXTURE_CUBE_MAP);
	// `ʹ��CUBEMAP��ͼ`
	glBindTexture( GL_TEXTURE_CUBE_MAP, g_TextureID );
	// Trilinear filter
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	// `����ת������`
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 world_view_matrix = world_matrix * view_matrix;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &world_view_matrix);
	// `����Vertex Array`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VN), g_pSphereVertices);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex_VN), g_pSphereVertices[0].m_Normal);
	// `����`
	glDrawElements(
		GL_TRIANGLES, // `ָ����Ҫ���Ļ���ͼ������`
		g_iNumSphereIndices, // `�м�������ֵ`
		GL_UNSIGNED_SHORT, // `����ֵ������`
		g_pSphereIndices // `����ֵ����`
	);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
