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
extern Vertex_VC g_pyramid_vertices[5];
// 
extern unsigned short g_pyramid_trianglefan_indices[6];

extern unsigned short g_pyramid_trianglelist_indices[12];

extern Vertex_VC g_road_vertices[4];

extern unsigned short g_road_trianglestrip_indices[4];

// ��ͼ
extern char g_map[8][8];


// ��ͷλ��
extern Vector4 g_eye; 
// ��ͷ��׼�ĵ�
extern Vector4 g_lookat; 
// ��ͷ���Ϸ��ķ���
extern Vector4 g_up; 

//
extern Matrix4x4 g_object_matrix;
