#include "Gut.h"
#include "render_data.h"
#include "GutModel_DX9.h"
#include "GutWin32.h"

CGutModel_DX9 g_Model_DX9;

static Matrix4x4 g_projection_matrix;
static Matrix4x4 g_mirror_view_matrix;

void InitStateDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	// �رչ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ʹ��trilinear
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	g_projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFOV, 1.0f, 0.1f, 100.0f);

	InitStateDX9();

	CGutModel::SetTexturePath("../../textures/");
	g_Model_DX9.ConvertToDX9Model(&g_Model);

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
	DWORD FogColor = D3DCOLOR_RGBA(128, 128, 128, 255);

	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	device->BeginScene(); 
	// �������
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, FogColor, 1.0f, 0);
	// ����ת������
	Matrix4x4 view_matrix = g_Control.GetViewMatrix();
	Matrix4x4 object_matrix = g_Control.GetObjectMatrix();

	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &g_projection_matrix);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &object_matrix);
	// ������
	device->SetRenderState(D3DRS_FOGENABLE, TRUE);
	device->SetRenderState(D3DRS_FOGCOLOR, FogColor);

	switch(g_iFogMode)
	{
	case 0:
		device->SetRenderState(D3DRS_FOGENABLE, FALSE);
		break;
	case 1:
		{
			// ��������Ա�Ũ����
			float fStart = 0.0f;
			float fEnd = 10.0f;
			device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
			device->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&fStart));
			device->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&fEnd));
			// ���㹫ʽΪ
			// (fog_end - distance_to_camera) / (fog_end - fog_start)
			break;
		}
	case 2:
		{
			// `ʹ��ָ���������仯���� `
			float fFogDensity = 0.5f;
			device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_EXP);
			device->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)&fFogDensity);
			// ���㹫ʽΪ
			// power(e, -(fog_density * distance_to_camera))
			break;
		}
	case 3:
		{
			// `ʹ��ָ���������仯���� `
			float fFogDensity = 0.5f;
			device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_EXP2);
			device->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)&fFogDensity);
			// ���㹫ʽΪ
			// power(e, -(fog_density * distance_to_camera)^2)
			break;
		}
	}
	// ����ģ��
	g_Model_DX9.Render();
	// �������еĻ�ͼָ�������
	device->EndScene(); 
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
