#include "BlankProject.h"
#include "EnemyScript.h"
#include "Enemy.h"

EnemyScript::EnemyScript(Enemy* enemy)
{
	m_Name = "script";
	m_pEnemy = enemy;
	m_pEntity = m_pEnemy->GetEntity();
}

EnemyScript::~EnemyScript()
{
}

void EnemyScript::InitEnemyScript(float speed, DirectX::XMFLOAT3 direction) {

	m_Speed = speed;
	m_Direction = direction;
	m_CurrentState = IDLE;
	m_pTransform = m_pEntity->GetTransform();

}

void EnemyScript::Update(float dt, float* gameSpeed)
{

	switch (m_CurrentState) {
		case IDLE:
			UpdateIDLE(dt, gameSpeed);
			break;
		case PATHING:
			UpdatePATHING(dt, gameSpeed);
			break;
		case TRIGGERED:
			UpdateTRIGGERED(dt, gameSpeed);
			break;
		case RETREAT:
			UpdateRETREAT(dt, gameSpeed);
			break;
	}

}

void EnemyScript::UpdateIDLE(float dt, float* gameSpeed)
{
	m_pEnemy->CheckDistancePlayer();
}

void EnemyScript::UpdatePATHING(float dt, float* gameSpeed)
{
	m_pEntity->Forward(m_Speed, dt, gameSpeed);

	m_pEnemy->CheckDistancePath();

	m_pEnemy->CheckDistancePlayer();
}

void EnemyScript::UpdateTRIGGERED(float dt, float* gameSpeed)
{
	m_pEnemy->FocusOnPlayer();

	m_pEntity->Forward(m_Speed, dt, gameSpeed);

	m_pEnemy->CheckDistancePlayerOutOfRange();
}

void EnemyScript::UpdateRETREAT(float dt, float* gameSpeed)
{
	m_pEntity->Forward(m_Speed, dt, gameSpeed);

	m_pEnemy->CheckDistancePath();
}