#include "Engine.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Shader.h"

MeshRenderer::MeshRenderer() {
		
};

MeshRenderer::~MeshRenderer() {

};

void MeshRenderer::InitMeshRenderer() {
	m_pMesh = new Mesh();
	m_pShader = new Shader();
};