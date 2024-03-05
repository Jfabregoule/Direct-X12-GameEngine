#include "Engine.h"
#include "Camera.h"


Camera::Camera(Transform *transform) {
    camTransform = transform;
};

Camera::~Camera() {

};

void Camera::Init(float aspectRatio) {

    SetName("camera");

    // Paramètres de la projection perspective
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(70.0f);
    m_NearZ = 0.1f;
    m_FarZ = 1000.0f;

    // Création de la matrice de projection perspective
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);

    m_Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    //m_Target = DirectX::XMVectorZero();
}


void Camera::MoveForward(float distance) {
    DirectX::XMVECTOR forward = DirectX::XMVector3Normalize(m_Forward);
    DirectX::XMVECTOR displacement = DirectX::XMVectorScale(forward, distance);

    m_Position = DirectX::XMVectorAdd(m_Position, displacement);
}

void Camera::MoveBackward(float distance) {
    DirectX::XMVECTOR backward = DirectX::XMVectorNegate(DirectX::XMVector3Normalize(m_Forward));
    DirectX::XMVECTOR displacement = DirectX::XMVectorScale(backward, distance);

    m_Position = DirectX::XMVectorAdd(m_Position, displacement);
}

void Camera::StrafeRight(float distance) {
    DirectX::XMVECTOR right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(m_Forward, m_Tup));
    DirectX::XMVECTOR displacement = DirectX::XMVectorScale(right, distance);

    m_Position = DirectX::XMVectorAdd(m_Position, displacement);
}

void Camera::StrafeLeft(float distance) {
    DirectX::XMVECTOR left = DirectX::XMVectorNegate(DirectX::XMVector3Normalize(DirectX::XMVector3Cross(m_Forward, m_Tup)));
    DirectX::XMVECTOR displacement = DirectX::XMVectorScale(left, distance);

    m_Position = DirectX::XMVectorAdd(m_Position, displacement);
}

void Camera::UpdateFront()
{

    // Direction est un vecteur normalisé, représentant le "devant" de la caméra
    DirectX::XMVECTOR direction = DirectX::XMVectorSet(0, 0, 1, 0);

    // Appliquer la rotation de la caméra à la direction
    DirectX::XMMATRIX rotationMatrix = DirectX::XMLoadFloat4x4(&camTransform->m_MatrixRotation);
    direction = DirectX::XMVector3TransformNormal(direction, rotationMatrix);

    // Normaliser la direction pour s'assurer qu'elle est unitaire
    direction = DirectX::XMVector3Normalize(direction);

    // Mettre à jour m_Forward avec la direction calculée
    m_Forward = direction;
}

void Camera::UpdateMatrix() {
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);
}
