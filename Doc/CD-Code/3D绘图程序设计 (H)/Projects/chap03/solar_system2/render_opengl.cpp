#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;

bool InitResourceOpenGL(void)
{
	// �����һ������ת������ͷ����ϵ�ľ���
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_CULL_FACE);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	// û���κ���
	return true;
}

// callback function. ���ڴ�С�ı�ʱ�ᱻ����, �������µĴ��ڴ�С.
void ResizeWindowOpenGL(int width, int height)
{
	// ʹ���µĴ��ڴ�С��Ϊ�µĻ�ͼ�ֱ���
	glViewport(0, 0, width, height);
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(60.0f, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// `����Ҫ������ķ�ʽ���붥��λ�ú���ɫ`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	Matrix4x4 world_view_matrix;

	glMatrixMode(GL_MODELVIEW);
	// `���뾵ͷת������`
	glLoadMatrixf( (float *) &view_matrix );
	glPushMatrix(); // `��Ŀǰ�ľ���浽stack��`
		// `̫��, ����������ת����.`
		glRotatef(FastMath::RadianToDegree(g_fRotate_X), 1.0f, 0.0f, 0.0f);
		glRotatef(FastMath::RadianToDegree(g_fRotate_Y), 0.0f, 1.0f, 0.0f);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pSunVertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pSunVertices[0].m_RGBA);
		glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
		// `ˮ��`
		glPushMatrix(); // `��Ŀǰ�ľ���浽stack��`
			float mercury_rotate_y = 360.0f * (g_simulation_days / days_a_year_mercury); 
			glRotatef(mercury_rotate_y, 0.0f, 1.0f, 0.0f);
			glTranslatef(mercury_to_sun_distance, 0.0f, 0.0f);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pMoonVertices);
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pMoonVertices[0].m_RGBA);
			glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
		// `��stack��pop��һ������, ��ʹ�õ�Ŀǰ��ָ��Ҫ�����ľ���`GL_MODELVIEW
		glPopMatrix(); 
		// `����`
		glPushMatrix(); // `��Ŀǰ�ľ���浽stack��`
			float venus_rotate_y = 360.0f * (g_simulation_days / days_a_year_venus); 
			glRotatef(venus_rotate_y, 0.0f, 1.0f, 0.0f);
			glTranslatef(venus_to_sun_distance, 0.0f, 0.0f);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pMoonVertices);
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pMoonVertices[0].m_RGBA);
			glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
		// `��stack��pop��һ������, ��ʹ�õ�Ŀǰ��ָ��Ҫ�����ľ���`GL_MODELVIEW
		glPopMatrix(); 
		// `����`
		glPushMatrix();// `��Ŀǰ�ľ���浽stack��`
			float earth_rotate_y = 360.0f * (g_simulation_days / days_a_year); 
			glRotatef(earth_rotate_y, 0.0f, 1.0f, 0.0f);
			glTranslatef(earth_to_sun_distance, 0.0f, 0.0f);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pEarthVertices);
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pEarthVertices[0].m_RGBA);
			glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
			// `����`
			float moon_rotate_y = 360.0f * (g_simulation_days / days_a_month);
			glRotatef(moon_rotate_y, 0.0f, 1.0f, 0.0f);
			glTranslatef(moon_to_earth_distance, 0.0f, 0.0f);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), g_pMoonVertices);
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), g_pMoonVertices[0].m_RGBA);
			glDrawElements(GL_TRIANGLES, g_iNumSphereIndices, GL_UNSIGNED_SHORT, g_pSphereIndices);
			// `��stack��pop��һ������, ��ʹ�õ�Ŀǰ��ָ��Ҫ�����ľ���GL_MODELVIEW`
		glPopMatrix(); 
	glPopMatrix();

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
