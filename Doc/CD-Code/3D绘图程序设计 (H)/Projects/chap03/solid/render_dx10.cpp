#ifdef _ENABLE_DX10_

#include "Gut.h"
#include "render_data.h"

static ID3D10Device			*g_pDevice			= NULL;
static ID3D10InputLayout	*g_pVertexLayout	= NULL;
static ID3D10Buffer			*g_pVertexBuffer	= NULL;
static ID3D10Buffer			*g_pIndexBuffer		= NULL;
static ID3D10Buffer			*g_pConstantBuffer	= NULL;
static ID3D10VertexShader	*g_pVertexShader	= NULL;
static ID3D10PixelShader	*g_pPixelShader		= NULL;

static Matrix4x4 g_view_proj_matrix;

bool InitResourceDX10(void)
{
	g_pDevice = GutGetGraphicsDeviceDX10();
	ID3D10Blob *pVSCode = NULL;

	// `����Vertex Shader`
	g_pVertexShader = GutLoadVertexShaderDX10_HLSL("../../shaders/vertex_color_dx10.hlsl", "VS", "vs_4_0", &pVSCode);
	if ( NULL==g_pVertexShader )
		return false;
	// `����Pixel Shader`
	g_pPixelShader = GutLoadPixelShaderDX10_HLSL("../../shaders/vertex_color_dx10.hlsl", "PS", "ps_4_0");
	if ( NULL==g_pPixelShader )
		return false;

    // `����Vertex���ݸ�ʽ`
    D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};

    if ( D3D_OK != g_pDevice->CreateInputLayout( layout, sizeof(layout)/sizeof(D3D10_INPUT_ELEMENT_DESC), pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), &g_pVertexLayout ) )
		return false;

	SAFE_RELEASE(pVSCode);

	// ����һ�����������Vertex���ڴ�.
    D3D10_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(g_vertices);
    cbDesc.Usage = D3D10_USAGE_IMMUTABLE;
    cbDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
	// ��Vertex Bufferʱͬʱ�����ݿ�����ȥ
	D3D10_SUBRESOURCE_DATA sbDesc;
	sbDesc.pSysMem = g_vertices;
	// ����һ����Դ��Vertex���ڴ�, Ҳ����Vertex Buffer.
	if ( D3D_OK != g_pDevice->CreateBuffer( &cbDesc, &sbDesc, &g_pVertexBuffer ) )
		return false;

	// ����һ�����������Index���ڴ�.
    cbDesc.ByteWidth = sizeof(g_indices);
    cbDesc.Usage = D3D10_USAGE_IMMUTABLE;
    cbDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
	// ��Index Bufferʱͬʱ�����ݿ�����ȥ
	sbDesc.pSysMem = g_indices;
    // ����һ����Դ��Index���ڴ�, Ҳ����Index Buffer.
	if ( D3D_OK != g_pDevice->CreateBuffer( &cbDesc, &sbDesc, &g_pIndexBuffer ) )
		return false;

	// ����Shader��ȡ�������ڴ�ռ�
    cbDesc.ByteWidth = sizeof(Matrix4x4);
    cbDesc.Usage = D3D10_USAGE_DYNAMIC;
    cbDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    cbDesc.MiscFlags = 0;
	if ( D3D_OK != g_pDevice->CreateBuffer( &cbDesc, NULL, &g_pConstantBuffer ) )
		return false;
	
	// �����һ������ת������ͷ����ϵ�ľ���
	Matrix4x4 view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(60.0f, 1.0f, 1.0f, 100.0f);
	g_view_proj_matrix = view_matrix * projection_matrix;

	return true;
}

bool ReleaseResourceDX10(void)
{
 	SAFE_RELEASE(g_pVertexLayout);
 	SAFE_RELEASE(g_pVertexBuffer);
 	SAFE_RELEASE(g_pConstantBuffer);
 	SAFE_RELEASE(g_pVertexShader);
 	SAFE_RELEASE(g_pPixelShader);

	return true;
}

void RenderFrameDX10(void)
{
	Vector4 vClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	UINT stride = sizeof(Vertex_VC);
	UINT offset = 0;

	// ��õ���GutCreateGraphicsDeviceDX10ʱ�����ɵ�D3D10����
	//frame buffer
	ID3D10RenderTargetView *pRenderTargetView = GutGetDX10RenderTargetView(); 
	//depth/stencil buffer
    ID3D10DepthStencilView *pDepthStencilView = GutGetDX10DepthStencilView(); 
	// front/back buffer
	IDXGISwapChain *pSwapChain = GutGetDX10SwapChain(); 

	// �����ɫ
	g_pDevice->ClearRenderTargetView(pRenderTargetView, (float *)&vClearColor);
	// ���Depth/Stencil buffer
	g_pDevice->ClearDepthStencilView(pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
	// ����vertex shader
	g_pDevice->VSSetShader(g_pVertexShader);
	// ����pixel shader
	g_pDevice->PSSetShader(g_pPixelShader);
	// ����vertex shader��ȡ�������ڴ�λ�D
    g_pDevice->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	// ����vertex���ݸ�ʽ
	g_pDevice->IASetInputLayout(g_pVertexLayout);
	// ����vertex buffer
	g_pDevice->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
	// ����index buffer
	g_pDevice->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    // ����Ҫ����
	g_pDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	static float angle = 0.0f;
	angle += 0.01f;

	// ��������ת������
	Matrix4x4 world_view_proj_matrix = g_view_proj_matrix;
	world_view_proj_matrix.RotateZ(angle); // ������ת����

	// ����shader����
	Matrix4x4 *pConstData;
	g_pConstantBuffer->Map( D3D10_MAP_WRITE_DISCARD, NULL, (void **) &pConstData );
	*pConstData = world_view_proj_matrix;
	g_pConstantBuffer->Unmap();

	// ����
	g_pDevice->DrawIndexed(18, 0, 0);

	// �ȴ�Ӳ��ɨ�����, Ȼ���ٸ��»���
	pSwapChain->Present(1, 0);
}

#endif // _ENABLE_DX10_