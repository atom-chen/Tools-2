#include "Vector4.h"
#include "render_data.h"
#include "gut.h"

// ��ͷλ��
Vector4 g_eye(0.0f, 0.0f, 2.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, 1.0f, 0.0f); 
// ��ͷת������
Matrix4x4 g_view_matrix;
// ������ת����
Matrix4x4 g_world_matrix;
// `��Դ����`
Vector4 g_vLightAmbient(0.1f, 0.1f, 0.1f, 0.1f);
Vector4 g_vLightDirection(0.0f, 0.0f, 1.0f, 0.0f);
Vector4 g_vLightColor(1.0f, 1.0f, 1.0f, 1.0f);
// ���ε�4������
// Position, Color, Normal
Vertex_VCN g_Quad[4] =
{
	{ Vector4(-0.5f, -0.5f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ Vector4( 0.5f, -0.5f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ Vector4(-0.5f,  0.5f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ Vector4( 0.5f,  0.5f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) }
};

Vertex_DX9 g_Quad_dx9[4];

// `����ɫ��ֵ���óɻ�����`
void CalculateAmbientLight(Vertex_VCN *pVertices, int num_vertices)
{
	for ( int i=0; i<num_vertices; i++ )
	{
		pVertices[i].m_Color = g_vLightAmbient;
	}
}

// `���㷽���, ��ֻ�붥�㷨�ߺ͹�Դ�����й�.`
void CalculateDirectionalLight(Vertex_VCN *pVertices, int num_vertices)
{
	for ( int i=0; i<num_vertices; i++ )
	{
		// `���ת��������������ϵ�Ķ��㷨��, RotateVector����ֻ����ת, ����λ��.`
		Vector4 vNormal = g_world_matrix.RotateVector(pVertices[i].m_Normal);
		// `���㷨�ߺ͹��߷���ļн�, ����������ǿ��.`
		Vector4 vIntensity = Vector3Dot(vNormal, g_vLightDirection);
		// `��intensity������0-1�ķ�Χ`
		vIntensity.Clamp_to_0();
		// `�ۼ��ϼ������������ǿ��`
		pVertices[i].m_Color += vIntensity * g_vLightColor;
		pVertices[i].m_Color = pVertices[i].m_Color.Clamp_to_1();
	}
}

void ConvertToDX9(Vertex_VCN g_quad_in[], Vertex_DX9 g_quad_out[], int num_vertices)
{
	for ( int i=0; i<num_vertices; i++ )
	{
		g_quad_in[i].m_Position.StoreXYZ(g_quad_out[i].m_Position);
		GutConvertColor(g_quad_in[i].m_Color, g_quad_out[i].m_Color);
	}
}
