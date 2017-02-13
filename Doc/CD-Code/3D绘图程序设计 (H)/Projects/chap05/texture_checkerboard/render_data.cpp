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
// ���ε�4������
// Position, Texcoord
Vertex_VT g_Quad[4] =
{
	{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}},
	{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}},
	{{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f}},
	{{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f}}
};
