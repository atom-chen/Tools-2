#include <windows.h>

#include "glew.h" // OpenGL extension
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "GutWin32.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;
static Matrix4x4 g_projection_matrix;

const int NumObjects = 2;
GLuint g_OcclusionQueryObjects[NumObjects];

bool InitResourceOpenGL(void)
{
	// �����һ������ת������ͷ����ϵ�ľ���
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ͶӰ����
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glGenQueries(2, g_OcclusionQueryObjects);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	glDeleteQueries(2, g_OcclusionQueryObjects);

	return true;
}

// callback function. ���ڴ�С�ı�ʱ�ᱻ����, �������µĴ��ڴ�С.
void ResizeWindowOpenGL(int width, int height)
{
	// ʹ���µĴ��ڴ�С��Ϊ�µĻ�ͼ�ֱ���
	glViewport(0, 0, width, height);
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(60.0f, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
}

GLuint g_FrameCount = 0;

static void RenderSolarSystemOpenGL(void)
{
	int index = g_FrameCount % 2;
	GLuint id = g_OcclusionQueryObjects[index];

	// ����Ҫ������ķ�ʽ���붥��λ�ú���ɫ
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	Matrix4x4 world_view_matrix;

	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_TEXTURE_2D);

	// ̫��
	world_view_matrix = g_sun_matrix * g_view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pSunVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pSunVertices[0].m_RGBA);
	glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
	// ����
	// ��鷶Χ��ʼ
	glBeginQuery(GL_SAMPLES_PASSED, id);
		world_view_matrix = g_earth_matrix * g_view_matrix;
		glLoadMatrixf( (float *) &world_view_matrix);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pEarthVertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pEarthVertices[0].m_RGBA);
		glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
	// ��鷶Χ����
	glEndQuery(GL_SAMPLES_PASSED);
	// ����
	world_view_matrix = g_moon_matrix * g_view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pMoonVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pMoonVertices[0].m_RGBA);
	glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);

	if ( g_FrameCount )
	{
		id = g_OcclusionQueryObjects[(index + 1) % 2];
		GLint samples_passed = 0;
		GLint result = GL_FALSE;
		int num_loops = 0;

		while(result==GL_FALSE)
		{
			glGetQueryObjectiv(id, GL_QUERY_RESULT_AVAILABLE, &result);
			// ������ܻ�û����, Ҫ�ٲ�ѯһ��
			num_loops++;
		}
		// �鿴�м����㱻����// �鿴�м����㱻����
		glGetQueryObjectiv(id, GL_QUERY_RESULT, &samples_passed);
		printf("Earth %s\t\r", samples_passed ? "visible" : "disappear");
	}

	g_FrameCount++;
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// ��ô��ڴ�С
	int w, h;
	GutGetWindowSize(w, h);
	// �������
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// object * view matrix
	Matrix4x4 object_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	g_view_matrix = object_matrix * view_matrix;
	// projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&g_projection_matrix[0][0]);
	// render objects
	RenderSolarSystemOpenGL();
	// �ѱ���backbuffer�Ļ�����ʾ����
	GutSwapBuffersOpenGL();
}
