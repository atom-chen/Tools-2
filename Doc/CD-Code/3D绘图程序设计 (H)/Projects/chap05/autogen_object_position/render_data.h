#include "Vector4.h"
#include "Matrix4x4.h"

struct Vertex_V
{
	float m_Position[3]; // ����λ��
};

// ��������
const float g_fFovW = 45.0f;
// ����
extern Vertex_V g_Quad[4];
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
extern int g_iFilterMode;
extern bool g_bAnisotropic;