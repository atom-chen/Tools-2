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
	// ����ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixOrthoRH_OpenGL(g_fOrthoWidth, g_fOrthoHeight, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);

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

static void SetupLighting(void)
{
	// �򿪹��չ���
	glEnable(GL_LIGHTING);
	// `���û�����`
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (float *)&g_vAmbientLight);
	// `���ö�������ķ�������`
	Vector4 vFullIntensity(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 vZeroIntensity(0.0f, 0.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, (float *) &vFullIntensity);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, (float *) &vFullIntensity);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (float *) &vFullIntensity);
	glMaterialfv(GL_FRONT, GL_EMISSION, (float *) &vZeroIntensity);
	glMaterialf (GL_FRONT, GL_SHININESS, g_fMaterialShininess);

	int i;
	for ( i=0; i<g_iNumActivatedLights; i++ )
	{
		int LightID = GL_LIGHT0 + i;

		glEnable(LightID);

		glLightfv(LightID, GL_POSITION, (float *) &g_ActivatedLights[i].m_Position);
		glLightfv(LightID, GL_DIFFUSE, (float *) &g_ActivatedLights[i].m_Diffuse);
		glLightfv(LightID, GL_SPECULAR, (float *) &g_ActivatedLights[i].m_Specular);

		glLightf(LightID, GL_CONSTANT_ATTENUATION,	1.0f);
		glLightf(LightID, GL_LINEAR_ATTENUATION,	0.0f);
		glLightf(LightID, GL_QUADRATIC_ATTENUATION, 0.0f);
	}

	for ( ; i<MAX_ACTIVATED_LIGHTS; i++ )
	{
		glDisable(GL_LIGHT0+i);
	}
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// `�õ���������Դλ��`	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( (float *) &g_view_matrix);
	// `��ʱ�رչ��չ���`
	glDisable(GL_LIGHTING);
	// `���û���ʱʹ��5x5����������һ����`
	glPointSize(5.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VCN), &g_LightPosition[0].m_Position);
	glColorPointer (4, GL_FLOAT, sizeof(Vertex_VCN), &g_LightPosition[0].m_Color);
	glDrawArrays(GL_POINTS, 0, NUM_LIGHTS);

	SetupLighting();

	glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VCN), &g_Quad[0].m_Position);
	glNormalPointer(GL_FLOAT, sizeof(Vertex_VCN), &g_Quad[0].m_Normal);
	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 world_view_matrix = g_world_matrix * g_view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	// `��һƬ������������Ч��`
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
