#include "Vector4.h"
#include "render_data.h"
#include "gut.h"

// ��ͷλ��
Vector4 g_eye(0.0f, 0.0f, 5.0f); 
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
	{{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
	{{ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
	{{-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f}},
	{{ 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f}}
};

Vertex_VT g_FullScreenQuad[4] =
{
	{{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f}},
	{{ 1.0f, -1.0f, 1.0f}, {1.0f, 1.0f}},
	{{-1.0f,  1.0f, 1.0f}, {0.0f, 0.0f}},
	{{ 1.0f,  1.0f, 1.0f}, {1.0f, 0.0f}}
};

int g_iMode = 1;

Light g_Light;
Vector4 g_vAmbientLight(0.3f, 0.3f, 0.3f, 1.0f);

// ��ȡģ�͵Ķ���
CGutModel g_Model;

bool g_bPass0 = true;
bool g_bPass1 = true;
