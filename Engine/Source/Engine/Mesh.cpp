#include "Engine.h"
#include "Mesh.h"
#include "Engine/CubeMesh.h"
#include "Engine/PyramidMesh.h"
#include "Engine/PipeMesh.h"
#include "Engine/SphereMesh.h"

Mesh::Mesh()
{
    m_Name = "mesh";
}

Mesh::~Mesh()
{
	
}

void Mesh::InitializeMesh(ID3D12Device* device, string type, Vertex* vertices)
{
    if (vertices == nullptr) {
        if (type == "cube")
        {
            CubeMesh* pCubeMesh = new CubeMesh();
            pCubeMesh->GenerateCube();
            m_Vertices = pCubeMesh->cube;
            m_Indices = pCubeMesh->cubeIndices;
            m_VerticesCount = pCubeMesh->cubeVerticesCount;
            m_IndexCount = pCubeMesh->cubeIndicesCount;
        }
        else if (type == "pyramid")
        {
            PyramidMesh* pPyramidMesh = new PyramidMesh();
            pPyramidMesh->GeneratePyramid();
            m_Vertices = pPyramidMesh->pyramid;
            m_Indices = pPyramidMesh->pyramidIndices;
            m_VerticesCount = pPyramidMesh->pyramidVerticesCount;
            m_IndexCount = pPyramidMesh->pyramidIndicesCount;
        }
        else if (type == "pipe")
        {
            PipeMesh* pPipeMesh = new PipeMesh();
            pPipeMesh->InitPipeMesh(100);
            pPipeMesh->GeneratePipe();
            m_Vertices = pPipeMesh->pipe;
            m_Indices = pPipeMesh->pipeIndices;
            m_VerticesCount = pPipeMesh->pipeVerticesCount;
            m_IndexCount = pPipeMesh->pipeIndicesCount;
        }
        else if (type == "sphere")
        {
            SphereMesh* pSphereMesh = new SphereMesh();
            pSphereMesh->InitSphereMesh(100);
            pSphereMesh->GenerateSphere();
            m_Vertices = pSphereMesh->sphere;
            m_Indices = pSphereMesh->sphereIndices;
            m_VerticesCount = pSphereMesh->sphereVerticesCount;
            m_IndexCount = pSphereMesh->sphereIndicesCount;
        }
        else
        {
            CubeMesh* pCubeMesh = new CubeMesh();
            pCubeMesh->GenerateCube();
            m_Vertices = pCubeMesh->cube;
            m_Indices = pCubeMesh->cubeIndices;
            m_VerticesCount = pCubeMesh->cubeVerticesCount;
            m_IndexCount = pCubeMesh->cubeIndicesCount;
        }
    }
    else {
        m_Vertices = vertices;
        m_Indices = nullptr;
    }
    m_VertexSize = sizeof(Vertex);
    m_IndexSize = sizeof(UINT);

    CreateVertexBuffer(device);
    CreateIndexBuffer(device);
    CreateVertexBufferView(device);
    CreateIndexBufferView(device);

}

void Mesh::CreateVertexBuffer(ID3D12Device* device) {
    // Créer un tampon de ressources (vertex buffer)
    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_VertexSize * m_VerticesCount);
    HRESULT hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_VertexBuffer)
    );
    if (FAILED(hr)) {
        // Gérer l'échec de la création de la ressource
        return;
    }

    // Remplir le tampon de ressources avec les données des vertices
    CD3DX12_RANGE readRange(0, 0);
    UINT8* pVertexDataBegin = nullptr;
    hr = m_VertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    if (hr != S_OK) {
        // Gérer l'échec de la mise en mappage
        m_VertexBuffer->Release(); // Libérer la ressource avant de quitter
        m_VertexBuffer = nullptr; // Réinitialiser le pointeur
        return;
    }
    memcpy(pVertexDataBegin, m_Vertices, m_VertexSize * m_VerticesCount);
    m_VertexBuffer->Unmap(0, nullptr);
}

void Mesh::CreateIndexBuffer(ID3D12Device* device) {

    // Créer un tampon de ressources (index buffer)
    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_IndexCount * m_IndexSize);
    HRESULT hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_IndicesBuffer)
    );

    // Remplir le tampon de ressources avec les données des indices
    UINT8* pIndexDataBegin = nullptr;
    CD3DX12_RANGE readRange(0, 0); // On ne lit pas les données actuellement, donc la plage est vide
    hr = m_IndicesBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
    if (hr != S_OK) {
        // Gérer l'échec de la mise en mappage
        m_IndicesBuffer->Release(); // Libérer la ressource avant de quitter
        m_IndicesBuffer = nullptr; // Réinitialiser le pointeur
        return;
    }
    memcpy(pIndexDataBegin, m_Indices, m_IndexCount * m_IndexSize);
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

void Mesh::CleanUpMeshResources() {
    // Libérer les ressources du vertex buffer
    if (m_VertexBuffer != nullptr) {
        m_VertexBuffer->Release();
        m_VertexBuffer = nullptr;
    }

    // Libérer les ressources de l'index buffer
    if (m_IndicesBuffer != nullptr) {
        m_IndicesBuffer->Release();
        m_IndicesBuffer = nullptr;
    }

    // Autres ressources à libérer, comme des textures, des buffers de constantes, etc.

    // Réinitialiser les vues de tampon
    ZeroMemory(&m_VertexBufferView, sizeof(D3D12_VERTEX_BUFFER_VIEW));
    ZeroMemory(&m_IndexBufferView, sizeof(D3D12_INDEX_BUFFER_VIEW));
}