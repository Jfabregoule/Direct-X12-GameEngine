#pragma once
#include "Engine/Component.h"
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include <string>

class Texture;
class Shader;

class MeshRenderer : public Component {
private:

	Mesh* m_pMesh = nullptr;
	Texture* m_pTexture = nullptr;
	Shader* m_pShader = nullptr;

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

	void SetMesh(Mesh* mesh) { m_pMesh = mesh; };
	void SetTexture(Texture* texture) { m_pTexture = texture; };
	void SetShader(Shader* shader) { m_pShader = shader; };

	/*
	|---------------------------------------------------------------
	|							Methods								|
	|---------------------------------------------------------------
	*/

	void InitMeshRenderer(ID3D12Device* device);
};