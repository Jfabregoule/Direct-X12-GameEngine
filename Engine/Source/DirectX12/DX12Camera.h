#pragma once
#include <DirectXMath.h>
#include <malloc.h>

class DX12Camera {
public:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 target;
    DirectX::XMFLOAT3 up;
    DirectX::XMFLOAT4X4 viewMatrix;
    DirectX::XMFLOAT4X4 projectionMatrix; // Ajout de la matrice de projection

    DX12Camera() : position(200.0f, 0.0f, 20.0f), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f) {}

    void RotateAutomatically(float deltaTime) {
        // Par exemple, faire tourner la caméra autour de l'axe Y à une vitesse constante
        float rotationSpeed = 120.0f; // Ajustez selon la vitesse de rotation souhaitée
        float angle = rotationSpeed * deltaTime; // deltaTime est le temps écoulé depuis la dernière frame

        // Créer une matrice de rotation autour de l'axe Y
        DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationY(angle);

        // Appliquer la rotation à la position de la caméra
        DirectX::XMVECTOR positionVector = DirectX::XMLoadFloat3(&position);
        positionVector = DirectX::XMVector3TransformCoord(positionVector, rotationMatrix);
        DirectX::XMStoreFloat3(&position, positionVector);

        // Recalculer la matrice de vue avec la nouvelle position
        DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&position);
        DirectX::XMVECTOR tgt = DirectX::XMLoadFloat3(&target);
        DirectX::XMVECTOR upward = DirectX::XMLoadFloat3(&up);

        DirectX::XMStoreFloat4x4(&viewMatrix, DirectX::XMMatrixLookAtLH(pos, tgt, upward));
    }

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

    // Ajouter une méthode pour obtenir l'adresse de la matrice de projection
    DirectX::XMFLOAT4X4* GetProjectionMatrixAddress() {
        return &projectionMatrix;
    }

    // Méthode pour obtenir l'adresse de la matrice de vue pour l'envoi au GPU
    D3D12_GPU_VIRTUAL_ADDRESS GetViewMatrixGpuAddress(const DirectX::XMFLOAT4X4& viewMatrix) const {
        // Allocation de mémoire alignée
        void* alignedMemory = _aligned_malloc(sizeof(DirectX::XMFLOAT4X4), 256);
        memcpy(alignedMemory, &viewMatrix, sizeof(DirectX::XMFLOAT4X4));
        return static_cast<D3D12_GPU_VIRTUAL_ADDRESS>(reinterpret_cast<size_t>(alignedMemory));
    }

    // Méthode pour obtenir l'adresse de la matrice de projection pour l'envoi au GPU
    D3D12_GPU_VIRTUAL_ADDRESS GetProjectionMatrixGpuAddress(const DirectX::XMFLOAT4X4& projectionMatrix) const {
        // Allocation de mémoire alignée
        void* alignedMemory = _aligned_malloc(sizeof(DirectX::XMFLOAT4X4), 256);
        memcpy(alignedMemory, &projectionMatrix, sizeof(DirectX::XMFLOAT4X4));
        return static_cast<D3D12_GPU_VIRTUAL_ADDRESS>(reinterpret_cast<size_t>(alignedMemory));
    }
};
