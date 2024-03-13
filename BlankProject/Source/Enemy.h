#pragma once
#include "Ship.h"
#include <DirectXMath.h>
#include "Engine/Entity.h"

class EnemyScript;

class Enemy : public Ship {
private:

	DirectX::XMFLOAT3		m_Path [4];
	DirectX::XMFLOAT3		m_PathDirection[4];
	int						m_pathState = 0;

	DirectX::XMFLOAT3		m_LastPos;
	DirectX::XMFLOAT3		m_Dir;

	float					m_Renge;

	EnemyScript*			m_Script;

	Entity*					m_pEntity;

public:

	Enemy();
	~Enemy();

	Entity* GetEntity() { return m_pEntity; };

	VOID InitializeEnemy(DirectX12Instance* inst, DirectX::XMFLOAT3 path[4]);

	VOID InitPath(DirectX::XMFLOAT3 path[4]);

	VOID ChangeLastPos();

	VOID CheckDistancePath();

	VOID ChangeDirection(DirectX::XMFLOAT3 pos);

};