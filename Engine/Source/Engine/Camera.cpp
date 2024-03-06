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

void Camera::UpdateMatrix() {
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);
}

void Camera::Change() {

    m_Target = m_Position + m_Forward; // Calculez le point que la caméra regarde

    //Si crash ici, m_Target doit etre différent de 0
    m_ViewMatrix = XMMatrixLookAtLH(m_Position, m_Target, m_Up);
    XMStoreFloat4x4(&m_MatrixView, m_ViewMatrix);
}

//On sépare les infos de change pos et change forward pour appeler seulement la fonction nécessaire
void Camera::ChangePos() {
    m_Position = XMVectorSet(camTransform->m_VectorPosition.x, camTransform->m_VectorPosition.y, camTransform->m_VectorPosition.z, 1.0f);
    Change();
}

void Camera::ChangeForward() {
    m_Forward = GetForwardVector();
    Change();
};