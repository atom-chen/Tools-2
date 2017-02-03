#include <stdio.h>
#include <conio.h>

#include "Gut.h"
#include "GutInput.h"
#include "GutTimer.h"

#include "render_dx9.h"
#include "render_dx10.h"
#include "render_opengl.h"
#include "render_data.h"

GutTimer g_Timer;

void GetUserInput(void)
{
	// `��ȡ���`
	GutMouseInfo mouse;
	GutReadMouse(&mouse);
	// `��ȡ����`
	char keyboard_state[256];
	GutReadKeyboard(keyboard_state);
	// `����Ŀǰ��ͷ����`
	Vector4 facing = g_lookat - g_eye;
	// `ȷ�����Ǹ���λ����`
	facing.Normalize(); 
	// `��û���ǰһ�����浽������������ʱ��`
	float time_diff = g_Timer.Stop();
	g_Timer.Restart();

	float moving_speed = 2.0f * time_diff;
	float rotation_speed = 1.0 * time_diff;
	float ry = 0.0f;

	// `������, ����ת��ͷ.`
	if ( mouse.button[0] ) 
		ry = mouse.x * rotation_speed;
	// `����A���߷����<-, ������.`
	if ( keyboard_state[GUTKEY_A] || keyboard_state[GUTKEY_LEFT] )
		ry = -rotation_speed;
	// `����D���߷����->, ������.`
	if ( keyboard_state[GUTKEY_D] || keyboard_state[GUTKEY_RIGHT] )
		ry = rotation_speed;
	
	if ( ry )
	{
		// `�Ȼ��һ����ת����`
		Matrix4x4 rotate_matrix;
		rotate_matrix.RotateY_Replace(-ry);
		// `��ԭ���ķ�����Y����תry��, ����µķ���.`
		facing = facing * rotate_matrix;
	}

	// `����W���������`
	if ( keyboard_state[GUTKEY_W] || keyboard_state[GUTKEY_UP] )
	{
		// `��ͷ��ǰ�ƶ�`
		g_eye += facing * moving_speed; 
	}

	// `����S���������`
	if ( keyboard_state[GUTKEY_S] || keyboard_state[GUTKEY_DOWN] )
	{
		// `��ͷ����ƶ�`
		g_eye -= facing * moving_speed; 
	}

	// `�������ͷ��׼�ĵ�, ���ɾ�ͷת������ʱ���õ�.`
	g_lookat = g_eye + facing; 
}

void main(int argc, char *argv[])
{
	// Ĭ��ʹ��DirectX 9����ͼ
	char *device = "dx9";
	void (*render)(void) = RenderFrameDX9;
	bool (*init_resource)(void) = InitResourceDX9;
	bool (*release_resource)(void) = ReleaseResourceDX9;

#ifdef _ENABLE_DX10_
	printf("Press\n(1) for Direct3D9\n(2) for OpenGL\n(3) for Direct3D10\n");
#else
	printf("Press\n(1) for Direct3D9\n(2) for OpenGL\n");
#endif

	int c = getche();

	switch(c)
	{
	default:
	case '1':
		render = RenderFrameDX9;
		init_resource = InitResourceDX9;
		release_resource = ReleaseResourceDX9;
		break;
	case '2':
		device = "opengl";
		init_resource = InitResourceOpenGL;
		release_resource = ReleaseResourceOpenGL;
		render = RenderFrameOpenGL;
		break;
	case '3':
	#ifdef _ENABLE_DX10_
		device = "dx10";
		init_resource = InitResourceDX10;
		release_resource = ReleaseResourceDX10;
		render = RenderFrameDX10;
	#endif
		break;
	}

	// ��(100,100)��λ�ô�һ����СΪ(512x512)�Ĵ���
	GutCreateWindow(100, 100, 512, 512, device);

	// ��OpenGL��DirectX��ʼ��
	if ( !GutInitGraphicsDevice(device) )
	{
		printf("Failed to initialize %s device\n", device);
		exit(0);
	}

	GutInputInit();
	g_object_matrix.Identity();

	// ����shader
	if ( !init_resource() )
	{
		release_resource();
		printf("Failed to load resources\n");
		exit(0);
	}

	// ��ѭ��
	while( GutProcessMessage() )
	{
		GetUserInput();
		render();
	}
	
	// �ͷ�shader
	release_resource();

	// �ر�OpenGL/DirectX��ͼ�豸
	GutReleaseGraphicsDevice();
}
