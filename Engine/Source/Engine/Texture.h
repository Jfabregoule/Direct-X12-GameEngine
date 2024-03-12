#pragma once 
#include <map>
#include <string>
#include <d3d12.h>
#include <wrl/client.h>
#include "DirectX12/dx12Inst.h"


struct Texture
{
	// Unique material name for lookup.
	std::string Name;

	std::wstring Filename;

	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_DescriptorHandleCPU;
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_DescriptorHandleGPU;

};

class ENGINE_API TextureManager {
private:

	std::map <std::string, Texture*> m_pListTexture = {};
	DirectX12Instance* m_pInst = nullptr;

	ID3D12DescriptorHeap* m_SrvHeap;
	D3D12_SHADER_RESOURCE_VIEW_DESC m_SrvDesc = {};
	D3D12_DESCRIPTOR_HEAP_DESC m_HeapDesc = {};

	UINT m_DescriptorIndexCPU = 0; // Suivi de l'index du prochain emplacement disponible dans le heap de descripteurs CPU
	UINT m_DescriptorIndexGPU = 0; // Suivi de l'index du prochain emplacement disponible dans le heap de descripteurs GPU



public:

	/*
	* |----------------------------------------------
	* |                        Init                     |
	* |----------------------------------------------
	*/

	TextureManager(DirectX12Instance* inst);
	~TextureManager();

	/*
	* |----------------------------------------------
	* |                 Getters/Setters                 |
	* |----------------------------------------------
	*/

	std::map <std::string, Texture*>* GetTextureMap() { return &m_pListTexture; };
	ID3D12DescriptorHeap* GetSrvHeap() { return m_SrvHeap; };
	D3D12_SHADER_RESOURCE_VIEW_DESC* GetSrvDesc() { return &m_SrvDesc; };
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