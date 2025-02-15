#include "Engine.h"

#include "Camera.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

Camera::Camera(Transform *transform) {
    m_Name = "camera";
    camTransform = transform;
};

Camera::~Camera() {

};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Initialize 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Initialize

void Camera::Init(float aspectRatio) {

    SetName("camera");

    // Param�tres de la projection perspective
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(90.0f);
    m_NearZ = 0.1f;
    m_FarZ = 10000.0f;

    // Cr�ation de la matrice de projection perspective
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);

    m_Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    //m_Target = DirectX::XMVectorZero();
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

void Camera::UpdateMatrix() {
    m_ProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);
}

void Camera::Update(float dt, float* gameSpeed)
{
    ChangePos();
}

void Camera::Change() {


    DirectX::XMVECTOR temp = DirectX::XMLoadFloat3(&m_Forward);

    m_Target = DirectX::XMVectorAdd(m_Position, temp); // Calculez le point que la cam�ra regarde

    //Si crash ici, m_Target doit etre diff�rent de 0
    m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, m_Up);
    DirectX::XMStoreFloat4x4(&m_MatrixView, m_ViewMatrix);
}

//On s�pare les infos de change pos et change forward pour appeler seulement la fonction n�cessaire
void Camera::ChangePos() {
    m_Position = DirectX::XMVectorSet(camTransform->m_VectorPosition.x, camTransform->m_VectorPosition.y, camTransform->m_VectorPosition.z, 1.0f);
    Change();
}

void Camera::ChangeForward() {
    m_Forward = camTransform->GetForwardVector();
    Change();
};

#pragma endregion