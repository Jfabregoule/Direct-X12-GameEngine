#pragma once

#include "Engine/Script.h"
#include "DirectXMath.h"
#include "Engine/Entity.h"

class Enemy;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									EnemyScript Class	                                |
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

	float m_clock = 0;

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

	VOID SetCurrentState(State state) { m_CurrentState = state; };

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

	bool InternClock(float dt);

#pragma endregion

};

#pragma endregion