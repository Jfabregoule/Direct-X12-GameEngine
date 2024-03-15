#include "Engine.h"

#include "Engine/Texture.h"

#include "DirectX12/DDSTextureLoader.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Constructor/Destructor 								|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

TextureManager::TextureManager(DirectX12Instance* inst) {
    m_pInst = inst;
};

TextureManager::~TextureManager() {

}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Methods 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Methods

void TextureManager::AddTexture(std::string name, std::wstring path) {

    Texture* texture = new Texture();
    texture->Name = name;
    texture->Filename = path;

    HRESULT hresult;

    hresult = DirectX::CreateDDSTextureFromFile12(m_pInst->device,
        m_pInst->mCommandList, texture->Filename.c_str(),
        texture->Resource, texture->UploadHeap);

    CheckSucceeded(hresult);

    InitSRV(texture);

    m_pListTexture[name] = texture;
}

void TextureManager::InitSRV(Texture* texture) {
    // Obtenez le handle CPU pour le prochain emplacement disponible dans le heap
    CD3DX12_CPU_DESCRIPTOR_HANDLE descriptorHandleCPU(m_SrvHeap->GetCPUDescriptorHandleForHeapStart(), m_DescriptorIndexCPU, m_pInst->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

    // Obtenez le handle GPU correspondant
    CD3DX12_GPU_DESCRIPTOR_HANDLE descriptorHandleGPU(m_SrvHeap->GetGPUDescriptorHandleForHeapStart(), m_DescriptorIndexGPU, m_pInst->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

    // Remplissez la description du SRV
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = texture->Resource->GetDesc().Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = texture->Resource->GetDesc().MipLevels;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

    // Créez le SRV en utilisant les handles CPU et GPU appropriés
    m_pInst->device->CreateShaderResourceView(texture->Resource.Get(), &srvDesc, descriptorHandleCPU);

    // Stockez les handles dans la structure de texture
    texture->m_DescriptorHandleCPU = descriptorHandleCPU;
    texture->m_DescriptorHandleGPU = descriptorHandleGPU;

    // Incrémentez les indices de descripteur pour la prochaine texture
    m_DescriptorIndexCPU += m_pInst->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    m_DescriptorIndexGPU += m_pInst->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void TextureManager::InitDescHeap() {
    //
    // Create the SRV heap.
    //

    m_HeapDesc.NumDescriptors = 1000;
    m_HeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    m_HeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    m_pInst->device->CreateDescriptorHeap(&m_HeapDesc, IID_PPV_ARGS(&m_SrvHeap));


}


#pragma endregion