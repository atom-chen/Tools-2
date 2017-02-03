#include <stdio.h>
#include "Gut.h"
#include "Vector4.h"

void RenderFrameDX9(void);
void RenderFrameOpenGL(void);

void main(int argc, char *argv[])
{
	// Ĭ��ʹ��DirectX 9����ͼ
	char *device = "dx9";

	if ( argc > 1 )
	{
		// ��������в���ָ����OpenGL, �͸���OpenGL.
		if ( stricmp(argv[1], "opengl")==0 )
		{
			device = "opengl";
		}
	}

	// ��(100,100)��λ�ô�һ����СΪ(512x512)�Ĵ���
	GutCreateWindow(100, 100, 512, 512, device);

	// ��OpenGL��DirectX��ʼ��
	if ( !GutInitGraphicsDevice(device) )
	{
		printf("Failed to initialize %s device\n", device);
		exit(0);
	}

	// ��ѭ��
	while( GutProcessMessage() )
	{
		if ( !strcmp(device, "dx9") )
		{
			RenderFrameDX9();
		}
		else
		{
			RenderFrameOpenGL();
		}
	}

	// �ر�OpenGL/DirectX��ͼ�豸
	GutReleaseGraphicsDevice();
}

// �������ε�8������
Vector4 g_vertices[] = 
{
	Vector4(-1.0f, 1.0f,-1.0f),
	Vector4(-1.0f,-1.0f,-1.0f),

	Vector4(-1.0f,-1.0f,-1.0f),
	Vector4( 1.0f,-1.0f,-1.0f),

	Vector4( 1.0f,-1.0f,-1.0f),
	Vector4( 1.0f, 1.0f,-1.0f),

	Vector4( 1.0f, 1.0f,-1.0f),
	Vector4(-1.0f, 1.0f,-1.0f),

	Vector4( 0.0f, 0.0f, 1.0f),
	Vector4(-1.0f, 1.0f,-1.0f),

	Vector4( 0.0f, 0.0f, 1.0f),
	Vector4(-1.0f,-1.0f,-1.0f),

	Vector4( 0.0f, 0.0f, 1.0f),
	Vector4( 1.0f,-1.0f,-1.0f),

	Vector4( 0.0f, 0.0f, 1.0f),
	Vector4( 1.0f, 1.0f,-1.0f),
};

// ��ͷλ��
Vector4 g_eye(0.0f,3.0f,3.0f); 
// ��ͷ��׼�ĵ�
Vector4 g_lookat(0.0f, 0.0f, 0.0f); 
// ��ͷ���Ϸ��ķ���
Vector4 g_up(0.0f, -1.0f, 1.0f); 

// `ʹ��Direct3D9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
    device->SetRenderState( D3DRS_LIGHTING, FALSE );
    device->Clear(
		0, NULL, // `�����������` 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // `�����ɫ��Z Buffer`
		D3DCOLOR_ARGB(0, 0, 0, 0), // `����Ҫ����ɫ��ɺ�ɫ`
		1.0f, // `����Ҫ��Zֵ��Ϊ1, Ҳ�����뾵ͷ��Զ.`
		0 // `����Ҫ��Stencil buffer��Ϊ0, �����Ƿ�����û������.`
	);
	
	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `�����һ��ʹ��͸��ͶӰ�ľ���`
	Matrix4x4 perspective_matrix = 
		GutMatrixPerspectiveRH_DirectX(90.0f, 1.0f, 1.0f, 100.0f);
	// `���������������`
	Matrix4x4 view_perspective_matrix = view_matrix * perspective_matrix;
	// `�ѿռ��е������ת������Ļ����ϵ��`
	Vector4 vertices[16];
	for ( int i=0; i<16; i++ )
	{
		vertices[i] = g_vertices[i] * view_perspective_matrix;
		vertices[i] /= vertices[i].GetW();
	}

	device->BeginScene(); // `��ʼ�»�ͼָ��`
	device->SetFVF(D3DFVF_XYZ); // `�������ݸ�ʽ`
	// `������������8������`
	device->DrawPrimitiveUP(D3DPT_LINELIST, 8, vertices, sizeof(Vector4)); 
	device->EndScene(); // `�������еĻ�ͼָ�������`
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	device->Present( NULL, NULL, NULL, NULL );
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// `�����һ������ת������ͷ����ϵ�ľ���`
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// `�����һ��͸��ͶӰ�ľ���`
	Matrix4x4 perspective_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 1.0f, 100.0f);
	// `���������������`
	Matrix4x4 view_perspective_matrix = view_matrix * perspective_matrix;
	// `�ѿռ��е������ת������Ļ����ϵ��`
	Vector4 vertices[16];
	for ( int i=0; i<16; i++ )
	{
		vertices[i] = g_vertices[i] * view_perspective_matrix;
		vertices[i] /= vertices[i].GetW();
	}
	// `������������8������`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(Vector4), vertices);
	glDrawArrays(GL_LINES, 0, 16);
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}