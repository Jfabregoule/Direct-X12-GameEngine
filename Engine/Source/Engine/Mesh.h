#pragma once
#include "Engine.h"
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"
#include "Engine/DirectX12Utils.h"

using namespace std;
using Microsoft::WRL::ComPtr;

class ENGINE_API Mesh
{
private:

    string m_Name;

    vector<Vertex>                  m_Vertices;
    UINT                            m_VertexSize;//Taille d'un vertex en octet
    UINT                            m_VerticesCount;//Nombre de vertex dans le tableau
    ComPtr<ID3D12Resource>          m_VertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW        m_VertexBufferView = {};

    vector<UINT>                    m_Indices;
    UINT                            m_IndexSize;//Taille d'un vertex en octet
    UINT                            m_IndexCount;
    ComPtr<ID3D12Resource>          m_IndicesBuffer;
    D3D12_INDEX_BUFFER_VIEW         m_IndexBufferView = {};

public:

    /*
    * |----------------------------------------------
    * |	                    Init                     |
    * |----------------------------------------------
    */

    Mesh(string name);
    ~Mesh();

    void InitializeMesh(DirectX::XMFLOAT3 vertex1, DirectX::XMFLOAT3 vertex2, DirectX::XMFLOAT3 vertex3);
    void CreateVertexBuffer(ID3D12Device* device);
    void CreateIndexBuffer(ID3D12Device* device);
    void CreateVertexBufferView(ID3D12Device* device);
    void CreateIndexBufferView(ID3D12Device* device);

    /*
    * |----------------------------------------------
    * |	               Getters/Setter                |
    * |----------------------------------------------
    */

    UINT* GetVerticesSize() { return &m_VertexSize; };
    vector<Vertex>* GetVertices() { return &m_Vertices; };
    ComPtr<ID3D12Resource> GetVertexBuffer() { return m_VertexBuffer; };
    D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() { return m_VertexBufferView; };

    UINT* GetIndexCount() { return &m_IndexCount; };
    vector<UINT>* GetIndices() { return &m_Indices; };
    ComPtr<ID3D12Resource> GetIndicesBuffer() { return m_IndicesBuffer; };
    D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() { return m_IndexBufferView; } ;

    //////////////////////////////////////////////////////////////////////////////////

    void AddVertices(Vertex vertices) { m_Vertices.push_back(vertices); m_VerticesCount++;};
    void SetVertexBufferView(D3D12_VERTEX_BUFFER_VIEW vertexBufferView) { m_VertexBufferView = vertexBufferView; };

    void AddIndices(UINT indice) { m_Indices.push_back(indice); m_IndexCount++;};
    void SetIndexBufferView(D3D12_INDEX_BUFFER_VIEW indexBufferView) { m_IndexBufferView = indexBufferView; };

    /*
      * |----------------------------------------------
      * |	               Methods                     |
      * |----------------------------------------------
      */

    const Vertex* ConvertVertexConst(vector<Vertex> vertices);
    const UINT* ConvertIndexConst(vector<UINT> index);
    
};