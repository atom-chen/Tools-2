#include <windows.h>
// OpenGL 1.2+ & extensions
#include "glew.h"
#include "wglew.h"
// OpenGL 1.2-
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static GLuint g_VertexBufferID = 0;
static GLuint g_IndexBufferID = 0;

bool InitResourceOpenGL(void)
{
	// `ͶӰ����`
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 0.1f, 100.0f);
	// `�����ӽ�ת������`
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	
	glMatrixMode(GL_MODELVIEW);	

	// `����һ���µ�Vertex Buffer Object`
	glGenBuffers(1, &g_VertexBufferID);
	// `ʹ��g_VertexBufferID�������Vertex Buffer Object`
	glBindBuffer(GL_ARRAY_BUFFER, g_VertexBufferID);
	// `����Vertex Buffer�Ĵ�С, ��ͬʱ��g_pSphereVertices�����ݿ�������ȥ.`
	glBufferData(GL_ARRAY_BUFFER, g_iNumSphereVertices * sizeof(Vertex_VC), g_pSphereVertices, GL_STATIC_COPY);

	// `����һ���µ�Index Buffer Object`
	glGenBuffers(1, &g_IndexBufferID);
	// `ʹ��g_IndexBufferID�������Index Buffer Object`
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID);
	// `����Index Buffer�Ĵ�С, ��ͬʱ��g_pSphereIndices�����ݿ�����ȥ.`
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_iNumSphereIndices * 2, g_pSphereIndices, GL_STATIC_COPY);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	if ( g_VertexBufferID )
	{
		glDeleteBuffers(1, &g_VertexBufferID);
		g_VertexBufferID = 0;
	}

	if ( g_IndexBufferID )
	{
		glDeleteBuffers(1, &g_IndexBufferID);
		g_IndexBufferID = 0;
	}

	return true;
}

void ResizeWindowOpenGL(int width, int height)
{
	glViewport(0, 0, width, height);
	// `ͶӰ����`
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(60.0f, aspect, 0.1f, 100.0f);
	// `�����ӽ�ת������`
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// `ʹ��g\_VertexBufferID�������Vertex Buffer Object`
	glBindBuffer(GL_ARRAY_BUFFER, g_VertexBufferID);
	// `ʹ��g\_IndexBufferID�������Index Buffer Object`
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IndexBufferID);

	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	// `VertexPointer/ColorPointer���ٴ���ָ��λ��`
	// ���Ǵ����ڴ���Ե�λ��ֵ
	int voffset = (int) &g_pSphereVertices[0].m_Position - (int) &g_pSphereVertices[0];
	int coffset = (int) &g_pSphereVertices[0].m_RGBA - (int) &g_pSphereVertices[0];
	// `���һ��ֵ�����ڴ��е���ʼλ��`
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), (GLvoid *)voffset); // voffset=0
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), (GLvoid *)coffset); // coffset=12

	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &view_matrix);

	glDrawElements(
		GL_TRIANGLES, // `ָ����Ҫ���Ļ���ͼ������`
		g_iNumSphereIndices, // `�м�������ֵ`
		GL_UNSIGNED_SHORT, // `����ֵ������`
		0 // `���ٴ��������ָ��, ���Ǵ�������ֵ��ʼ��λ��.`
	);

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
