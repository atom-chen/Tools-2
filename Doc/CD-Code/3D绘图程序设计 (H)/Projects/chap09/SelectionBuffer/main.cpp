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
	g_fFrame_Time = g_Timer.Stop();
	g_Timer.Restart();
	g_Control.Update(g_fFrame_Time, CGutUserControl::CONTROLLER_ROTATEOBJECT);
}

void frame_move(void)
{
	const float PI = 3.14159;
	const float PI_double = PI * 2.0f;
	const float days_a_year = 365.0f;
	const float days_a_month = 28.0f;
	const float earth_to_sun_distance = 2.0f; // ������̫���ļ���ֵ
	const float moon_to_earth_distance = 2.0f; // ���������ļ���ֵ
	const float simulation_speed = 60.0f; // 1���൱��60��

	static float simulation_days = 0;
	simulation_days += g_fFrame_Time * simulation_speed;
	
	// ��̫��������������ϵԭ��
	g_sun_matrix.Identity();
	// ��������λ��
	g_earth_matrix = g_sun_matrix; // �ѵ���ŵ�̫��������ϵ��
	g_earth_matrix.RotateZ( 2.0f * PI * simulation_days / days_a_year); 
	g_earth_matrix.TranslateX( earth_to_sun_distance );
	// ��������λ��
	g_moon_matrix = g_earth_matrix; // ������ŵ����������ϵ��
	g_moon_matrix.RotateZ( 2.0f * PI * simulation_days / days_a_month );
	g_moon_matrix.TranslateX( moon_to_earth_distance );
}

void main(void)
{
	// Ĭ��ʹ��DirectX 9����ͼ
	char *device = "opengl";
	void (*render)(void) = RenderFrameOpenGL;
	bool (*init_resource)(void) = InitResourceOpenGL;
	bool (*release_resource)(void) = ReleaseResourceOpenGL;
	void (*resize_func)(int width, int height) = ResizeWindowOpenGL;

	GutResizeFunc( resize_func );
	// ��(100,100)��λ�ô�һ����СΪ(512x512)�Ĵ���
	GutCreateWindow(100, 100, 512, 512, device);
	// ��OpenGL��DirectX��ʼ��
	if ( !GutInitGraphicsDevice(device) )
	{
		printf("Failed to initialize %s device\n", device);
		exit(0);
	}

	CGutModel::SetTexturePath("../../textures/");

	g_sun_model.Load_ASCII("../../models/sun.gma");
	g_earth_model.Load_ASCII("../../models/earth.gma");

	g_view_matrix.Identity();
	g_world_matrix.Identity();

	GutInputInit();

	g_Control.SetCamera(Vector4(0.0f, 5.0f, 0.0f), Vector4(0.0f), Vector4(0.0f, 0.0f, 1.0f) );

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
