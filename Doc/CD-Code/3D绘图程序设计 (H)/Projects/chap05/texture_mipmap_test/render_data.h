#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutUserControl.h"

struct Vertex_VT
{
	float m_Position[3]; // ����λ��
	float m_Texcoord[2]; // ��ͼ����
};

// ��������
const float g_fFovW = 45.0f;
// ����
extern Vertex_VT g_Quad[4];
// controller object
extern CGutUserControl g_Control;
//
extern int g_iFilterMode;
//
extern int g_iWidth;
extern int g_iHeight;
extern unsigned char *g_pImages[10];

bool CreateMipmapImages(void);