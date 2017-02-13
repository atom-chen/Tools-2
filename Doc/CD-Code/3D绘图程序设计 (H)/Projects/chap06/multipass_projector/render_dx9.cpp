#include <d3dx9.h>

#include "Gut.h"
#include "GutWin32.h"
#include "GutTexture_DX9.h"
#include "GutModel_DX9.h"

#include "render_data.h"

static Matrix4x4 g_projection_matrix;

CGutModel_DX9 g_Model_DX9;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	int w, h;
	GutGetWindowSize(w, h);
	float aspect = (float) h / (float) w;
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);

	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CGutModel::SetTexturePath("../../textures/");

	for ( int t=0; t<MAX_NUM_TEXTURES; t++ )
	{
		// trilinear filter
		device->SetSamplerState(t, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(t, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		device->SetSamplerState(t, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	g_Model_DX9.ConvertToDX9Model(&g_Model);

	g_pTexture = GutLoadTexture_DX9("../../textures/nasa_stars.tga");

	return true;
}

bool ReleaseResourceDX9(void)
{
	g_Model_DX9.Release();
	SAFE_RELEASE(g_pTexture);

	return true;
}

void ResizeWindowDX9(int width, int height)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// Reset Device
	GutResetGraphicsDeviceDX9();
	// �����ӽ�ת������
	int w, h;
	GutGetWindowSize(w, h);
	float aspect = (float) h / (float) w;
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// ��ͷ����ϵ��ת������
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
}

D3DCOLOR ConvertToD3DCOLOR(Vector4 &vColor)
{
	Vector4 vColor_0_255 = vColor;
	vColor_0_255.Saturate();
	vColor_0_255 *= 255.0f;

	int r = (int) vColor_0_255.GetX();
	int g = (int) vColor_0_255.GetY();
	int b = (int) vColor_0_255.GetZ();
	int a = (int) vColor_0_255.GetW();

	D3DCOLOR d3dcolor = D3DCOLOR_ARGB(a, r, g, b);
	return d3dcolor;
}

void SetupLightingDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ���û�����
	device->SetRenderState(D3DRS_AMBIENT, ConvertToD3DCOLOR(g_vAmbientLight));
	// ���ù�Դ
	device->LightEnable(0, TRUE);

	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(light) );
	
	light.Type = D3DLIGHT_POINT;

	light.Position = *(D3DVECTOR *) &g_Light.m_Position;
	light.Diffuse = *(D3DCOLORVALUE*) &g_Light.m_Diffuse;
	light.Specular = *(D3DCOLORVALUE*) &g_Light.m_Specular;
	light.Range = 1000.0f;

	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	device->SetLight(0, &light);

}

// `ʹ��Direct3D9����ͼ`
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

	// `��ʼ�»�ͼָ��`
	device->BeginScene(); 

	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);

	{
		// `�������������`
		device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
		device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);

		SetupLightingDX9();
		if ( g_bPass0 )
			g_Model_DX9.Render();
	}

	{
		// `ͶӰ��`
		sModelMaterial_DX9 material;
		material.m_bBlend = true;
		material.m_DestBlend = D3DBLEND_ONE;
		material.m_SrcBlend = D3DBLEND_ONE;
		material.m_pTextures[0] = g_pTexture;
		// `ʹ����ͼ����ɫ���ģʽ`
		material.Submit();

		// `ʹ���Զ�������ͼ���깦��`
		device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// `����ͼ�������ת������`
		device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT4 | D3DTTFF_PROJECTED);
		device->SetSamplerState(0,  D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		device->SetSamplerState(0,  D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		//device->SetSamplerState(0,  D3DSAMP_ADDRESSW, D3DTADDRESS_BORDER);

		// `������ͼ�������`
		Vector4 vLightPos = g_Light.m_Position;
		Vector4 vLightUp(0.0f, 1.0f, 0.0f);
		Vector4 vLightLookat = g_Light.m_LookAt;

		// `��ͷ����ϵ�������, �Ѷ��㻹ԭ����������ϵ��.`
		Matrix4x4 inv_view = view_matrix; inv_view.FastInvert();
		// `ͶӰ��λ�õľ�ͷ����ϵת������`
		Matrix4x4 light_view_matrix = GutMatrixLookAtRH(vLightPos, vLightLookat, vLightUp);
		// `ͶӰ����ͷ��ͶӰת������`
		Matrix4x4 light_projection_matrix = GutMatrixPerspectiveRH_DirectX(30.0f, 1.0f, 0.1f, 100.0f);
		// `�� -1~1 ת���� 0~1 ��Χ�ľ���`
		Matrix4x4 uv_offset_matrix;
		uv_offset_matrix.Scale_Replace(0.5f, -0.5f, 1.0f);
		uv_offset_matrix[3].Set(0.5f, 0.5f, 0.0f, 1.0f);
		// `��˳����⼸�������������`
		Matrix4x4 texture_matrix = inv_view * light_view_matrix * light_projection_matrix * uv_offset_matrix;
		// `ʹ��`texture matrix
		device->SetTransform(D3DTS_TEXTURE0, (D3DMATRIX *)&texture_matrix);

		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		if ( g_bPass1 )
		{
			// `����0����ʹ���ο�ģ���е���������`
			g_Model_DX9.Render(0);
		}

		// `��ԭ����`
		device->SetSamplerState(0,  D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		device->SetSamplerState(0,  D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		device->SetSamplerState(0,  D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		Matrix4x4 ident_matrix = Matrix4x4::IdentityMatrix();
		device->SetTransform(D3DTS_TEXTURE0, (D3DMATRIX *)&ident_matrix);
		device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	}

	// `�������еĻ�ͼָ�������`
	device->EndScene(); 

	// `�ѱ���backbuffer�Ļ�����ʾ����`
    device->Present( NULL, NULL, NULL, NULL );
}
