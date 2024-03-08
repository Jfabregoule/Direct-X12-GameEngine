#include "Engine.h"
#include "Engine/Texture.h"

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
	DirectX::CreateDDSTextureFromFile12(m_pInst->device,
		m_pInst->mCommandList, texture->Filename.c_str(),
		texture->Resource, texture->UploadHeap);

	m_pListTexture[name] = std::move(texture);
	
}

void TextureManager::InitSRV() {

};


#pragma endregion

