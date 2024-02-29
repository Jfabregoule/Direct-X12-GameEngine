#pragma once
#include "Engine.h"
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"

//using namespace std;

#ifndef Vertex

struct Vertex {
    DirectX::XMFLOAT3 position;
};

#endif

class ENGINE_API Mesh
{
private:

    string m_Name;

    vector<Vertex> m_Vertices;

    UINT m_VerticesSize;

public:

    Mesh(string name);

    ~Mesh();

    void InitializeMesh(DirectX::XMFLOAT3 vertex1, DirectX::XMFLOAT3 vertex2, DirectX::XMFLOAT3 vertex3);

    UINT* GetVerticesSize();

    vector<Vertex>* GetVertices();
};