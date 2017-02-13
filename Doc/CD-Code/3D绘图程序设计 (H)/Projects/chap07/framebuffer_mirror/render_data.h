#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutModel.h"
#include "GutUserControl.h"

struct Vertex_VC
{
	float m_Position[3];
	// R,G,B,A in OpenGL
	// B,G,R,A in Direct3D 9
	// Direct3D 10可是是两种其中之1, 看设置而定.
	unsigned char m_RGBA[4];
};

struct Vertex_VT
{
	Vector4 m_Position; // 顶点位置
	Vector4 m_Texcoord; // 贴图坐标
};

//
extern CGutModel g_Model;
// controller object
extern CGutUserControl g_Control;

extern float g_fFOV;

extern float g_mirror_z;
// 矩形
extern Vertex_VT g_Quad[4];

// 球的数据
extern Vertex_VC *g_pSunVertices;
extern Vertex_VC *g_pEarthVertices;
extern Vertex_VC *g_pMoonVertices;
extern unsigned short *g_pSphereIndices;

extern int g_iNumSphereVertices;
extern int g_iNumSphereTriangles;
extern int g_iNumSphereIndices;

// 镜头位置
extern Vector4 g_eye; 
// 镜头对准的点
extern Vector4 g_lookat; 
// 镜头正上方的方向
extern Vector4 g_up; 
// 镜头转换矩阵
extern Matrix4x4 g_view_matrix;

extern Matrix4x4 g_world_matrix;
// 
extern Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix;

// 生成球模型的程序
bool CreateSphere(float radius, Vertex_VC **ppVertices, unsigned short **ppIndices, float *color=NULL, int stacks = 20, int pieces = 20);
