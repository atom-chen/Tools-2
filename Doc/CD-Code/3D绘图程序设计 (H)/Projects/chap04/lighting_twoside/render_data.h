#include "Vector4.h"
#include "Matrix4x4.h"

struct Vertex_VN
{
	float m_Position[3];	// ����λ��
	float m_Normal[3];		// ���㷨��
};

// ��������
const float g_fFovW = 45.0f;
extern Vertex_VN g_Quad[4];

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
// ��Դ����
extern Vector4 g_vGlobal_AmbientLight;
extern Vector4 g_vLightAmbient;
extern Vector4 g_vLightDirection;
extern Vector4 g_vLightDiffuse;
extern Vector4 g_vLightSpecular;
// ��������
extern Vector4 g_vMaterialAmbient;
extern Vector4 g_vMaterialDiffuse;
extern Vector4 g_vMaterialSpecular;
extern Vector4 g_vMaterialEmissive;
extern float   g_fMaterialShininess;
// ��������
extern Vector4 g_vMaterialAmbient_Back;
extern Vector4 g_vMaterialDiffuse_Back;
extern Vector4 g_vMaterialSpecular_Back;
extern Vector4 g_vMaterialEmissive_Back;
extern float   g_fMaterialShininess_Back;
