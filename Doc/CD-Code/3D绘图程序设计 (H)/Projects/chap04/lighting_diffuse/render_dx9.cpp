#include "Gut.h"
#include "render_data.h"

bool InitResourceDX9(void)
{
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �����ӽ�ת������
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &view_matrix);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

void ResizeWindowDX9(int width, int height)
{
	GutResetGraphicsDeviceDX9();
	// ͶӰ����, ����ˮƽ�ʹ�ֱ������ӽ�.
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	// ���Direct3D 9�豸
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// ��������ͷ����������
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
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
	// `���Direct3D9�豸`
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	
	// `�򿪹��չ���`
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	// `���û�����`
	device->SetRenderState(D3DRS_AMBIENT, ConvertToD3DCOLOR(g_vGlobal_AmbientLight));
	// `ָ��Diffuse�����������Դ, ������Ϊ��SetMaterial������������.`
	device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// `���ö�������ķ�������`
	D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(mtrl) );
	mtrl.Ambient = *(D3DCOLORVALUE*) &g_vMaterialAmbient;
	mtrl.Diffuse = *(D3DCOLORVALUE*) &g_vMaterialDiffuse;
	mtrl.Specular = *(D3DCOLORVALUE*) &g_vMaterialSpecular;
	mtrl.Emissive = *(D3DCOLORVALUE*) &g_vMaterialEmissive;
	// `ͨ������SetMaterial����������`
	device->SetMaterial(&mtrl);
	// `���ù�Դ`
	for ( int i=0; i<g_iNumLights; i++ )
	{
		if ( g_Lights[i].m_bEnabled )
		{
			// `����յ��`
			device->LightEnable(i, TRUE);
			// `D3D9ͨ������D3DLIGHT9 struct�����ù�Դ����`
			D3DLIGHT9 light;
			ZeroMemory( &light, sizeof(light) );

			switch(g_Lights[i].m_eType)
			{
			case LIGHT_DIRECTIONAL:
				// `���óɷ����`
				light.Type = D3DLIGHT_DIRECTIONAL;
				// `���÷���`
				light.Direction = *(D3DVECTOR *) &g_Lights[i].m_vDirection;	
				break;
			case LIGHT_POINT:
				// `���óɵ��Դ`
				light.Type = D3DLIGHT_POINT;
				// `����λ��`
				light.Position = *(D3DVECTOR *) &g_Lights[i].m_vPosition;
				// `������˥��ֵ`
				// 1/(CONSTANT+LINEAR*d+QUADRATIC*d^2)
				// `��ʽ�е�CONSTANT, LINEAR, QUADRATICֵ`
				light.Attenuation0 = g_Lights[i].m_vAttenuation[0];
				light.Attenuation1 = g_Lights[i].m_vAttenuation[1];
				light.Attenuation2 = g_Lights[i].m_vAttenuation[2];
				break;
			case LIGHT_SPOT:
				// `���óɾ۹��`
				light.Type = D3DLIGHT_SPOT;
				// `����λ��`
				light.Position = *(D3DVECTOR *) &g_Lights[i].m_vPosition;
				// `���÷���`
				light.Direction = *(D3DVECTOR *) &g_Lights[i].m_vDirection;	
				// `������˥��ֵ`
				// 1/(CONSTANT+LINEAR*d+QUADRATIC*d^2)
				// `��ʽ�е�CONSTANT, LINEAR, QUADRATICֵ`
				light.Attenuation0 = g_Lights[i].m_vAttenuation[0];
				light.Attenuation1 = g_Lights[i].m_vAttenuation[1];
				light.Attenuation2 = g_Lights[i].m_vAttenuation[2];
				// `����Բ׶��һ��Ƕ�`
				light.Phi = FastMath::DegreeToRadian(g_Lights[i].m_fSpotlightCutoff);
				// `Inner Cone�ĽǶ�, Inner Cone�ڲ�û�нǶ�˥��.`
				light.Theta = FastMath::DegreeToRadian(g_Lights[i].m_fSpotLightInnerCone);
				// `�����ĽǶ�˥��ֵ`
				light.Falloff = g_Lights[i].m_fSpotlightExponent;
				break;
			}
			// `��Դ��Ambientֵ`
			light.Ambient = *(D3DCOLORVALUE*) &g_Lights[i].m_vAmbientColor;
			// `��Դ��Diffuseֵ`
			light.Diffuse = *(D3DCOLORVALUE*) &g_Lights[i].m_vDiffuseColor;
			// `��Դ��Ч��Χ, �ڴ˰������óɸ��������ݼƵ����ֵ.`
			light.Range = 1000.0f;
			// `��SetLight�����ù�Դ����`
			device->SetLight(i, &light);
		}
		else
		{
			// `�ر���յ��`
			device->LightEnable(i, FALSE);
		}
	}
}

// ʹ��DirectX 9����ͼ
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// �������
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	// ��ʼ�»�ͼָ��
	device->BeginScene(); 
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_world_matrix);
	// ���ù�Դ
	SetupLightingDX9();
	// �������ݸ�ʽ
	device->SetFVF(D3DFVF_XYZ|D3DFVF_NORMAL);
	// ��������
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, g_iNumGridVertices, g_iNumGridTriangles, 
		g_pGridIndices, D3DFMT_INDEX16, g_pGridVertices, sizeof(Vertex_V3N3) );
	// �������еĻ�ͼָ�������
	device->EndScene(); 
	// �ѱ���backbuffer�Ļ�����ʾ����
    device->Present( NULL, NULL, NULL, NULL );
}
