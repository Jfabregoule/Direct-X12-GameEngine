#pragma once 
#include <DirectXMath.h>


#include "Engine/Component.h"
#include "DirectX12/MathHelper.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Camera Class                                        |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Camera Class

class ENGINE_API Camera : public Component {
private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

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

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                               Constructor/Destructor                                |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	Camera(Transform *transform);
	~Camera();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Init											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Init

	void Init(float aspectRatio);

#pragma endregion


	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									Getters/Setters										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Getters And Setters

	DirectX::XMFLOAT4X4 GetMatrixProj() { return m_MatrixProj; };
	void SetFov(float FOV) { m_FovAngleY = FOV; UpdateMatrix(); };

	DirectX::XMVECTOR* GetTarget() { return &m_Target; };
	void SetTarget(DirectX::XMVECTOR vector) { m_Target = vector; };

	DirectX::XMVECTOR* GetUp() { return &m_Up; };
	void SetUp(DirectX::XMVECTOR vector) { m_Up = vector; };


		return forward;
	}

	DirectX::XMVECTOR GetRightVector() {
		// Construire une matrice de rotation à partir des angles d'Euler de la caméra

		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&camTransform->m_VectorRotation));

		// Définir la direction avant comme l'axe x (1, 0, 0) transformé par la matrice de rotation
		DirectX::XMVECTOR right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		right = DirectX::XMVector3TransformNormal(right, rotationMatrix);

		// Normaliser le vecteur résultant
		right = DirectX::XMVector3Normalize(right);

		return right;
	}

	DirectX::XMVECTOR GetUpVector() {
		// Construire une matrice de rotation à partir des angles d'Euler de la caméra

		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&camTransform->m_VectorRotation));

		// Définir la direction avant comme l'axe y (0, 1, 0) transformé par la matrice de rotation
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		up = DirectX::XMVector3TransformNormal(up, rotationMatrix);

		// Normaliser le vecteur résultant
		up = DirectX::XMVector3Normalize(up);

		return up;
	}

#pragma endregion


	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										 Methods								        |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void ChangePos();
	void ChangeForward();

	void Change();
	void UpdateMatrix();

#pragma endregion

};

#pragma endregion