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
float g_fFrame_Time = 0.0f;

void GetUserInput(void)
{
	// ��ȡ���
	GutMouseInfo mouse;
	GutReadMouse(&mouse);
	// ��ȡ����
	char keyboard_state[256];
	GutReadKeyboard(keyboard_state);
	// ��û���ǰһ�����浽������������ʱ��
	g_fFrame_Time = g_Timer.Stop();
	g_Timer.Restart();

	float moving_speed = 2.0f * g_fFrame_Time;
	float rotation_speed = 1.0 * g_fFrame_Time;

	// ������ϵͳ
	static float theta = -MATH_PI * 0.5f;
	static float phi = 0.0f;

	// ������������ת��ͷ
	if ( mouse.button[0] ) 
	{
		theta += mouse.x * rotation_speed;
		phi -= mouse.y * rotation_speed;
	}

	float sin_phi, cos_phi;
	float sin_theta, cos_theta;
	
	FastMath::SinCos(phi, sin_phi, cos_phi);
	FastMath::SinCos(theta, sin_theta, cos_theta);

	// ���㾵ͷ�ķ���
	Vector4 camera_facing;

	camera_facing[0] = cos_phi * cos_theta;
	camera_facing[1] = sin_phi;
	camera_facing[2] = cos_phi * sin_theta;

	// ���㾵ͷ���Ϸ�������
	Vector4 camera_up;
	FastMath::SinCos(phi + MATH_PI*0.5f, sin_phi, cos_phi);

	camera_up[0] = cos_phi * cos_theta;
	camera_up[1] = sin_phi;
	camera_up[2] = cos_phi * sin_theta;

	// ��þ����ҷ��ķ���
	Vector4 camera_right = Vector3CrossProduct(camera_up, camera_facing);

	// ����W���������
	if ( keyboard_state[GUTKEY_W] || keyboard_state[GUTKEY_UP] )
	{
		g_eye += camera_facing * moving_speed;
	}
	// ����S���������
	if ( keyboard_state[GUTKEY_S] || keyboard_state[GUTKEY_DOWN] )
	{
		g_eye -= camera_facing * moving_speed;
	}
	// ����A���������
	if ( keyboard_state[GUTKEY_A] || keyboard_state[GUTKEY_LEFT] )
	{
		g_eye -= camera_right * moving_speed;
	}
	// ����D���������
	if ( keyboard_state[GUTKEY_D] || keyboard_state[GUTKEY_RIGHT] )
	{
		g_eye += camera_right * moving_speed;
	}

	// �������ͷ��׼�ĵ�, ���ɾ�ͷת������ʱ���õ�.
	g_lookat = g_eye + camera_facing;
	// ��Ϊ�Ƕ�2����ת��, ��Ҫ���¾�ͷ���ϵ���
	g_up = camera_up;
}

void GetUserInputOld(void)
{
	// ��ȡ���
	GutMouseInfo mouse;
	GutReadMouse(&mouse);
	// ��ȡ����
	char keyboard_state[256];
	GutReadKeyboard(keyboard_state);
	// ��û���ǰһ�����浽������������ʱ��
	g_fFrame_Time = g_Timer.Stop();
	g_Timer.Restart();

	float moving_speed = 4.0f * g_fFrame_Time;
	float rotation_speed = 1.0 * g_fFrame_Time;

	// Ҫ�ۻ��¶�X��Y�����ת�Ƕ�
	static float ry = 0.0f;
	static float rx = 0.0f;

	// ������������ת��ͷ
	if ( mouse.button[0] ) 
	{
		ry += mouse.x * rotation_speed;
		rx -= mouse.y * rotation_speed;
	}

	Matrix4x4 rotate_matrix;
	rotate_matrix.RotateY_Replace(ry);
	rotate_matrix.RotateX(rx);
	
	// ����������ϵ��, ����ķ�����ת�������-Z��
	Vector4 camera_facing = -rotate_matrix[2];
	// ��þ����ұߵķ���
	Vector4 camera_right = rotate_matrix[0];

	// ����W���������
	if ( keyboard_state[GUTKEY_W] || keyboard_state[GUTKEY_UP] )
	{
		g_eye += camera_facing * moving_speed;
	}
	// ����S���������
	if ( keyboard_state[GUTKEY_S] || keyboard_state[GUTKEY_DOWN] )
	{
		g_eye -= camera_facing * moving_speed;
	}
	// ����A���������
	if ( keyboard_state[GUTKEY_A] || keyboard_state[GUTKEY_LEFT] )
	{
		g_eye -= camera_right * moving_speed;
	}
	// ����D���������
	if ( keyboard_state[GUTKEY_D] || keyboard_state[GUTKEY_RIGHT] )
	{
		g_eye += camera_right * moving_speed;
	}
	// �������ͷ��׼�ĵ�, ���ɾ�ͷת������ʱ���õ�.
	g_lookat = g_eye + camera_facing;
	// ��Ϊ�Ƕ�2����ת��, ��Ҫ���¾�ͷ���ϵ���
	g_up = Vector3CrossProduct(camera_right, camera_facing);
}

