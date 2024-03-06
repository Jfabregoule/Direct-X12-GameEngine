#pragma once 
#include <DirectXMath.h>


#include "Engine/Component.h"
#include "DirectX12/MathHelper.h"
#include "transform.h"



class ENGINE_API Camera : public Component {
private:

	float m_AspectRatio;
	float m_FovAngleY;
	float m_NearZ;
	float m_FarZ;

	DirectX::XMMATRIX m_ProjMatrix;
	DirectX::XMFLOAT4X4 m_MatrixProj = MathHelper::Identity4x4();

	DirectX::XMVECTOR m_Target;
	DirectX::XMVECTOR m_Up;

	DirectX::XMVECTOR m_Forward;
	DirectX::XMVECTOR m_Position;
	DirectX::XMVECTOR m_Tup;

	Transform* camTransform;

public:

	Camera(Transform *transform);
	~Camera();

	void Init(float aspectRatio);

	/*
	|---------------------------------------------------------------
	|						Getter/Setter							|
	|---------------------------------------------------------------
	*/

	DirectX::XMFLOAT4X4 GetMatrixProj() { return m_MatrixProj; };
	void SetFov(float FOV) { m_FovAngleY = FOV; UpdateMatrix(); };

	DirectX::XMVECTOR* GetTarget() { return &m_Target; };
	void SetTarget(DirectX::XMVECTOR vector) { m_Target = vector; };

	DirectX::XMVECTOR* GetUp() { return &m_Up; };
	void SetUp(DirectX::XMVECTOR vector) { m_Up = vector; };

	DirectX::XMVECTOR GetForwardVector() {
		// Construire une matrice de rotation à partir des angles d'Euler de la caméra

		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&camTransform->m_VectorRotation));

		// Définir la direction avant comme l'axe z (0, 0, 1) transformé par la matrice de rotation
		DirectX::XMVECTOR forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		forward = DirectX::XMVector3TransformNormal(forward, rotationMatrix);

		// Normaliser le vecteur résultant
		forward = DirectX::XMVector3Normalize(forward);

		return forward;
	}


	/*
	|---------------------------------------------------------------
	|							Methods								|
	|---------------------------------------------------------------
	*/


	void MoveForward(float distance);
	void MoveBackward(float distance);
	void StrafeRight(float distance);
	void StrafeLeft(float distance);
	void UpdateFront();
	void UpdateMatrix();

};