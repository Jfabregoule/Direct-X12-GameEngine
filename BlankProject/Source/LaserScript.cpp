#include "BlankProject.h"
#include "LaserScript.h"

LaserScript::LaserScript(Entity* entity)
{
    m_Name = "script";
    m_pEntity = entity;
}

LaserScript::~LaserScript()
{
}

void LaserScript::InitLaserScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed) {

    m_Speed = speed;
    m_LifeTime = lifetime;
    m_Direction = direction;
    m_DecreaseLifeSpeed = decreaselifespeed;

}

void LaserScript::Update(float dt, float* gameSpeed) {

    m_LifeTime -= m_DecreaseLifeSpeed;

    m_Speed += m_Speed * 0.1f;

    if (m_LifeTime <= 0)
    {
        m_pEntity->SetDestroyValue(true);
        return;
    }

    m_pEntity->Translate(m_Speed * m_Direction.x, m_Speed * m_Direction.y, m_Speed * m_Direction.z);
}