#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutModel.h"

struct Vertex_VT
{
	float m_Position[3]; // ����λ��
	float m_Texcoord[2]; // ��ͼ����
};

struct Light
{
	Vector4 m_Position;
	Vector4 m_LookAt;
	Vector4 m_Diffuse;
	Vector4 m_Specular;
};

extern Light g_Light;
extern Vector4 g_vAmbientLight;

extern bool g_bPass0;
extern bool g_bPass1;

// ��������
const float g_fFovW = 45.0f;
// ����
extern Vertex_VT g_Quad[4];
extern Vertex_VT g_FullScreenQuad[4];
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
//
extern int g_iMode;
//
extern CGutModel g_Model;