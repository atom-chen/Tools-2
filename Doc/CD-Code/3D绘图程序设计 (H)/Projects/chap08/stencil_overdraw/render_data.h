#include "Vector4.h"
#include "Matrix4x4.h"
#include "GutModel.h"
#include "GutUserControl.h"

struct Vertex_V
{
	Vector4 m_Position; // ����λ��
};

// controller object
extern CGutUserControl g_Control;
// model object
extern CGutModel g_Model;
// camera field of view
extern float g_fFOV;
// ����
extern Vertex_V g_Quad[4];
