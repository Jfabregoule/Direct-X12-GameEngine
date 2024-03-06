#pragma once
#include "Engine/Component.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include <string>

class Texture;
class Shader;

class ENGINE_API MeshRenderer : public Component {
private:

	Mesh* m_pMesh = nullptr;
	Texture* m_pTexture = nullptr;
	Shader* m_pShader = nullptr;

	ID3D12Resource* m_pConstantBufferGPU;
	// Méthode pour initialiser le tampon de constantes sur le GPU
	CD3DX12_HEAP_PROPERTIES test = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	UINT8* m_pConstantBufferData;

public:

	MeshRenderer();
	~MeshRenderer();
	

	/*
	|---------------------------------------------------------------
	|						Getter/Setter							|
	|---------------------------------------------------------------
	*/

	Mesh* GetMesh() { return m_pMesh; };
	Texture* GetTexture() { return m_pTexture; };
	Shader* GetShader() { return m_pShader; };
	ID3D12Resource* GetConstantBufferGPU() { return m_pConstantBufferGPU;  };
	UINT8* GetConstantBufferData() { return m_pConstantBufferData; };

	void SetMesh(Mesh* mesh) { m_pMesh = mesh; };
	void SetTexture(Texture* texture) { m_pTexture = texture; };
	void SetShader(Shader* shader) { m_pShader = shader; };
	void SetConstantBufferGPU(ID3D12Resource* constantBufferGPU) { m_pConstantBufferGPU = constantBufferGPU; };
	void SetConstantBufferData(UINT8* constantBufferData) { m_pConstantBufferData = constantBufferData; };

	/*
	|---------------------------------------------------------------
	|							Methods								|
	|---------------------------------------------------------------
	*/

	void InitMeshRenderer(ID3D12Device* device, string type = "null");
	void UpdateConstantBuffer(XMMATRIX worldViewProjMatrix);
};