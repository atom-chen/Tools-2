#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutModel.h"
#include "GutUserControl.h"

// camera fox
extern float g_fFOV;
// model object
extern CGutModel g_Models[4];
// controller object
extern CGutUserControl g_Control;
extern float g_mirror_z;
// ����cubemapʱ�ľ�ͷλ��
extern Vector4 g_vCubemap_Eye;
extern Vector4 g_vCubemap_Lookat[6];
extern Vector4 g_vCubemap_Up[6];
// ��ͷλ��
extern Vector4 g_eye; 
// ��ͷ��׼�ĵ�
extern Vector4 g_lookat; 
// ��ͷ���Ϸ��ķ���
extern Vector4 g_up; 
// ��ͷת������
extern Matrix4x4 g_view_matrix;
extern Matrix4x4 g_scale_matrix;
extern Matrix4x4 g_world_matrix;
// 
extern Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix, g_mars_matrix;
