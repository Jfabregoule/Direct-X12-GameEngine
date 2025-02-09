#include "Engine.h"
#include "Camera.h"


Camera::Camera() {

};

Camera::~Camera() {

};

void Camera::Init(float aspectRatio) {

    SetName("camera");

    // Param�tres de la projection perspective
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(70.0f);
    m_NearZ = 0.1f;
    m_FarZ = 1000.0f;

    // Cr�ation de la matrice de projection perspective
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);

    m_Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_Target = DirectX::XMVectorZero();
}

void Camera::UpdateMatrix() {
    // Cr�ation de la matrice de projection perspective
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

};