#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutUserControl.h"

struct Vertex_VCT
{
	float m_Position[3]; // ����λ��
	unsigned char m_Color[4];
	float m_Texcoord[2]; // ��ͼ����
};

// ��������
const float g_fFovW = 45.0f;
// ����
extern Vertex_VCT g_Quad[4];
extern Vertex_VCT g_FullScreenQuad[4];
// controller object
extern CGutUserControl g_Control;
//
extern int g_iMode;
