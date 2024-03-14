#include "Engine.h"

#include "Engine/MeshRenderer.h"


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
	//m_pConstantBufferGPU->Unmap(0, nullptr);
	m_pMesh = nullptr;
	m_pShader = nullptr;
	delete m_pConstantBufferData;
	delete m_pConstantBufferGPU;
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

void MeshRenderer::InitMeshRenderer(DirectX12Instance* inst, std::string type, std::string shader_type, std::string texture_name) {
	SetName("mesh_renderer");
	m_pMesh = inst->m_ListMesh.find(type)->second;
	m_pShader = inst->m_ListShader.find(shader_type)->second;
	m_pTexture = inst->m_pTextureManager->GetTextureMap()->find(texture_name)->second;

	//auto testo = CD3DX12_RESOURCE_DESC::Buffer(64);
	auto testo = CD3DX12_RESOURCE_DESC::Buffer(256);
	CD3DX12_HEAP_PROPERTIES test = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	inst->device->CreateCommittedResource(
		&test,
		D3D12_HEAP_FLAG_NONE,
		&testo,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_pConstantBufferGPU));

	m_pConstantBufferGPU->Map(0, nullptr, reinterpret_cast<void**>(&m_pConstantBufferData));

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

void MeshRenderer::UpdateConstantBuffer(DirectX::XMFLOAT4X4 worldViewProjMatrix) {

	memcpy(m_pConstantBufferData, &worldViewProjMatrix, sizeof(worldViewProjMatrix));
}

#pragma endregion