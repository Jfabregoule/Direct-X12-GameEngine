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
	m_Vertices.push_back({ vertex1 });
    m_Vertices.push_back({ vertex2 });
    m_Vertices.push_back({ vertex3 });

	m_VerticesSize = sizeof(m_Vertices);
}

UINT* Mesh::GetVerticesSize()
{
	return &m_VerticesSize;
}

vector<Vertex>* Mesh::GetVertices()
{
    return &m_Vertices;
}