#pragma once 
#include <map>
#include <string>
#include <d3d12.h>
#include <wrl/client.h>

class DirectX12Instance;


struct Texture
{
	// Unique material name for lookup.
	std::string Name;

	std::wstring Filename;

	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;

};

class ENGINE_API TextureManager {
private: 

	std::map <std::string, Texture*> m_pListTexture = {};
	DirectX12Instance* m_pInst = nullptr;

	D3D12_DESCRIPTOR_HEAP_DESC m_HeapDesc;

	ID3D12DescriptorHeap* m_SrvHeap;
	D3D12_SHADER_RESOURCE_VIEW_DESC m_SrvDesc = {};

public: 
	
	/*
	* |----------------------------------------------
	* |	                    Init                     |
	* |----------------------------------------------
	*/

	TextureManager(DirectX12Instance* inst);
	~TextureManager();

	/*
	* |----------------------------------------------
	* |	             Getters/Setters                 |
	* |----------------------------------------------
	*/

	std::map <std::string, Texture*>* GetTextureMap() { return &m_pListTexture; };
	ID3D12DescriptorHeap* GetSrvHeap() { return m_SrvHeap; };
	D3D12_DESCRIPTOR_HEAP_DESC* GetHeapDesc() { return &m_HeapDesc; };
	

	/*
	* |----------------------------------------------
	* |	                   Methods                   |
	* |----------------------------------------------
	*/

	void AddTexture(std::string name, std::wstring path);
	void InitSRV(Texture* texture);
	void InitDescHeap();
};




