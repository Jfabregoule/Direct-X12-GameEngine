#pragma once
#include "Engine/Component.h"
#include "Engine/Mesh.h"
#include <DirectXMath.h>
#include <string>
#include "Engine/Texture.h"
#include "Engine/Shader.h"

//class Texture;
//class Shader;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                               MeshRenderer Class	                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Mesh Renderer

class ENGINE_API MeshRenderer : public Component {
private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs								        |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	Mesh* m_pMesh = nullptr;
	Texture* m_pTexture = nullptr;
	Shader* m_pShader = nullptr;

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                               Constructor/Destructor                                |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	MeshRenderer();
	~MeshRenderer();
	
#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									Getters/Setters										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Getters And Setters

	Mesh* GetMesh() { return m_pMesh; };
	Texture* GetTexture() { return m_pTexture; };
	Shader* GetShader() { return m_pShader; };

	void SetMesh(Mesh* mesh) { m_pMesh = mesh; };
	void SetTexture(Texture* texture) { m_pTexture = texture; };
	void SetShader(Shader* shader) { m_pShader = shader; };

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void InitMeshRenderer(ID3D12Device* device, string type = "null");
	void UpdateConstantBuffer(DirectX::XMMATRIX worldViewProjMatrix);

	void Update() override;

#pragma endregion

};

#pragma endregion