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

    m_VertexSize = sizeof(vertex1);
	m_VerticesCount = sizeof(m_Vertices);
}

void Mesh::CreateVertexBuffer(ID3D12Device* device) {

    // Créer un tampon de ressources (vertex buffer)
    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_VertexSize * m_VerticesCount);
    device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&m_VertexBuffer)
    );

    // Remplir le tampon de ressources avec les données des vertices
    UINT8* pVertexDataBegin;
    CD3DX12_RANGE readRange(0, 0); // On ne lit pas les données actuellement, donc la plage est vide
    m_VertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    memcpy(pVertexDataBegin, ConvertVertexConst(m_Vertices), m_VertexSize * m_VerticesCount);
    m_VertexBuffer->Unmap(0, nullptr);

    return;

};

void Mesh::CreateIndexBuffer(ID3D12Device* device) {

    // Créer un tampon de ressources (index buffer)
    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_IndexCount * m_IndexSize);
    device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&m_IndicesBuffer)
    );

    // Remplir le tampon de ressources avec les données des indices
    UINT8* pIndexDataBegin;
    CD3DX12_RANGE readRange(0, 0); // On ne lit pas les données actuellement, donc la plage est vide
    m_IndicesBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
    memcpy(pIndexDataBegin, ConvertIndexConst(m_Indices), m_IndexCount * m_IndexSize);
    m_IndicesBuffer->Unmap(0, nullptr);

    return;
};

void Mesh::CreateVertexBufferView(ID3D12Device* device) 
{
 
    // Remplir la structure D3D12_VERTEX_BUFFER_VIEW
    m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress(); // Adresse virtuelle du vertex buffer
    m_VertexBufferView.SizeInBytes = m_VerticesCount * m_VertexSize; // Taille totale du vertex buffer en octets
    m_VertexBufferView.StrideInBytes = m_VertexSize; // Taille d'un vertex en octets

    return;
}

void Mesh::CreateIndexBufferView(ID3D12Device* device)
{
    // Remplir la structure D3D12_INDEX_BUFFER_VIEW
    m_IndexBufferView.BufferLocation = m_IndicesBuffer->GetGPUVirtualAddress(); // Adresse virtuelle de l'index buffer
    m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT; // Format des indices (par exemple, 32 bits non signés)
    m_IndexBufferView.SizeInBytes = m_IndexCount * m_IndexSize; // Taille totale de l'index buffer en octets

    return;
};

const Vertex* Mesh::ConvertVertexConst(vector<Vertex> vertices) {
    return vertices.data();
};

const UINT* Mesh::ConvertIndexConst(vector<UINT> index) {
    return index.data();
};