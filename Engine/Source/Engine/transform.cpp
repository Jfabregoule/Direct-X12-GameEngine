#include "Engine.h"
#include "Transform.h"

#define IDENTITY {1.0f,0.0f,0.0f,0.0f,    0.0f,1.0f,0.0f,0.0f,    0.0f,0.0f,1.0f,0.0f,    0.0f,0.0f,0.0f,1.0f};

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

void Transform::Scale(float scaleX, float scaleY, float scaleZ) 
{
    // Vector
    m_VectorScale.x *= scaleX;
    m_VectorScale.y *= scaleY;
    m_VectorScale.z *= scaleZ;

    // Matrix
    XMMATRIX scalingMatrix = XMMatrixScaling(m_VectorScale.x, m_VectorScale.y, m_VectorScale.z);

    XMStoreFloat4x4(&m_MatrixScale, scalingMatrix);
}

// Rotation
void Transform::Rotate(float yaw, float pitch, float roll) 
{
    // Quaternion
    XMVECTOR quaternion;
    quaternion = XMQuaternionRotationAxis(XMLoadFloat3(&m_VectorDirection), roll);
    quaternion = XMQuaternionMultiply(quaternion, XMQuaternionRotationAxis(XMLoadFloat3(&m_VectorRight), pitch));
    quaternion = XMQuaternionMultiply(quaternion, XMQuaternionRotationAxis(XMLoadFloat3(&m_VectorUp), yaw));
    XMVECTOR qRot = XMLoadFloat4(&m_QuaternionRotation);
    qRot = XMQuaternionMultiply(qRot, quaternion);
    XMStoreFloat4(&m_QuaternionRotation, qRot);

    m_VectorRotation.x += pitch;
    m_VectorRotation.y += yaw;
    m_VectorRotation.z += roll;

    // Matrix
    XMMATRIX  rotationMatrix = XMMatrixRotationQuaternion(qRot);
    XMStoreFloat4x4(&m_MatrixRotation, rotationMatrix);

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

void Transform::Translate(float positionX, float positionY, float positionZ) 
{
    // Vector
    m_VectorPosition.x += positionX;
    m_VectorPosition.y += positionY;
    m_VectorPosition.z += positionZ;


    // Matrix
    XMMATRIX translationMatrix = XMMatrixTranslation(m_VectorPosition.x, m_VectorPosition.y, m_VectorPosition.z);

    XMStoreFloat4x4(&m_MatrixPosition, translationMatrix);
}

// Result
void Transform::UpdateMatrix() 
{
    XMMATRIX globalMatrix;

    globalMatrix = XMLoadFloat4x4(&m_MatrixScale);
    globalMatrix = XMMatrixMultiply(globalMatrix, XMLoadFloat4x4(&m_MatrixRotation));
    globalMatrix = XMMatrixMultiply(globalMatrix, XMLoadFloat4x4(&m_MatrixPosition));

    XMStoreFloat4x4(&m_Matrix, globalMatrix);
}