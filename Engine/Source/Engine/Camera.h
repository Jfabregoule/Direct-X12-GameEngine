#pragma once 
#include <DirectXMath.h>


#include "Engine/Component.h"
#include "DirectX12/MathHelper.h"
#include "transform.h"

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

	float				m_AspectRatio;
	float				m_FovAngleY;
	float				m_NearZ;
	float				m_FarZ;

	DirectX::XMMATRIX	m_ProjMatrix;
	DirectX::XMMATRIX	m_ViewMatrix;
	DirectX::XMFLOAT4X4 m_MatrixProj = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 m_MatrixView = MathHelper::Identity4x4();

	DirectX::XMVECTOR	m_Target;
	DirectX::XMVECTOR	m_Up;

	DirectX::XMFLOAT3	m_Forward;
	DirectX::XMVECTOR	m_Position;
	DirectX::XMVECTOR	m_Tup;

	Transform*			camTransform;

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

	DirectX::XMFLOAT4X4 GetMatrixView() { return m_MatrixView; };

	DirectX::XMVECTOR* GetTarget() { return &m_Target; };
	void SetTarget(DirectX::XMVECTOR vector) { m_Target = vector; };

	DirectX::XMVECTOR* GetUp() { return &m_Up; };
	void SetUp(DirectX::XMVECTOR vector) { m_Up = vector; };

	Transform* GetTransform() { return camTransform; };

	

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

	void Update(float dt) override;

#pragma endregion

};

#pragma endregion