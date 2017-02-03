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
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(g_fFovW, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	// ������ͷ�����涼������
	glDisable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
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
	// `�򿪹��չ���`
	glEnable(GL_LIGHTING);
	// `��/�ر�auto normalize����`
	if ( g_bAutoNormalize )
		glEnable(GL_NORMALIZE);
	else
		glDisable(GL_NORMALIZE);
	// `��/�ر�localviewer����`
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, g_bLocalViewer ? 1 : 0 );
	// `���û�����`
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (float *)&g_vGlobal_AmbientLight);
	// `���ö�������ķ�������`
	glMaterialfv(GL_FRONT, GL_AMBIENT, (float *) &g_vMaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, (float *) &g_vMaterialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (float *) &g_vMaterialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, (float *) &g_vMaterialEmissive);
	glMaterialf (GL_FRONT, GL_SHININESS, g_fMaterialShininess);
	// `���ù�Դ`
	for ( int i=0; i<g_iNumLights; i++ )
	{
		// `ÿ����Դ�ֱ���GL_LIGHT0,GL_LIGHT1,GL_LIGHT2����ʾ`
		// `�����ڶ���ʱ����˳������,������GL_LIGHT0+n����ù�ԴID`
		int LightID = GL_LIGHT0 + i;

		if ( g_Lights[i].m_bEnabled )
		{
			// ����յ��
			glEnable(LightID);
			
			switch(g_Lights[i].m_eType)
			{
			case LIGHT_DIRECTIONAL:
				// `��Դ����`
				// `��һ��(x,y,z,w)����������GL_POSITION, ���wֵ��0�ᱻ��Ϊ�Ƿ����.`
				glLightfv(LightID, GL_POSITION, (float *)&(-g_Lights[i].m_vDirection) );
				break;
			case LIGHT_POINT:
				// `��Դλ��`
				glLightfv(LightID, GL_POSITION, (float *)&g_Lights[i].m_vPosition);
				// `������˥��ֵ` 
				// 1/(CONSTANT + LINEAR*d + QUADRATIC*d^2) 
				// `��ʽ�е�CONSTANT,LINEAR,QUADRATICֵ`
				glLightf(LightID, GL_CONSTANT_ATTENUATION,	g_Lights[i].m_vAttenuation[0]);
				glLightf(LightID, GL_LINEAR_ATTENUATION,	g_Lights[i].m_vAttenuation[1]);
				glLightf(LightID, GL_QUADRATIC_ATTENUATION, g_Lights[i].m_vAttenuation[2]);
				break;
			case LIGHT_SPOT:
				// ��Դλ��
				glLightfv(LightID, GL_POSITION, (float *)&g_Lights[i].m_vPosition);
				// `������˥��ֵ`
				// 1/(CONSTANT + LINEAR*d + QUADRATIC*d^2) 
				// `��ʽ�е�CONSTANT, LINEAR, QUADRATICֵ`
				glLightf(LightID, GL_CONSTANT_ATTENUATION,	g_Lights[i].m_vAttenuation[0]);
				glLightf(LightID, GL_LINEAR_ATTENUATION,	g_Lights[i].m_vAttenuation[1]);
				glLightf(LightID, GL_QUADRATIC_ATTENUATION, g_Lights[i].m_vAttenuation[2]);
				// `�����ķ���`
				glLightfv(LightID, GL_SPOT_DIRECTION, (float *)&g_Lights[i].m_vDirection);
				// `����Բ׶��һ��Ƕ�`
				glLightf(LightID, GL_SPOT_CUTOFF, g_Lights[i].m_fSpotlightCutoff * 0.5f);
				// `����Բ׶�ĽǶ�˥��`
				glLightf(LightID, GL_SPOT_EXPONENT, g_Lights[i].m_fSpotlightExponent);
				break;
			}
			// `��Դ��Ambientֵ`
			glLightfv(LightID, GL_AMBIENT, (float *)&g_Lights[i].m_vAmbientColor); 
			// `��Դ��Diffuseֵ`
			glLightfv(LightID, GL_DIFFUSE, (float *)&g_Lights[i].m_vDiffuseColor);
			// `��Դ��specularֵ`
			glLightfv(LightID, GL_SPECULAR, (float *)&g_Lights[i].m_vSpecularColor);
		}
		else
		{
			// `�ر���յ��`
			glDisable(LightID);
		}
	}
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	// ����Ҫ������ķ�ʽ���붥��λ�ú���ɫ
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_V3N3), g_pGridVertices[0].m_Position);
	glNormalPointer(GL_FLOAT, sizeof(Vertex_V3N3), g_pGridVertices[0].m_Normal);
	
	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// ʹ�þ�ͷת������
	glLoadMatrixf( (float *) &view_matrix);
	// ���ù�Դ, ���й�Դ��ת������ͷ����ϵ,����Ҫ��ʹ�þ�ͷת������
	SetupLightingOpenGL();
	
	Matrix4x4 world_view_matrix = g_world_matrix * view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	// ��������
	glDrawElements (GL_TRIANGLE_STRIP, g_iNumGridIndices, GL_UNSIGNED_SHORT, g_pGridIndices);
	// �ѱ���backbuffer�Ļ�����ʾ����
	GutSwapBuffersOpenGL();
}
