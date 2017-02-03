#include "Vector4.h"
#include "render_data.h"
#include "gut.h"
#include "GutModel.h"

// ��ͷλ��
Vector4 g_eye(0.0f, 0.0f, 2.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, 1.0f, 0.0f); 
// ��ͷת������
Matrix4x4 g_view_matrix;
//
Matrix4x4 g_world_matrix;
//
Matrix4x4 g_sun_matrix, g_earth_matrix, g_moon_matrix;
//
CGutModel g_sun_model, g_earth_model;
//
CGutUserControl g_Control;