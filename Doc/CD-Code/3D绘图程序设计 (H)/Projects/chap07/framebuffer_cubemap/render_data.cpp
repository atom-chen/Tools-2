#include "Vector4.h"
#include "render_data.h"
#include "gut.h"
#include "GutModel.h"

// ��cubemap 6����ʱ�ľ�ͷλ�úͷ���

Vector4 g_vCubemap_Eye(0.0f, 0.0f, 0.0f);

Vector4 g_vCubemap_Up[6] =
{
	Vector4(0.0f, 1.0f, 0.0f), // +x
	Vector4(0.0f, 1.0f, 0.0f), // -x

	Vector4(0.0f, 0.0f,-1.0f), // +y
	Vector4(0.0f, 0.0f, 1.0f), // -y

	Vector4(0.0f, 1.0f, 0.0f), // +z
	Vector4(0.0f, 1.0f, 0.0f) // -z
};

Vector4 g_vCubemap_Lookat[6] =
{
	Vector4(1.0f, 0.0f, 0.0f), // +x
	Vector4(-1.0f, 0.0f, 0.0f), // -x

	Vector4(0.0f, 1.0f, 0.0f), // +y
	Vector4(0.0f,-1.0f, 0.0f), // -y

	Vector4(0.0f, 0.0f, 1.0f), // +z
	Vector4(0.0f, 0.0f,-1.0f) // -z
};

// ��ͷλ��
Vector4 g_eye(0.0f, 0.0f, 15.0f, 1.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f, 1.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, 1.0f, 0.0f, 1.0f); 
// ��ͷת������
Matrix4x4 g_view_matrix;
//
Matrix4x4 g_world_matrix;
Matrix4x4 g_scale_matrix;
//
Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix, g_mars_matrix;

// ��ͷ����
float g_fFOV = 45.0f;
// ģ��
CGutModel g_Models[4];
// controller object
CGutUserControl g_Control;

