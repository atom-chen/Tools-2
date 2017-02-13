#include "Vector4.h"
#include "Matrix4x4.h"

struct Vertex_VC
{
	float m_Position[3];
	// R,G,B,A in OpenGL
	// B,G,R,A in Direct3D 9
	// Direct3D 10��������������֮1, �����ö���.
	unsigned char m_RGBA[4];
};

// �������ε�8������
extern Vertex_VC g_vertices[5];
extern unsigned short g_indices[18];

// ��ͷλ��
extern Vector4 g_eye; 
// ��ͷ��׼�ĵ�
extern Vector4 g_lookat; 
// ��ͷ���Ϸ��ķ���
extern Vector4 g_up; 

//
extern Matrix4x4 g_object_matrix;
