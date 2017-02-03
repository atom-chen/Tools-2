#include "Gut.h"
#include "render_data.h"
#include "GutModel_DX9.h"
#include "GutWin32.h"

CGutModel_DX9 g_Model_DX9;

static Matrix4x4 g_projection_matrix;

void InitStateDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
}

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFOV, 1.0f, 0.1f, 100.0f);

	InitStateDX9();

	CGutModel::SetTexturePath("../../textures/");
	g_Model_DX9.ConvertToDX9Model(&g_Model_textured);

	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// Reset Device
	GutResetGraphicsDeviceDX9();
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFOV, aspect, 0.1f, 100.0f);

	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);

	InitStateDX9();
}

// ʹ��DirectX 9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 world_matrix = g_Control.GetObjectMatrix();
	Matrix4x4 ident_matrix; ident_matrix.Identity();
	device->BeginScene(); 
	// �������
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_RGBA(30, 30, 30, 255), 1.0f, 0);
	// light position & orientation
	Vector4 light_pos(5.0f, 0.0f, 5.0f);
	Vector4 light_lookat(0.0f, 0.0f, 0.0f);
	Vector4 light_up(0.0f, 1.0f, 0.0f);
	// light matrix
	Matrix4x4 light_view = GutMatrixLookAtRH(light_pos, light_lookat, light_up);
	Matrix4x4 light_world_view = world_matrix * light_view;
	Matrix4x4 shadow_matrix;
	// ����shadow volume
	if ( g_bDirectionalLight )
	{
		g_ShadowVolume.BuildShadowVolume_DirectionalLight(light_world_view, 20.0f, true);
		shadow_matrix = light_view;
		shadow_matrix.FastInvert();
	}
	else
	{
		g_ShadowVolume.BuildShadowVolume_PointLight(light_pos, world_matrix, 20.0f, true);
		shadow_matrix.Identity();
	}
	// �����ռ��еĲ��
	{
		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &world_matrix);

		g_Model_DX9.Render();
	}
	// ����ǽ��
	{
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &ident_matrix);

		sModelMaterial_DX9 material;

		material.m_Material.Diffuse.r = 0.0f;
		material.m_Material.Diffuse.g = 0.0f;
		material.m_Material.Diffuse.b = 1.0f;
		material.m_Material.Diffuse.a = 1.0f;

		material.Submit();

		device->SetFVF(D3DFVF_XYZ);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_Quad, sizeof(Vertex_VT));
	}
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	device->SetRenderState(D3DRS_STENCILREF, 0x01);
	device->SetRenderState(D3DRS_STENCILMASK, 0xff);
	// ��Stencil Buffer�ϱ�ʾ����Ӱ����
	{
		sModelMaterial_DX9 material;
		material.m_bCullFace = false;
		material.Submit();
		// ʹ�þ���
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &shadow_matrix);
		// ���ö������ݸ�ʽ
		device->SetFVF(D3DFVF_XYZ);

		device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, TRUE);
		// cw stencil setting
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
		// ccw stencil setting
		device->SetRenderState(D3DRS_CCW_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_DECR);
		// disable color write
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		// ����Shadow Volume
		device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, g_ShadowVolume.m_iNumShadowVolumeFaces, g_ShadowVolume.m_pShadowVolume, sizeof(Vector4));
		// �ָ�����framebuffer
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xff);
		device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP);
	}
	// ������Ӱ
	{
		sModelMaterial_DX9 material;
		material.m_bCullFace = false;
		material.Submit();

		device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		// ʹ�þ���
		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &ident_matrix);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &ident_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &ident_matrix);
		// ֻ����stencil buffer��ֵΪ1������
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		device->SetRenderState(D3DRS_STENCILREF, 0x01);
		// ʹ�ú�ɫ�ٻ�һ��ǽ��
		device->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA(0, 0, 0,255) );
		device->SetFVF(D3DFVF_XYZ);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_FullScreenQuad, sizeof(Vertex_VT));
	}
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	// �۲�shadow volume, ������.
	if ( g_bDrawShadowVolume )
	{
		device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &shadow_matrix);

		sModelMaterial_DX9 material;
		material.m_bCullFace = false;
		material.Submit();

		device->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA(255, 255, 255, 255) );
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, g_ShadowVolume.m_iNumShadowVolumeFaces, g_ShadowVolume.m_pShadowVolume, sizeof(Vector4));
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	// �ָ�����zbuffer
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// ����ɫ��Դ��ԭΪ diffuse * texture
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	// �������еĻ�ͼָ�������
	device->EndScene(); 
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
