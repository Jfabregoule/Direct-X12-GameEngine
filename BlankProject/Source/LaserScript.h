#pragma once

#include "DirectXMath.h"

#include "Engine/Script.h"
#include "Engine/Entity.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									LaserScript Class	                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region LaserScript Class

class LaserScript : public Script { 

private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	Entity* m_pEntity;

	int					m_Dmg;
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

	LaserScript(Entity* entity);
	~LaserScript();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	int GetDmg() { return m_Dmg; };

	void InitLaserScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed);

	void Update(float dt, float* gameSpeed) override;

#pragma endregion

};

#pragma endregion