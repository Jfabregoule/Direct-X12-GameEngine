#pragma once
#include "DirectX12Utils.h"

using namespace std;

class ENGINE_API Mesh
{
private:

	string m_Name;

	vector<Vertex> m_VertexBuffer;

	UINT m_VertexBufferSize;

public:

	Mesh(string name);

	~Mesh();

	void InitializeMesh(DirectX::XMFLOAT3 vertex1, DirectX::XMFLOAT3 vertex2, DirectX::XMFLOAT3 vertex3);

	vector<Vertex> GetBuffer();

	UINT GetBufferSize();
};