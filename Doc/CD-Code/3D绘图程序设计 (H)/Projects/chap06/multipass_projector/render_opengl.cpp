#include <windows.h>

#include "glew.h" // OpenGL extension
#include <GL/gl.h>

#include "Gut.h"
#include "GutTexture_OpenGL.h"
#include "GutModel_OpenGL.h"

#include "render_data.h"

static Matrix4x4 g_view_matrix;
static Matrix4x4 g_projection_matrix;

GLuint g_texture = 0;

CGutModel_OpenGL g_Model_OpenGL;

bool InitResourceOpenGL(void)
{
	// ��ͷ����ϵת������
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ͶӰ����
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);

	CGutModel::SetTexturePath("../../textures/");
	
	g_Model_OpenGL.ConvertToOpenGLModel(&g_Model);

	g_texture = GutLoadTexture_OpenGL("../../textures/nasa_stars.tga");

	if ( g_texture==0 )
		return false;

	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);
	// ����2D��ͼ����
	glEnable(GL_TEXTURE_2D);
	// ����zbuffer����������
	glEnable(GL_DEPTH_TEST);
	//
	glDepthFunc(GL_LEQUAL);

	return true;
}

bool ReleaseResourceOpenGL(void)
{

	return true;
}

// callback function. ���ڴ�С�ı�ʱ�ᱻ����, �������µĴ��ڴ�С.
void ResizeWindowOpenGL(int width, int height)
{
	// ʹ���µĴ��ڴ�С��Ϊ�µĻ�ͼ�ֱ���
	glViewport(0, 0, width, height);
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	g_projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, aspect, 0.1f, 100.0f);
	// �����ӽ�ת������
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &g_projection_matrix);
}

void SetupLightingOpenGL(void)
{
	int LightID = GL_LIGHT0;

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(LightID);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &g_vAmbientLight[0]);

	glLightfv(LightID, GL_POSITION, &g_Light.m_Position[0]);
	glLightfv(LightID, GL_DIFFUSE, &g_Light.m_Diffuse[0]);
	glLightfv(LightID, GL_SPECULAR, &g_Light.m_Specular[0]);

	glLightf(LightID, GL_CONSTANT_ATTENUATION,	1.0f);
	glLightf(LightID, GL_LINEAR_ATTENUATION,	0.0f);
	glLightf(LightID, GL_QUADRATIC_ATTENUATION, 0.0f);
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	Matrix4x4 world_view_matrix = g_world_matrix * view_matrix;

	{
		// `�������������`
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf( (float *) &view_matrix);
		SetupLightingOpenGL();
		glLoadMatrixf( (float *) &world_view_matrix);
		if ( g_bPass0 )
			g_Model_OpenGL.Render();
	}

	{
		// `ͶӰ��
		sModelMaterial_OpenGL material;
		material.m_bBlend = true;
		material.m_SrcBlend = GL_ONE;
		material.m_DestBlend = GL_ONE;
		material.m_Textures[0] = g_texture;
		material.Submit(NULL);

		// `�����Զ�������ͼ���깦��`
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);
		// `���óɲο�����λ����������ͼ����`
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//
		Matrix4x4 ident_matrix = Matrix4x4::IdentityMatrix();
		glTexGenfv(GL_S, GL_OBJECT_PLANE, &ident_matrix[0][0]);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, &ident_matrix[1][0]);
		glTexGenfv(GL_R, GL_OBJECT_PLANE, &ident_matrix[2][0]);
		//
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

		// `����`texture matrix
		Vector4 vLightPos = g_Light.m_Position;
		Vector4 vLightUp(0.0f, 1.0f, 0.0f);
		Vector4 vLightLookat = g_Light.m_LookAt;
		// `ͶӰ��λ�õľ�ͷ����ϵת������`
		Matrix4x4 light_view_matrix = GutMatrixLookAtRH(vLightPos, vLightLookat, vLightUp);
		// `ͶӰ����ͷ��ͶӰת������`
		Matrix4x4 light_projection_matrix = GutMatrixPerspectiveRH_OpenGL(30.0f, 1.0f, 0.1f, 100.0f);
		// `�� -1~1 ת���� 0~1 ��Χ�ľ���`
		Matrix4x4 uv_offset_matrix;
		uv_offset_matrix.Scale_Replace(0.5f, -0.5f, 1.0f); // invert Y
		uv_offset_matrix[3].Set(0.5f, 0.5f, 0.0f, 1.0f);
		// `��������Ҫʹ�õ�`texture matrix
		Matrix4x4 texture_matrix = g_world_matrix * light_view_matrix * light_projection_matrix * uv_offset_matrix;
		// `ʹ��`texture matrix
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf( (float *)&texture_matrix);
		
		if ( g_bPass1 )
			// `����0����ʹ���ο�ģ���е���������`
			g_Model_OpenGL.Render(0);

		glLoadIdentity();

		glDisable(GL_LIGHTING);
	}

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
