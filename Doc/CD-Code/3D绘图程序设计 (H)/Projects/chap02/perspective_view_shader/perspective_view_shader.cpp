#include <stdio.h>

#include "Gut.h"
#include "render_dx9.h"
#include "render_dx10.h"
#include "render_opengl.h"

void main(int argc, char *argv[])
{
	// Ĭ��ʹ��DirectX 9����ͼ
	char *device = "dx9";
	void (*render)(void) = RenderFrameDX9;
	bool (*init_resource)(void) = InitResourceDX9;
	bool (*release_resource)(void) = ReleaseResourceDX9;

	if ( argc > 1 )
	{
		// ��������в���ָ����OpenGL, �͸���OpenGL.
		if ( stricmp(argv[1], "opengl")==0 )
		{
			device = "opengl";
			init_resource = InitResourceOpenGL;
			release_resource = ReleaseResourceOpenGL;
			render = RenderFrameOpenGL;
		}
		// ��������в���ָ����DX10, �͸���DX10.
		else if ( stricmp(argv[1], "dx10")==0 )
		{
		#ifdef _ENABLE_DX10_
			device = "dx10";
			init_resource = InitResourceDX10;
			release_resource = ReleaseResourceDX10;
			render = RenderFrameDX10;
		#endif // _ENABLE_DX10_
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
		render();
	}
	
	// �ͷ�shader
	release_resource();

	// �ر�OpenGL/DirectX��ͼ�豸
	GutReleaseGraphicsDevice();
}
