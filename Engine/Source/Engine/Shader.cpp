#include "Engine.h"
#include "Engine/Shader.h"
#include <d3dcompiler.h>
//#include "Engine/DirectX12Utils.h"

Shader::Shader()
{
	m_Device = nullptr;
	m_HResult = S_OK;
	m_pspherelineState = nullptr;
	m_spherelineDesc = {};
	m_M4XMsaaState = false;
	m_M4XMsaaQuality = 0;
}

Shader::~Shader()
{
}

void Shader::InitializeShader(ID3D12Device* device)
{
	m_Device = device;
	ID3DBlob* error;

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
	
	if (InitializePipelineState() == false)
	{
		OutputDebugString(L"Error Initializing spherelineState");
		return;
	}
}

bool Shader::InitializePipelineState()
{
	// Définition du layout d'entrée
	m_InputLayout.push_back(
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	);
	m_InputLayout.push_back(
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	);

	// Définition de la description de l'état du sphereline
	m_spherelineDesc.InputLayout = { m_InputLayout.data(), (UINT)m_InputLayout.size() };
	m_spherelineDesc.pRootSignature = m_pRootSignature;

	// Définition des shaders
	m_spherelineDesc.VS =
	{
		reinterpret_cast<BYTE*>(m_VSByteCode->GetBufferPointer()),
		m_VSByteCode->GetBufferSize()
	};
	m_spherelineDesc.PS =
	{
		reinterpret_cast<BYTE*>(m_PSByteCode->GetBufferPointer()),
		m_PSByteCode->GetBufferSize()
	};

	// Définition de l'état de rasterisation, de mélange et de stencil
	m_spherelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	m_spherelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	//m_spherelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	m_spherelineDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	m_spherelineDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// Définition du masque d'échantillonage et de la topologie primitive
	m_spherelineDesc.SampleMask = UINT_MAX;
	m_spherelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// Définition de la cible de rendu
	m_spherelineDesc.NumRenderTargets = 1;
	m_spherelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Initialisation de la description d'échantillonage
	m_spherelineDesc.SampleDesc.Count = m_M4XMsaaState ? 4 : 1;
	m_spherelineDesc.SampleDesc.Quality = m_M4XMsaaState ? (m_M4XMsaaQuality - 1) : 0;

	// Définition du format de vue de profondeur-stencil
	m_spherelineDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Création de l'état du sphereline
	HRESULT hr = m_Device->CreateGraphicsPipelineState(&m_spherelineDesc, IID_PPV_ARGS(&m_pspherelineState));
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


bool Shader::InitializeRootSignature()
{
	CD3DX12_ROOT_PARAMETER rootParams[_COUNT] = {};
	rootParams[0].InitAsConstantBufferView(0);

	CD3DX12_ROOT_SIGNATURE_DESC desc(_COUNT, rootParams, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

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

void Shader::Update()
{

}

HRESULT Shader::CompileShaderS(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code) 
{
	ID3DBlob* error;
	m_HResult = D3DCompileFromFile(filename, 0, 0, entrypoint, profile, D3DCOMPILE_DEBUG, 0, out_code, &error);

	return m_HResult;
}