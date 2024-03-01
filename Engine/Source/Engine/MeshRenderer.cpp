#include "Engine.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Shader.h"

MeshRenderer::MeshRenderer() {
		
};

MeshRenderer::~MeshRenderer() {

};

void MeshRenderer::InitMeshRenderer(ID3D12Device* device) {
	m_pMesh = new Mesh();
	m_pMesh->InitializeMesh(device);
	m_pShader = new Shader();
};