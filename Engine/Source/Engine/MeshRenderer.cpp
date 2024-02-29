#include "Engine.h"
#include "Engine/MeshRenderer.h"

MeshRenderer::MeshRenderer() {
		
};

MeshRenderer::~MeshRenderer() {

};

void MeshRenderer::InitMeshRenderer() {
	m_pMesh = new Mesh();
};