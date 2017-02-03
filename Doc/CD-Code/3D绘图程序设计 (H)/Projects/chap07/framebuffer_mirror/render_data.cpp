#include "Vector4.h"
#include "render_data.h"
#include "gut.h"
#include "GutModel.h"

CGutModel g_Model;
// controller object
CGutUserControl g_Control;

// ��ͷλ��
Vector4 g_eye(7.0f, 0.0f, 7.0f, 1.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f, 1.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, 1.0f, 0.0f, 1.0f); 
// ��ͷת������
Matrix4x4 g_view_matrix;
//
Matrix4x4 g_world_matrix;
//
Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix;
// ���ε�4������
// Position, Texcoord
float g_fFOV = 45.0f;

float g_mirror_z = -2.0f;
const float mirror_size_half = 2.0f;

Vertex_VT g_Quad[4] =
{
	{Vector4(-mirror_size_half, -mirror_size_half, g_mirror_z), Vector4(0.0f, 1.0f, 0.0f, 0.0f)},
	{Vector4( mirror_size_half, -mirror_size_half, g_mirror_z), Vector4(1.0f, 1.0f, 0.0f, 0.0f)},
	{Vector4(-mirror_size_half,  mirror_size_half, g_mirror_z), Vector4(0.0f, 0.0f, 0.0f, 0.0f)},
	{Vector4( mirror_size_half,  mirror_size_half, g_mirror_z), Vector4(1.0f, 0.0f, 0.0f, 0.0f)}
};

