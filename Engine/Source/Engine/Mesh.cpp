#include "Engine.h"
#include "Mesh.h"

Mesh::Mesh(string name)
{
	m_Name = name;
}

Mesh::~Mesh()
{
	
}

void Mesh::InitializeMesh(DirectX::XMFLOAT3 vertex1, DirectX::XMFLOAT3 vertex2, DirectX::XMFLOAT3 vertex3)
{
	m_VertexBuffer.push_back({ vertex1 });
	m_VertexBuffer.push_back({ vertex2 });
	m_VertexBuffer.push_back({ vertex3 });

	m_VertexBufferSize = sizeof(m_VertexBuffer);
}

vector<Vertex> Mesh::GetBuffer()
{
	return m_VertexBuffer;
}

UINT Mesh::GetBufferSize()
{
	return m_VertexBufferSize;
}