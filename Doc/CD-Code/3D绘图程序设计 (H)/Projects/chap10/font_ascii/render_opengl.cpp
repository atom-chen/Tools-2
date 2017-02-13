#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "GutWin32.h"
#include "GutTexture_OpenGL.h"
#include "GutFont_OpenGL.h"

static CGutFontOpenGL g_Font;

bool InitResourceOpenGL(void)
{
	// ʹ��2D��ͼ����
	glEnable(GL_TEXTURE_2D);

	g_Font.SetFontSize(32, 32);
	g_Font.SetFontAdvance(20, 30);
	g_Font.SetConsoleSize(32, 16);
	g_Font.LoadTexture("../../textures/ascii_couriernew.tga");

	g_Font.Puts("3D Graphics", false);
	g_Font.Puts("Font Rendering Demo", false);
	g_Font.Puts("", false);
	g_Font.Puts("0123456789+-*/{}|\\", false);
	g_Font.Puts("abcdefghijklmnopqrstuvwxyz", false);
	g_Font.Puts("ABCDEFGHIJKLMNOPQRSTUVWXYZ", true);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	return true;
}

// callback function. ���ڴ�С�ı�ʱ�ᱻ����, �������µĴ��ڴ�С.
void ResizeWindowOpenGL(int width, int height)
{
	// ʹ���µĴ��ڴ�С��Ϊ�µĻ�ͼ�ֱ���
	glViewport(0, 0, width, height);
	g_Font.SetConsoleResolution(width, height);
	g_Font.BuildMesh();
}

// ʹ��OpenGL����ͼ
void RenderFrameOpenGL(void)
{
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	g_Font.Render();
	// �ѱ���backbuffer�Ļ�����ʾ����
	GutSwapBuffersOpenGL();
}
