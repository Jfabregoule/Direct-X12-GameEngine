#pragma once
#include "Engine/Component.h"
#include "Engine/Mesh.h"
#include <string>

class Texture;
class Shader;

class MeshRenderer : public Component {
public:

	Mesh* m_pMesh;
	Texture* m_pTexture = nullptr;
	Shader* m_pShader = nullptr;


	MeshRenderer();

};