#pragma once 
#include <DirectXMath.h>


#include "Engine/Component.h"
#include "DirectX12/MathHelper.h"



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

public:

	Camera();
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


	/*
	|---------------------------------------------------------------
	|							Methods								|
	|---------------------------------------------------------------
	*/



	void UpdateMatrix();

};