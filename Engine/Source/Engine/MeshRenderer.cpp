#include "Engine.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Shader.h"

MeshRenderer::MeshRenderer() {
		
};

MeshRenderer::~MeshRenderer() {

};

void MeshRenderer::InitMeshRenderer(ID3D12Device* device, string type) {
	SetName("mesh_renderer");
	m_pMesh = new Mesh();
	m_pMesh->InitializeMesh(device, type);
	m_pShader = new Shader();
	m_pShader->InitializeShader(device);
};