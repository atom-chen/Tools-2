#include "Vector4.h"

// �������ε�5������
Vector4 g_vertices[5] = 
{
	Vector4(-1.0f, 1.0f,-1.0f),
	Vector4(-1.0f,-1.0f,-1.0f),
	Vector4( 1.0f,-1.0f,-1.0f),
	Vector4( 1.0f, 1.0f,-1.0f),
	Vector4( 0.0f, 0.0f, 1.0f),
};

// ���ӳ�������8�����ߵ�����ֵ
unsigned short g_indices[16] =
{
	0, 1,
	1, 2,
	2, 3,
	3, 0,
	0, 4,
	1, 4,
	2, 4,
	3, 4
};

// ��ͷλ��
Vector4 g_eye(0.0f, 3.0f, 3.0f); 
//Vector4 g_eye(0.0f, 0.0f, 10.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, -1.0f, 1.0f); 
//Vector4 g_up(0.0f, 1.0f, 0.0f); 
