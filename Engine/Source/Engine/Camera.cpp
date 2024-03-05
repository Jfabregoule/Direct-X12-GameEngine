#include "Engine.h"
#include "Camera.h"


Camera::Camera(Transform *transform) {
    camTransform = transform;
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

    //m_Target = DirectX::XMVectorZero();
}



void Camera::UpdateFront()
{

    // Direction est un vecteur normalis�, repr�sentant le "devant" de la cam�ra
    DirectX::XMVECTOR direction = DirectX::XMVectorSet(0, 0, 1, 0);

    // Appliquer la rotation de la cam�ra � la direction
    DirectX::XMMATRIX rotationMatrix = DirectX::XMLoadFloat4x4(&camTransform->m_MatrixRotation);
    direction = DirectX::XMVector3TransformNormal(direction, rotationMatrix);

    // Normaliser la direction pour s'assurer qu'elle est unitaire
    direction = DirectX::XMVector3Normalize(direction);

    // Mettre � jour m_Forward avec la direction calcul�e
    m_Forward = direction;
}

void Camera::UpdateMatrix() {
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);
}
