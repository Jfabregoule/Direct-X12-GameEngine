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

TextureManager::TextureManager() {

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
	/*
	Texture* texture = new Texture();
	texture->Name = "woodCrateTex";
	texture->Filename = L"../../Textures/WoodCrate01.dds";
	DirectX::CreateDDSTextureFromFile12(m_device,
		mCommandList.Get(), texture->Filename.c_str(),
		texture->Resource, texture->UploadHeap);

	m_pListTexture->insert(std::make_pair(name, texture));
	*/

}

void TextureManager::LoadTextures()
{
	
}

#pragma endregion

