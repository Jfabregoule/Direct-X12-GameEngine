#pragma once

#pragma region Includes

#include "Engine.h"

#include <vector>

#include "Platform/Win32/d3dx12.h"

#include "DirectX12/MathHelper.h"

#pragma endregion

#pragma region Namespaces

using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;

#pragma endregion 

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |										Shader Class									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Shader Class

class ENGINE_API Shader
{
private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	ID3D12Device* m_Device;

	ID3D12PipelineState* m_pPipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PipelineDesc;
	ID3DBlob* m_VSByteCode = nullptr;
	ID3DBlob* m_PSByteCode = nullptr;
	bool m_M4XMsaaState;
	UINT m_M4XMsaaQuality;

	ID3D12RootSignature* m_pRootSignature;
	ComPtr<ID3DBlob> m_SerializedRootSignature = nullptr;
	ComPtr<ID3DBlob> m_ErrorBlob = nullptr;

	HRESULT m_HResult;

	vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;

	int m_rootParamSize; 
	int m_isDescTable;

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Structs											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Structs

	struct ConstantBufferStruct
	{
		XMFLOAT4X4 world;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
		XMFLOAT4X4 worldViewProjMatrix;
	};

	struct VertexPositionColor
	{
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
	};

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |								Constructor/Destructor									|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	Shader();
	~Shader();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Initialize										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Initialize

	void InitializeShader(ID3D12Device* device, std::string name = "default");

	bool InitializePipelineState();

	void InitializePipelineLayout();

	void InitializePipelineLayoutShader();

	bool InitializeRootSignatureShader();

	bool InitializeRootSignature();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									Getters/Setters										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Getters And Setters

	ID3D12RootSignature* GetRootSignature() {
		return m_pRootSignature;
	};

	ID3D12PipelineState* GetPipelineState() {
		return m_pPipelineState;
	};

	int GetRootParamSize() { return m_rootParamSize; };
	int GetIsDescTable() { return m_isDescTable; };

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void Update();

	HRESULT CompileShaderS(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code);

	std::vector<CD3DX12_STATIC_SAMPLER_DESC> GetStaticSamplers();

#pragma endregion

};

#pragma endregion