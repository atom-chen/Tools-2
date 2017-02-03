#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutModel.h"

// ��������
const float g_fFovW = 45.0f;
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
//
extern CGutModel g_Model;

void CopyVertexBuffer(void *target, sModelVertex *source, int num_vertices);
