#include "Engine.h"
#include "Transform.h"
#include "Maths.h"
#include <cmath>

//#define IDENTITY {1,0,0,0,    0,1,0,0,    0,0,1,0,    0,0,0,1};

#define IDENTITY {1.0f,0.0f,0.0f,0.0f,    0.0f,1.0f,0.0f,0.0f,    0.0f,0.0f,1.0f,0.0f,    0.0f,0.0f,0.0f,1.0f};

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

void Transform::Identity() {

    // Scale
    m_VectorScale = { 1.0f,1.0f,1.0f };

    m_MatrixScale = IDENTITY;


    // Rotation
    m_VectorDirection = { 0.0f,0.0f,1.0f };
    m_VectorRight = { 1.0f,0.0f,0.0f };
    m_VectorUp = { 0.0f,1.0f,0.0f };

    m_QuaternionRotation = { 0.0f,0.0f,0.0f,1.0f };

    m_VectorRotation = { 0.0f, 0.0f, 0.0f };

    m_MatrixRotation = IDENTITY;


    // Position
    m_VectorPosition = { 0.0f,0.0f,0.0f };

    m_MatrixPosition = IDENTITY;

    // Result
    m_Matrix = IDENTITY;
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

void Transform::Scale(float scaleX, float scaleY, float scaleZ) {

    // Vector
    m_VectorScale.x *= scaleX;
    m_VectorScale.y *= scaleY;
    m_VectorScale.z *= scaleZ;


    // Matrix
    DirectX::XMMATRIX scalingMatrix = DirectX::XMMatrixScaling(m_VectorScale.x, m_VectorScale.y, m_VectorScale.z);

    DirectX::XMStoreFloat4x4(&m_MatrixScale, scalingMatrix);
}

void Transform::Rotate(float yaw, float pitch, float roll) {

    // Quaternion
    DirectX::XMVECTOR quaternion;
    quaternion = DirectX::XMQuaternionRotationAxis(XMLoadFloat3(&m_VectorDirection), roll);
    quaternion = DirectX::XMQuaternionMultiply(quaternion, DirectX::XMQuaternionRotationAxis(DirectX::XMLoadFloat3(&m_VectorRight), pitch));
    quaternion = DirectX::XMQuaternionMultiply(quaternion, DirectX::XMQuaternionRotationAxis(DirectX::XMLoadFloat3(&m_VectorUp), yaw));
    DirectX::XMVECTOR qRot = DirectX::XMLoadFloat4(&m_QuaternionRotation);
    qRot = DirectX::XMQuaternionMultiply(qRot, quaternion);
    DirectX::XMStoreFloat4(&m_QuaternionRotation, qRot);

    m_VectorRotation.x += pitch;
    m_VectorRotation.y += yaw;
    m_VectorRotation.z += roll;

    // Matrix
    DirectX::XMMATRIX  rotationMatrix = DirectX::XMMatrixRotationQuaternion(qRot);
    DirectX::XMStoreFloat4x4(&m_MatrixRotation, rotationMatrix);

    // Axis
    m_VectorDirection.x = m_MatrixRotation._11;
    m_VectorDirection.y = m_MatrixRotation._12;
    m_VectorDirection.z = m_MatrixRotation._13;

    m_VectorRight.x = m_MatrixRotation._21;
    m_VectorRight.y = m_MatrixRotation._22;
    m_VectorRight.z = m_MatrixRotation._23;

    m_VectorUp.x = m_MatrixRotation._31;
    m_VectorUp.y = m_MatrixRotation._32;
    m_VectorUp.z = m_MatrixRotation._33;

}

void Transform::Translate(float positionX, float positionY, float positionZ) {
    // Vector
    m_VectorPosition.x += positionX;
    m_VectorPosition.y += positionY;
    m_VectorPosition.z += positionZ;


    // Matrix
    DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslation(m_VectorPosition.x, m_VectorPosition.y, m_VectorPosition.z);

    DirectX::XMStoreFloat4x4(&m_MatrixPosition, translationMatrix);
}

void Transform::UpdateMatrix() {

    DirectX::XMMATRIX globalMatrix;

    globalMatrix = DirectX::XMLoadFloat4x4(&m_MatrixScale);
    globalMatrix = DirectX::XMMatrixMultiply(globalMatrix, DirectX::XMLoadFloat4x4(&m_MatrixRotation));
    globalMatrix = DirectX::XMMatrixMultiply(globalMatrix, DirectX::XMLoadFloat4x4(&m_MatrixPosition));

    DirectX::XMStoreFloat4x4(&m_Matrix, globalMatrix);
}

DirectX::XMFLOAT3 Transform::GetForwardVector() {
    // Construire une matrice de rotation à partir des angles d'Euler de la caméra

    DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&m_VectorRotation));

    // Définir la direction avant comme l'axe z (0, 0, 1) transformé par la matrice de rotation
    DirectX::XMVECTOR forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forward = DirectX::XMVector3TransformNormal(forward, rotationMatrix);

    // Normaliser le vecteur résultant
    forward = DirectX::XMVector3Normalize(forward);

    DirectX::XMFLOAT3 temp;

    DirectX::XMStoreFloat3(&temp, forward);

    return temp;
}

