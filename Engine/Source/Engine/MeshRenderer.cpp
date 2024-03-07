#include "Engine.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Shader.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

MeshRenderer::MeshRenderer() {
		
};

MeshRenderer::~MeshRenderer() {

};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									   Initialize 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Initialize

void MeshRenderer::InitMeshRenderer(ID3D12Device* device, string type) {
	SetName("mesh_renderer");
	m_pMesh = new Mesh();
	m_pMesh->InitializeMesh(device, type);
	m_pShader = new Shader();
	m_pShader->InitializeShader(device);

	auto testo = CD3DX12_RESOURCE_DESC::Buffer(64);
	CD3DX12_HEAP_PROPERTIES test = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	device->CreateCommittedResource(
		&test,
		D3D12_HEAP_FLAG_NONE,
		&testo,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_pConstantBufferGPU));
	

};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Methods 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Methods

void MeshRenderer::UpdateConstantBuffer(XMMATRIX worldViewProjMatrix) {

	CD3DX12_RANGE readRange(0, 0);
	m_pConstantBufferGPU->Map(0, &readRange, reinterpret_cast<void**>(&m_pConstantBufferData));

	memcpy(m_pConstantBufferData, &worldViewProjMatrix, sizeof(worldViewProjMatrix));
	m_pConstantBufferGPU->Unmap(0, nullptr);

};

#pragma endregion