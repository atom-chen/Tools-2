#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutModel.h"
#include "GutUserControl.h"

struct Vertex_VT
{
	float m_Position[3]; // ����λ��
	float m_Texcoord[2]; // ��ͼ����
};

struct Light
{
	Vector4 m_Position;
	Vector4 m_Diffuse;
	Vector4 m_Specular;
};

#define NUM_LIGHTS 16
extern Light g_Lights[NUM_LIGHTS];

extern Light g_Light;
extern Vector4 g_vAmbientLight;

// ��������
const float g_fFovW = 45.0f;
// ����
extern Vertex_VT g_Quad[4];
extern Vertex_VT g_FullScreenQuad[4];
// controller object
extern CGutUserControl g_Control;
//
extern int g_iMode;
//
extern CGutModel g_Model;
//
extern int g_iSwitch;