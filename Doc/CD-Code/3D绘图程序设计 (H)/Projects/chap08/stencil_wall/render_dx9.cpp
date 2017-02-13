#include <d3dx9.h>

#include "Gut.h"
#include "GutWin32.h"
#include "GutTexture_DX9.h"

#include "render_data.h"

static LPDIRECT3DTEXTURE9 g_pTexture0 = NULL;
static LPDIRECT3DTEXTURE9 g_pTexture1 = NULL;

static Matrix4x4 g_projection_matrix;

bool InitResourceDX9(void)
{
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	// �����ӽ�ת������
	g_projection_matrix = GutMatrixOrthoRH_DirectX(g_fOrthoWidth, g_fOrthoHeight, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);

	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ������ͼ
	g_pTexture0 = GutLoadTexture_DX9("../../textures/brickwall_broken.tga");
	g_pTexture1 = GutLoadTexture_DX9("../../textures/spotlight_effect.tga");

	// trilinear
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// trilinear
	device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	return true;
}

bool ReleaseResourceDX9(void)
{
	SAFE_RELEASE(g_pTexture0);
	SAFE_RELEASE(g_pTexture1);

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	GutResetGraphicsDeviceDX9();
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	g_fOrthoWidth = g_fOrthoSize;
	g_fOrthoHeight = g_fOrthoSize;
	if ( aspect > 1.0f )
		g_fOrthoHeight *= aspect;
	else
		g_fOrthoWidth /= aspect;

	g_projection_matrix = GutMatrixOrthoRH_DirectX(g_fOrthoWidth, g_fOrthoHeight, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �����һ������ת������ͷ����ϵ�ľ���
	//device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// trilinear
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	// trilinear
	device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

// `ʹ��Direct3D9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 
	// `�������ݸ�ʽ`
	device->SetFVF(D3DFVF_XYZ|D3DFVF_TEX1); 

	{
		Matrix4x4 IdentityMatrix; 
		IdentityMatrix.Identity();
		
		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &IdentityMatrix);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &IdentityMatrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &IdentityMatrix);
		device->SetTexture(0, g_pTexture0);

		if ( g_bStencil )
		{
			// `����` Stencil Buffer Test
			device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			// `�� Stencil �ο�ֵ���� 1`
			device->SetRenderState(D3DRS_STENCILREF, 1);
			// `Stencil Test �ж��������ó���Զ����`
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
			// `ֱ�Ӱ� Stencil �ο�ֵ���� Stencil Buffer ��`
			device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		}
		else
		{
			// �ر�Stencil Buffer Test
			device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		}

		// `���� Alpha Test ����`
		device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		device->SetRenderState(D3DRS_ALPHAREF, 128);

		// `����ǽ��, ��ͬʱ����Framebuffer�ϵ���ɫ��Stencil Buffer.`
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_VT));
	}

	{
		if ( g_bStencil )
		{
			// `���� 3 �г���������ó�ֻ���»����� Stencil ֵΪ 1 ������`
			// `�� Stencil �ο�ֵ���� 1`
			device->SetRenderState(D3DRS_STENCILREF, 1);
			// `Stencil Test �ж��������óɵ��� Stencil �ο�ֵ�ų���`
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			// `Stencil Test �жϳ���ʱ������ Stencil Buffer ֵ����ȥ��������`
			device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		}

		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
		// `��ͷ����ϵת������`
		Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);
		device->SetTexture(0, g_pTexture1);
		// `�򿪻�Ϲ���`
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// `��Ϲ�ʽ` = source_color * 1 + dest_color * 1
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		// `��������`
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_VT));
		// `�ر�Alpha Test����`
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 
	// `�ѱ���backbuffer�Ļ�����ʾ����`
	device->Present( NULL, NULL, NULL, NULL );
}
