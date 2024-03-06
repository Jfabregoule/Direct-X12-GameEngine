#pragma once

#pragma region Includes
#include "Engine.h"
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"
#include <vector>
#pragma endregion

#pragma region Namespaces
using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma endregion 

const int _COUNT = 1;

class ENGINE_API Shader
{
private:
	#pragma region Attributes
	ID3D12Device* m_Device;

	ID3D12PipelineState* m_pspherelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_spherelineDesc;
	ID3DBlob* m_VSByteCode = nullptr;
	ID3DBlob* m_PSByteCode = nullptr;
	bool m_M4XMsaaState;
	UINT m_M4XMsaaQuality;

	ID3D12RootSignature* m_pRootSignature;
	ComPtr<ID3DBlob> m_SerializedRootSignature;
	ComPtr<ID3DBlob> m_ErrorBlob;

	HRESULT m_HResult;

	vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;
	#pragma endregion

public:
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
	* |----------------------------------------------
	* |	                    Init                     |
	* |----------------------------------------------
	*/

	Shader();
	~Shader();

	ID3D12RootSignature* GetRootSignature() {
		return m_pRootSignature;
	};

	ID3D12PipelineState* GetPipelineState(){
		return m_pspherelineState;
	};

	void InitializeShader(ID3D12Device* device);

	bool InitializePipelineState();

	bool InitializeRootSignature();

	void Update();

	HRESULT CompileShaderS(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code);
};