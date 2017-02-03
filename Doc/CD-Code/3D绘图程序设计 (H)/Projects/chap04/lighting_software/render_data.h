#include "Vector4.h"
#include "Matrix4x4.h"

struct Vertex_VCN
{
	Vector4 m_Position; // ����λ��
	Vector4 m_Color;	// ������ɫ
	Vector4 m_Normal;	// ���㷨��
};

struct Vertex_DX9
{
	float m_Position[3];	// ����λ��
	unsigned char m_Color[4]; // ������ɫ
};

// ��������
const float g_fFovW = 45.0f;
const int	g_iMaxNumGrids = 100;
const int	g_iMaxNumGridVertices = (g_iMaxNumGrids+1) * (g_iMaxNumGrids+1);
const int	g_iMaxNumGridIndices = g_iMaxNumGrids * (g_iMaxNumGrids * 2 + 2);

// ����ģ������
extern int	g_iNumGridVertices;
extern int	g_iNumGridIndices;
extern int	g_iNumGridTriangles;
extern Vertex_VCN *g_pGridVertices;
extern Vertex_DX9 *g_pGridVerticesDX9;
extern unsigned short *g_pGridIndices;

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
extern Vector4 g_vLightAmbient;
extern Vector4 g_vLightDirection;
extern Vector4 g_vLightPosition;
extern Vector4 g_vLightColor;
extern Vector4 g_vLightAttenuation;
extern float   g_fSpotLightCutoff;
extern float   g_fSpotLightExponent;

//
void ConvertToDX9(Vertex_VCN g_quad_in[], Vertex_DX9 g_quad_out[], int num_vertices);
// ���ɸ��ӵĺ���
bool GenerateGrids(int x_grids, int y_grids, 
				   Vertex_VCN **ppVertices, int &num_vertices, 
				   unsigned short **ppIndices, int &num_indices,
				   int &num_triangles);
// �ͷŸ���ģ����Դ
bool ReleaseGridsResource(Vertex_VCN **ppVertices, unsigned short **ppIndices);
// ������յĺ���
void CalculateAmbientLight(Vertex_VCN *pVertices, int num_vertices);
void CalculateDirectionalLight(Vertex_VCN *pVertices, int num_vertices);
void CalculatePointLight(Vertex_VCN *pVertices, int num_vertices);
void CalculateSpotLight(Vertex_VCN *pVertices, int num_vertices);
