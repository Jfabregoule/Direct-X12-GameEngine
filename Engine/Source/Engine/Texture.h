#pragma once 
#include <map>
#include <string>
#include <d3d12.h>
#include <wrl/client.h>

struct Texture
{
	// Unique material name for lookup.
	std::string Name;

	std::wstring Filename;

	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;


};

class TextureManager {
private: 

	std::map <std::string, Texture*>* m_pListTexture;
	ID3D12Device* m_device;

public: 
	
	/*
	* |----------------------------------------------
	* |	                    Init                     |
	* |----------------------------------------------
	*/

	TextureManager();
	~TextureManager();

	/*
	* |----------------------------------------------
	* |	             Getters/Setters                 |
	* |----------------------------------------------
	*/

	/*
	* |----------------------------------------------
	* |	                   Methods                   |
	* |----------------------------------------------
	*/

	void AddTexture(std::string name, std::wstring path);
	void LoadTextures();
};




