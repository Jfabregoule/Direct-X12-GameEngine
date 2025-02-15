#pragma once

#include "Engine.h"

#include "Platform/Win32/d3dx12.h"

#include "DirectX12/MathHelper.h"
#include "DirectX12/Vertex.h"

using namespace std;
using Microsoft::WRL::ComPtr;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                     Mesh Class                                      |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Mesh Class

class ENGINE_API Mesh
{
protected:

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                     Attributs                                       |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Attributs

    string m_Name;

    Vertex*                         m_Vertices;
    UINT                            m_VertexSize;//Taille d'un vertex en octet
    UINT                            m_VerticesCount;//Nombre de vertex dans le tableau
    ID3D12Resource*                 m_VertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW        m_VertexBufferView = {};

    UINT*                           m_Indices;
    UINT                            m_IndexSize;//Taille d'un vertex en octet
    UINT                            m_IndexCount;
    ComPtr<ID3D12Resource>          m_IndicesBuffer;
    D3D12_INDEX_BUFFER_VIEW         m_IndexBufferView = {};

#pragma endregion

public:

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                               Constructor/Destructor                                |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Constructor And Destructor

    Mesh();
    ~Mesh();

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                     Initialize                                      |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Initialize

    void InitializeMesh(ID3D12Device* device, string type = "null", Vertex* vertices = nullptr);
    void CreateVertexBuffer(ID3D12Device* device);
    void CreateIndexBuffer(ID3D12Device* device);
    void CreateVertexBufferView(ID3D12Device* device);
    void CreateIndexBufferView(ID3D12Device* device);

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                 Getters/Setters                                     |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Getters And Setters

    UINT* GetVerticesSize() { return &m_VertexSize; };
    Vertex* GetVertices() { return m_Vertices; };
    ComPtr<ID3D12Resource> GetVertexBuffer() { return m_VertexBuffer; };
    D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() { return m_VertexBufferView; };

    UINT* GetIndexCount() { return &m_IndexCount; };
    UINT* GetIndices() { return m_Indices; };
    ComPtr<ID3D12Resource> GetIndicesBuffer() { return m_IndicesBuffer; };
    D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() { return m_IndexBufferView; } ;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SetVertexBufferView(D3D12_VERTEX_BUFFER_VIEW vertexBufferView) { m_VertexBufferView = vertexBufferView; };

    void SetIndexBufferView(D3D12_INDEX_BUFFER_VIEW indexBufferView) { m_IndexBufferView = indexBufferView; };

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                         Methods                                     |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Methods

    void CleanUpMeshResources();

#pragma endregion
   
};

#pragma endregion