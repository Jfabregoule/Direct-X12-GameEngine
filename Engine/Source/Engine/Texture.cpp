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
    texture->Name = "woodCrateTex";
    texture->Filename = L"../../Textures/WoodCrate01.dds";

    InitSRV(texture);

    DirectX::CreateDDSTextureFromFile12(m_pInst->device,
        m_pInst->command_list.Get(), texture->Filename.c_str(),
        texture->Resource, texture->UploadHeap);



    m_pListTexture[name] = std::move(texture);

}

void TextureManager::InitSRV(Texture* texture) {
    //
    // Create the SRV heap.
    //
    m_HeapDesc = {};
    m_HeapDesc->NumDescriptors = 1;
    m_HeapDesc->Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    m_HeapDesc->Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    m_pInst->device->CreateDescriptorHeap(m_HeapDesc, IID_PPV_ARGS(&m_SrvHeap));

    //
    // Fill out the heap with actual descriptors.
    //
    CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(m_SrvHeap->GetCPUDescriptorHandleForHeapStart());


    m_SrvDesc->Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    m_SrvDesc->Format = texture->Resource->GetDesc().Format;
    m_SrvDesc->ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    m_SrvDesc->Texture2D.MostDetailedMip = 0;
    m_SrvDesc->Texture2D.MipLevels = texture->Resource->GetDesc().MipLevels;
    m_SrvDesc->Texture2D.ResourceMinLODClamp = 0.0f;

    m_pInst->device->CreateShaderResourceView(texture->Resource.Get(), m_SrvDesc, hDescriptor);
};


#pragma endregion