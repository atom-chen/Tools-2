#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutUserControl.h"

struct Vertex_VC
{
	float m_Position[3];
	// R,G,B,A in OpenGL
	// B,G,R,A in Direct3D 9
	// Direct3D 10��������������֮1, �����ö���.
	unsigned char m_RGBA[4];
};

struct Vertex_VT
{
	float m_Position[3]; // ����λ��
	float m_Texcoord[2]; // ��ͼ����
};

// ����
extern Vertex_VT g_Quad[4];
extern Vertex_VT g_Quad_Inv[4];

// �������
extern Vertex_VC *g_pSunVertices;
extern Vertex_VC *g_pEarthVertices;
extern Vertex_VC *g_pMoonVertices;
extern unsigned short *g_pSphereIndices;

extern int g_iNumSphereVertices;
extern int g_iNumSphereTriangles;
extern int g_iNumSphereIndices;
//
extern Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix;
//
extern float g_fFOV;
// controller object
extern CGutUserControl g_Control;

// ������ģ�͵ĳ���
bool CreateSphere(float radius, Vertex_VC **ppVertices, unsigned short **ppIndices, float *color=NULL, int stacks = 20, int pieces = 20);
