#pragma once

#include "DirectXMath.h"

#include "Engine/Entity.h"
#include "Engine/Script.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									BulletScript Class	                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region BulletScript Class

class BulletScript : public Script {

private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	Entity*				m_pEntity;

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

	BulletScript(Entity *entity);
	~BulletScript();

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

	void InitBulletScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed);

	void Update(float dt, float* gameSpeed) override;

#pragma endregion

};

#pragma endregion