void frame_move(void)
{
	const float PI = 3.14159;
	const float PI_double = PI * 2.0f;
	const float days_a_year = 365.0f;
	const float days_a_month = 28.0f;
	const float earth_to_sun_distance = 8.0f; // ������̫���ļ���ֵ
	const float moon_to_earth_distance = 2.0f; // ���������ļ���ֵ
	const float simulation_speed = 60.0f; // 1���൱��60��

	static float simulation_days = 0;
	simulation_days += g_fFrame_Time * simulation_speed;
	
	// ��̫��������������ϵԭ��
	g_sun_matrix.Identity();
	// ��������λ��
	g_earth_matrix = g_sun_matrix; // �ѵ���ŵ�̫��������ϵ��
	g_earth_matrix.RotateY( 2.0f * PI * simulation_days / days_a_year); 
	g_earth_matrix.TranslateX( earth_to_sun_distance );
	// ��������λ��
	g_moon_matrix = g_earth_matrix; // ������ŵ����������ϵ��
	g_moon_matrix.RotateY( 2.0f * PI * simulation_days / days_a_month );
	g_moon_matrix.TranslateX( moon_to_earth_distance );
}

void main(void)
{
	// Ĭ��ʹ��DirectX 9����ͼ
	char *device = "dx9";
	void (*render)(void) = RenderFrameDX9;
	bool (*init_resource)(void) = InitResourceDX9;
	bool (*release_resource)(void) = ReleaseResourceDX9;
	void (*resize_func)(int width, int height) = ResizeWindowDX9;

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
		resize_func = ResizeWindowDX9;
		break;
	case '2':
		device = "opengl";
		init_resource = InitResourceOpenGL;
		release_resource = ReleaseResourceOpenGL;
		render = RenderFrameOpenGL;
		resize_func = ResizeWindowOpenGL;
		break;
#ifdef _ENABLE_DX10_
	case '3':
		device = "dx10";
		init_resource = InitResourceDX10;
		release_resource = ReleaseResourceDX10;
		render = RenderFrameDX10;
		resize_func = ResizeWindowDX10;
		break;
#endif // _ENABLE_DX10_
	}

	GutResizeFunc( resize_func );

	// ��(100,100)��λ�ô�һ����СΪ(512x512)�Ĵ���
	GutCreateWindow(100, 100, 512, 512, device);

	// ��OpenGL��DirectX��ʼ��
	if ( !GutInitGraphicsDevice(device) )
	{
		printf("Failed to initialize %s device\n", device);
		exit(0);
	}

	g_view_matrix.Identity();
	GutInputInit();

	// Sun
	float yellow[]={1.0f, 1.0f, 0.0f, 1.0f};
	CreateSphere(2.0f, &g_pSunVertices, &g_pSphereIndices, yellow);
	// Earch
	float blue[]={0.0f, 0.0f, 1.0f, 1.0f};
	CreateSphere(1.0f, &g_pEarthVertices, NULL, blue);
	// Moon
	float white[]={1.0f, 1.0f, 1.0f, 1.0f};
	CreateSphere(0.2f, &g_pMoonVertices, NULL);

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
		frame_move();
		render();
	}
	
	// �ͷ�shader
	release_resource();

	// �ر�OpenGL/DirectX��ͼ�豸
	GutReleaseGraphicsDevice();
}
