#pragma once

#include "Engine/Script.h"
#include "DirectXMath.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									PlayerScript Class	                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region PlayerScript Class

class PlayerScript : public Script {

private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	float				m_DecreaseLifeSpeed;
	float				m_LifeTime;
	float				m_Speed;
	DirectX::XMFLOAT3	m_Direction;

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

	PlayerScript();
	~PlayerScript();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void InitPlayerScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed);

	void Update(float dt, float* gameSpeed) override;

#pragma endregion

};

#pragma endregion