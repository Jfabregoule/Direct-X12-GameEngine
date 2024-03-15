#include "BlankProject.h"
#include "BulletScript.h"

BulletScript::BulletScript(Entity *entity)
{
	m_Name = "bulletscript";
	m_pEntity = entity;
}

BulletScript::~BulletScript()
{
}

void BulletScript::InitBulletScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed) {

	m_Dmg = 1;
	m_Speed = speed;
	m_LifeTime = lifetime;
	m_Direction = direction;
	m_DecreaseLifeSpeed = decreaselifespeed;

}

void BulletScript::Update(float dt, float* gameSpeed)
{

	m_LifeTime -= m_DecreaseLifeSpeed * dt * *gameSpeed;

	if (m_LifeTime <= 0)
	{
		m_pEntity->SetDestroyValue(true);
		return;
	}

	m_pEntity->Forward(m_Speed, dt, gameSpeed);

}