DirectX::XMVECTOR Transform::GetRightVector() {
    // Construire une matrice de rotation à partir des angles d'Euler de la caméra

    DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&m_VectorRotation));

    // Définir la direction avant comme l'axe x (1, 0, 0) transformé par la matrice de rotation
    DirectX::XMVECTOR right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
    right = DirectX::XMVector3TransformNormal(right, rotationMatrix);

    // Normaliser le vecteur résultant
    right = DirectX::XMVector3Normalize(right);

    return right;
}

DirectX::XMVECTOR Transform::GetUpVector() {
    // Construire une matrice de rotation à partir des angles d'Euler de la caméra

    DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&m_VectorRotation));

    // Définir la direction avant comme l'axe y (0, 1, 0) transformé par la matrice de rotation
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    up = DirectX::XMVector3TransformNormal(up, rotationMatrix);

    // Normaliser le vecteur résultant
    up = DirectX::XMVector3Normalize(up);

    return up;
}

void Transform::RotateEntityTowardsObject(const DirectX::XMFLOAT3& objectPosition) {
    
}

VOID Transform::SetDirection(DirectX::XMFLOAT3 posTarget) {


    // Calcul de la direction vers la cible
    DirectX::XMFLOAT3 direction;
    direction.x = posTarget.x - m_VectorPosition.x;
    direction.y = posTarget.y - m_VectorPosition.y;
    direction.z = posTarget.z - m_VectorPosition.z;

    // Normalisation de la direction
    float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length > 0.0f) {
        direction.x /= length;
        direction.y /= length;
        direction.z /= length;
    }

    // Calcul de l'angle de rotation autour de l'axe Y (yaw)
    float yaw = atan2(direction.x, direction.z);

    // Calcul de l'angle de rotation autour de l'axe X (pitch)
    float pitch = asin(-direction.y);

    // Mise à jour du vecteur de rotation
    m_VectorRotation.x = pitch;
    m_VectorRotation.y = yaw;
    m_VectorRotation.z = 0.0f; // Le roll est souvent considéré comme nul lorsqu'on vise une direction précise

    // Création de la matrice de rotation à partir des angles de rotation
    DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);
    DirectX::XMStoreFloat4x4(&m_MatrixRotation, rotationMatrix);

    // Mise à jour des vecteurs de direction, de droite et de haut à partir de la matrice de rotation
    m_VectorDirection.x = m_MatrixRotation._31;
    m_VectorDirection.y = m_MatrixRotation._32;
    m_VectorDirection.z = m_MatrixRotation._33;

    m_VectorRight.x = m_MatrixRotation._11;
    m_VectorRight.y = m_MatrixRotation._12;
    m_VectorRight.z = m_MatrixRotation._13;

    m_VectorUp.x = m_MatrixRotation._21;
    m_VectorUp.y = m_MatrixRotation._22;
    m_VectorUp.z = m_MatrixRotation._23;
    
};

#pragma endregion