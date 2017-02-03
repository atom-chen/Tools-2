#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;

bool InitResourceOpenGL(void)
{
	// ʹ��zbuffer test
	glEnable(GL_DEPTH_TEST);
	// �����һ������ת������ͷ����ϵ�ľ���
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ����ͶӰ����
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

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
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
}

void SetupLightingOpenGL(void)
{
	// `���û�����`
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (float *)&g_vGlobal_AmbientLight);
	// `ʹ��two side lighting����`
	glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// `���ö�����������ķ�������`
	glMaterialfv(GL_FRONT, GL_AMBIENT, &g_vMaterialAmbient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &g_vMaterialDiffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &g_vMaterialSpecular[0]);
	glMaterialfv(GL_FRONT, GL_EMISSION, &g_vMaterialEmissive[0]);
	glMaterialf (GL_FRONT, GL_SHININESS, g_fMaterialShininess);
	// `���ö���������ķ�������`
	glMaterialfv(GL_BACK, GL_AMBIENT, &g_vMaterialAmbient_Back[0]);
	glMaterialfv(GL_BACK, GL_DIFFUSE, &g_vMaterialDiffuse_Back[0]);
	glMaterialfv(GL_BACK, GL_SPECULAR, &g_vMaterialSpecular_Back[0]);
	glMaterialfv(GL_BACK, GL_EMISSION, &g_vMaterialEmissive_Back[0]);
	glMaterialf (GL_BACK, GL_SHININESS, g_fMaterialShininess_Back);
	// `�򿪹��չ���`
	glEnable(GL_LIGHTING);
	// `�򿪵�0�Ź�`
	glEnable(GL_LIGHT0);
	// `��һ��(x,y,z,w)����������GL_POSITION, ���wֵ��0�ᱻ��Ϊ�Ƿ���`
	glLightfv(GL_LIGHT0, GL_POSITION, (float *)&(-g_vLightDirection) );
	// `��Դ��Ambientֵ`
	glLightfv(GL_LIGHT0, GL_AMBIENT, &g_vLightAmbient[0]); 
	// `��Դ��Diffuseֵ`
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &g_vLightDiffuse[0]);
	// `��Դ��Specularֵ`
	glLightfv(GL_LIGHT0, GL_SPECULAR, &g_vLightSpecular[0]);
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// `������ͷ�����涼������`
	glDisable(GL_CULL_FACE);
	// `���ù�Դ`
	glLoadMatrixf( (float *) &g_view_matrix);
	SetupLightingOpenGL();
	// `����Ҫ������ķ�ʽ���붥��λ�úͷ���`
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VN), &g_Quad[0].m_Position);
	glNormalPointer(GL_FLOAT, sizeof(Vertex_VN), &g_Quad[0].m_Normal);
	// `���㲢����ת������`
	Matrix4x4 world_view_matrix = g_world_matrix * g_view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	// `����һƬ����`
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
