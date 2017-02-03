#include "Vector4.h"
#include "render_data.h"
#include "gut.h"
#include "GutModel.h"

// ��ͷλ��
Vector4 g_eye(0.0f, 0.0f, 30.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, 1.0f, 0.0f); 
// ��ͷת������
Matrix4x4 g_view_matrix;
// ������ת����
Matrix4x4 g_world_matrix;
// ��ȡģ�͵Ķ���
CGutModel g_Model;

// ת���������ݵĺ���, Direct3D��OpenGL���Թ���.
void CopyVertexBuffer(void *target, sModelVertex *source, int num_vertices)
{
	// ���������, OpenGL��Direct3D����ʱֻ��ҪPosition & Normal
	struct sRunTimeVertex
	{
		float m_Position[3];
		float m_Normal[3];
	};

	sRunTimeVertex *pVertexArray = (sRunTimeVertex *) target;

	for ( int v=0; v<num_vertices; v++ )
	{
		sRunTimeVertex *p = pVertexArray + v;

		p->m_Position[0] = source[v].m_Position[0];
		p->m_Position[1] = source[v].m_Position[1];
		p->m_Position[2] = source[v].m_Position[2];

		p->m_Normal[0] = source[v].m_Normal[0];
		p->m_Normal[1] = source[v].m_Normal[1];
		p->m_Normal[2] = source[v].m_Normal[2];
	}
}
