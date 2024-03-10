#include "Engine.h"
#include "Engine/Shader.h"
#include <d3dcompiler.h>

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

Shader::Shader()
{
	m_Device = nullptr;
	m_HResult = S_OK;
	m_pPipelineState = nullptr;
	m_PipelineDesc = {};
	m_M4XMsaaState = false;
	m_M4XMsaaQuality = 0;
}

Shader::~Shader()
{
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									  Initialize 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Initialize

void Shader::InitializeShader(ID3D12Device* device, std::string name)
{
	m_Device = device;
	ID3DBlob* error;

	

	//Deux shaders différents
	if (name == "default") {

		m_HResult = CompileShaderS(L".\\Content\\Shaders\\shader.hlsl", "vs_main", "vs_5_0", &m_VSByteCode);
		if (m_HResult != S_OK)
		{
			OutputDebugString(L"Error Compiling Shader");
			return;
		}

		m_HResult = CompileShaderS(L".\\Content\\Shaders\\shader.hlsl", "ps_main", "ps_5_0", &m_PSByteCode);
		if (m_HResult != S_OK)
		{
			OutputDebugString(L"Error Compiling Shader");
			return;
		}

		if (InitializeRootSignature() == false)
		{
			OutputDebugString(L"Error Initializing RootSignature");
			return;
		}
		InitializePipelineLayout();
	}
	else if (name == "textured") {

		m_HResult = CompileShaderS(L".\\Content\\Shaders\\shaderTexture.hlsl", "vs_main", "vs_5_0", &m_VSByteCode);
		if (m_HResult != S_OK)
		{
			OutputDebugString(L"Error Compiling Shader");
			return;
		}

		m_HResult = CompileShaderS(L".\\Content\\Shaders\\shaderTexture.hlsl", "ps_main", "ps_5_0", &m_PSByteCode);
		if (m_HResult != S_OK)
		{
			OutputDebugString(L"Error Compiling Shader");
			return;
		}

		if (InitializeRootSignatureShader() == false)
		{
			OutputDebugString(L"Error Initializing RootSignature");
			return;
		}
		InitializePipelineLayoutShader();
	}


	if (InitializePipelineState() == false)
	{
		OutputDebugString(L"Error Initializing PipelineState");
		return;
	}
}

bool Shader::InitializePipelineState()
{

	// Définition de la description de l'état du pipeline
	m_PipelineDesc.InputLayout = { m_InputLayout.data(), (UINT)m_InputLayout.size() };
	m_PipelineDesc.pRootSignature = m_pRootSignature;

	// Définition des shaders
	m_PipelineDesc.VS =
	{
		reinterpret_cast<BYTE*>(m_VSByteCode->GetBufferPointer()),
		m_VSByteCode->GetBufferSize()
	};
	m_PipelineDesc.PS =
	{
		reinterpret_cast<BYTE*>(m_PSByteCode->GetBufferPointer()),
		m_PSByteCode->GetBufferSize()
	};

	// Définition de l'état de rasterisation, de mélange et de stencil
	m_PipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	m_PipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	m_PipelineDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	m_PipelineDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// Définition du masque d'échantillonage et de la topologie primitive
	m_PipelineDesc.SampleMask = UINT_MAX;
	m_PipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// Définition de la cible de rendu
	m_PipelineDesc.NumRenderTargets = 1;
	m_PipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Initialisation de la description d'échantillonage
	m_PipelineDesc.SampleDesc.Count = m_M4XMsaaState ? 4 : 1;
	m_PipelineDesc.SampleDesc.Quality = m_M4XMsaaState ? (m_M4XMsaaQuality - 1) : 0;

	// Définition du format de vue de profondeur-stencil
	m_PipelineDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Création de l'état du pipeline
	HRESULT hr = m_Device->CreateGraphicsPipelineState(&m_PipelineDesc, IID_PPV_ARGS(&m_pPipelineState));
	
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void Shader::InitializePipelineLayout() {
	// Définition du layout d'entrée
	m_InputLayout.push_back(
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	);
	m_InputLayout.push_back(
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	);
}

void Shader::InitializePipelineLayoutShader() {
	// Définition du layout d'entrée
	m_InputLayout.push_back(
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	);
	m_InputLayout.push_back(
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	);
	m_InputLayout.push_back(
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 } //28 ou 24 jsp
	);
}

bool Shader::InitializeRootSignatureShader()
{

	CD3DX12_DESCRIPTOR_RANGE descRange;//Safe
	descRange.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);//Safe
	CD3DX12_ROOT_PARAMETER rootParams[2] = {};//Safe
	rootParams[0].InitAsDescriptorTable(1, &descRange, D3D12_SHADER_VISIBILITY_PIXEL);//Safe
	rootParams[1].InitAsConstantBufferView(0);//Safe

	auto staticSamplers = GetStaticSamplers();//Safe

	CD3DX12_ROOT_SIGNATURE_DESC desc(2, rootParams, staticSamplers.size(), staticSamplers.data(), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);//Safe

	/* Serialize the root signature */
	m_HResult = D3D12SerializeRootSignature(
		&desc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		m_SerializedRootSignature.GetAddressOf(),
		m_ErrorBlob.GetAddressOf()
	);
	if (m_HResult != S_OK)
	{
		return false;
	}

	/* Creating the Root Signature */
	m_HResult = m_Device->CreateRootSignature(
		0,
		m_SerializedRootSignature->GetBufferPointer(),
		m_SerializedRootSignature->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature)
	);
	if (m_HResult != S_OK)
	{
		return false;
	}
	
	m_SerializedRootSignature->Release();
	if (m_ErrorBlob) m_ErrorBlob->Release();

	return true;

}

bool Shader::InitializeRootSignature()
{
	CD3DX12_ROOT_PARAMETER rootParams[1] = {};
	rootParams[0].InitAsConstantBufferView(0);

	CD3DX12_ROOT_SIGNATURE_DESC desc(1, rootParams, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	/* Serialize the root signature */
	m_HResult = D3D12SerializeRootSignature(
		&desc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		m_SerializedRootSignature.GetAddressOf(),
		m_ErrorBlob.GetAddressOf()
	);
	if (m_HResult != S_OK)
	{
		return false;
	}

	/* Creating the Root Signature */
	m_HResult = m_Device->CreateRootSignature(
		0,
		m_SerializedRootSignature->GetBufferPointer(),
		m_SerializedRootSignature->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature)
	);
	if (m_HResult != S_OK)
	{
		return false;
	}
	return true;
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Methods 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Methods

void Shader::Update()
{

}

HRESULT Shader::CompileShaderS(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code) 
{
	ID3DBlob* error;
	m_HResult = D3DCompileFromFile(filename, 0, 0, entrypoint, profile, D3DCOMPILE_DEBUG, 0, out_code, &error);

	return m_HResult;
}

std::vector<CD3DX12_STATIC_SAMPLER_DESC> Shader::GetStaticSamplers()
{
	std::vector<CD3DX12_STATIC_SAMPLER_DESC> samplers;

	samplers.emplace_back(
		0,                                  // Register
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,    // Filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,    // AddressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,    // AddressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,    // AddressW
		0.0f,                               // MipLODBias
		8,                                  // MaxAnisotropy
		D3D12_COMPARISON_FUNC_LESS_EQUAL,   // ComparisonFunc
		D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE, // BorderColor
		0.0f,                               // MinLOD
		D3D12_FLOAT32_MAX,                  // MaxLOD
		D3D12_SHADER_VISIBILITY_ALL);

	return samplers;
}

#pragma endregion