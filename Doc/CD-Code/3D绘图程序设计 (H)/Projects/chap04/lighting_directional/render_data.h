#include "Vector4.h"
#include "Matrix4x4.h"

struct Vertex_VCN
{
	Vector4 m_Position; // ����λ��
	Vector4 m_Color;	// ������ɫ
	Vector4 m_Normal;	// ���㷨��
};

struct Vertex_DX9
{
	float m_Position[3];	// ����λ��
	unsigned char m_Color[4]; // ������ɫ
};

// ��������
const float g_fFovW = 45.0f;
extern Vertex_VCN g_Quad[4];
extern Vertex_DX9 g_Quad_dx9[4];

// ��ͷλ��
extern Vector4 g_eye; 
// ��ͷ��׼�ĵ�
extern Vector4 g_lookat; 
// ��ͷ���Ϸ��ķ���
extern Vector4 g_up; 
// ��ͷת������
extern Matrix4x4 g_view_matrix;
// ������ת����
extern Matrix4x4 g_world_matrix;
// ��Դ����
extern Vector4 g_vLightAmbient;
extern Vector4 g_vLightDirection;
extern Vector4 g_vLightColor;

// ������յĺ���
void CalculateAmbientLight(Vertex_VCN *pVertices, int num_vertices);
void CalculateDirectionalLight(Vertex_VCN *pVertices, int num_vertices);

void ConvertToDX9(Vertex_VCN g_quad_in[], Vertex_DX9 g_quad_out[], int num_vertices);
