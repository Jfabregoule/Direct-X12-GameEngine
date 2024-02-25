#pragma once
#include <DirectXMath.h>
#include <malloc.h>

class DX12Camera {
public:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 target;
    DirectX::XMFLOAT3 up;
    DirectX::XMFLOAT4X4 viewMatrix;

    DX12Camera() : position(0.0f, 0.0f, -20.0f), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f) {}

    void UpdateViewMatrix(float dx, float dy, float dz) {
        // Mettre à jour la position de la caméra
        position.x += dx;
        position.y += dy;
        position.z += dz;

        // Mettre à jour la matrice de vue avec la nouvelle position
        DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&position);
        DirectX::XMVECTOR tgt = DirectX::XMLoadFloat3(&target);
        DirectX::XMVECTOR upward = DirectX::XMLoadFloat3(&up);

        DirectX::XMStoreFloat4x4(&viewMatrix, DirectX::XMMatrixLookAtLH(pos, tgt, upward));
    }

    // Ajouter une méthode pour obtenir l'adresse de la matrice de vue
    DirectX::XMFLOAT4X4* GetViewMatrixAddress() {
        return &viewMatrix;
    }

    D3D12_GPU_VIRTUAL_ADDRESS GetViewMatrixGpuAddress() const {
        // Utiliser aligned_alloc pour allouer la mémoire alignée
        void* alignedMemory = _aligned_malloc(sizeof(DirectX::XMFLOAT4X4), 256);
        memcpy(alignedMemory, &viewMatrix, sizeof(DirectX::XMFLOAT4X4));
        return static_cast<D3D12_GPU_VIRTUAL_ADDRESS>(reinterpret_cast<size_t>(alignedMemory));
    }
};
