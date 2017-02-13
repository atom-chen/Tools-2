#include <stdio.h>
#include "Gut.h"
#include "Vector4.h"
#include <d3dx9.h>
#include <GL/glu.h>

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

// `ʹ��DirectX9����ͼ`
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
	D3DXVECTOR3 eye(0.0f, 3.0f, 3.0f);
	D3DXVECTOR3 lookat(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, -1.0f, 1.0f);
	// `���㾵ͷת������`
	D3DXMATRIX view_matrix;
	D3DXMatrixLookAtRH(&view_matrix, &eye, &lookat, &up);
	// `���þ�ͷת������`
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix); 	

	// `����͸��ͶӰ����`
	D3DXMATRIX perspective_matrix;
	D3DXMatrixPerspectiveFovRH(&perspective_matrix, FastMath::DegreeToRadian(90.0f), 1.0f, 1.0f, 100.0f);
	// `�����ӽ�ת������`
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *)&perspective_matrix); 	

	device->BeginScene(); // `��ʼ�»�ͼָ��`
	device->SetFVF(D3DFVF_XYZ); // `�������ݸ�ʽ`
	// `������������8������`
	device->DrawPrimitiveUP(D3DPT_LINELIST, 8, g_vertices, sizeof(Vector4)); 
	device->EndScene(); // `�������еĻ�ͼָ�������`
	
	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}

// `ʹ��OpenGL����ͼ`
void RenderFrameOpenGL(void)
{
	// `�������`
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// `���㲢���þ�ͷת������`
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		g_eye[0], g_eye[1], g_eye[2],
		g_lookat[0], g_lookat[1], g_lookat[2],
		g_up[0], g_up[1], g_up[2]);
	// `���㲢�����ӽ�ת������`
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 100.0f);

	// `������������8������`
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(Vector4), g_vertices);
	glDrawArrays(GL_LINES, 0, 16);

	// `�ѱ���backbuffer�Ļ�����ʾ����`
	GutSwapBuffersOpenGL();
}
