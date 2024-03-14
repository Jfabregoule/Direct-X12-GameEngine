#include "BlankProject.h"

#include "RocketScript.h"

RocketScript::RocketScript(Entity* entity)
{
    m_Name = "rocketscript";
    m_pEntity = entity;
}

RocketScript::~RocketScript()
{
}

void RocketScript::InitRocketScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed) {

    m_Dmg = 3;
    m_Speed = speed;
    m_LifeTime = lifetime;
    m_Direction = direction;
    m_DecreaseLifeSpeed = decreaselifespeed;

}

void RocketScript::Update(float dt, float* gameSpeed) {

    m_LifeTime -= m_DecreaseLifeSpeed;

    if (m_LifeTime <= 0)
    {
        m_pEntity->SetDestroyValue(true);
        return;
    }

    m_pEntity->Translate(m_Speed * m_Direction.x, m_Speed * m_Direction.y, m_Speed * m_Direction.z);
}