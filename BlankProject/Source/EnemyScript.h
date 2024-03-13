#pragma once

#include "Engine/Script.h"
#include "DirectXMath.h"
#include "Engine/Entity.h"

class Enemy;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									BulletScript Class	                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

enum State {
	IDLE,
	PATHING,
	TRIGGERED,
	RETREAT
};

#pragma region EnemyScript Class

class EnemyScript : public Script {

private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	Enemy* m_pEnemy;
	Entity* m_pEntity;
	Transform* m_pTransform;

	State m_CurrentState;
	
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

	EnemyScript(Enemy* enemy);
	~EnemyScript();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void InitEnemyScript(float speed, DirectX::XMFLOAT3 direction);

	void Update(float dt, float* gameSpeed) override;

	void UpdateIDLE(float dt, float* gameSpeed);

	void UpdatePATHING(float dt, float* gameSpeed);

	void UpdateTRIGGERED(float dt, float* gameSpeed);

	void UpdateRETREAT(float dt, float* gameSpeed);

#pragma endregion

};

#pragma endregion