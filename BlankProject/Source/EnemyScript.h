#pragma once

#include "DirectXMath.h"

#include "Engine/Entity.h"
#include "Engine/Script.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									EnemyScript Class	                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

enum State {
	AFK,
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

	Entity*					m_pSelf;
	Entity*					m_pPlayer;
	Transform*				m_pTransform;

	DirectX12Instance*		m_pInst;

	State					m_CurrentState;
	
	float					m_Speed;
	DirectX::XMFLOAT3		m_Direction;

	DirectX::XMFLOAT3		m_Path[4];
	DirectX::XMFLOAT3		m_PathDirection[4];
	int						m_pathState = 0;
	int						m_nextPathState = 1;

	DirectX::XMFLOAT3		m_LastPos;
	DirectX::XMFLOAT3		m_Dir;
	DirectX::XMFLOAT3		m_Spawn;

	float					m_Range;

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

	EnemyScript();
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

	void InitEnemyScript(float speed, Entity* self, Entity* player);

	void Update(float dt, float* gameSpeed) override;

	void UpdateAFK(float dt, float* gameSpeed);

	void UpdatePATHING(float dt, float* gameSpeed);

	void UpdateTRIGGERED(float dt, float* gameSpeed);

	void UpdateRETREAT(float dt, float* gameSpeed);

	VOID InitializeEnemy(DirectX12Instance* inst, DirectX::XMFLOAT3 path[4]);

	VOID InitPath(DirectX::XMFLOAT3 path[4]);

	VOID ChangeLastPos();

	VOID CheckDistancePath();

	VOID CheckDistancePlayer();

	VOID FocusOnPlayer();

	VOID CheckDistancePlayerOutOfRange();

	VOID CheckDistanceSpawn();

	VOID ChangeDirection(DirectX::XMFLOAT3 pos);

	VOID SetCurrentState(State state) { m_CurrentState = state; };

	bool InternClock(float dt);

#pragma endregion

};

#pragma endregion