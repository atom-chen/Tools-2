#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutUserControl.h"
#include "GutModel.h"

// ��ͷλ��
extern Vector4 g_eye; 
// ��ͷ��׼�ĵ�
extern Vector4 g_lookat; 
// ��ͷ���Ϸ��ķ���
extern Vector4 g_up; 
// ��ͷת������
extern Matrix4x4 g_view_matrix;
extern Matrix4x4 g_world_matrix;
extern Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix;
//
extern CGutModel g_sun_model, g_earth_model;
//
extern CGutUserControl g_Control;