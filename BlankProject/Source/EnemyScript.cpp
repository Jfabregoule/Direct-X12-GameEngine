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

void EnemyScript::Update(float dt)
{

	switch (m_CurrentState) {
		case IDLE:
			UpdateIDLE();
			break;
		case TRIGGERED:
			UpdateTRIGGERED();
			break;
		case RETREAT:
			UpdateRETREAT();
			break;
	}

}

void EnemyScript::UpdateIDLE()
{
	//m_pEnemy->ChangeLastPos();

	m_pEntity->Forward(m_Speed,1);


	//if (m_pTransform->) {
	//}
}

void EnemyScript::UpdateTRIGGERED()
{

}

void EnemyScript::UpdateRETREAT()
{

}