#include "BlankProject.h"
#include "RocketScript.h"

RocketScript::RocketScript(Entity* entity)
{
    m_Name = "script";
    m_pEntity = entity;
}

RocketScript::~RocketScript()
{
}

void RocketScript::InitRocketScript(float speed, float lifetime, DirectX::XMFLOAT3 direction, float decreaselifespeed) {

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



    /*

    // Recherche de l'ennemi le plus proche
    Enemy* closestEnemy = nullptr;
    float closestDistanceSq = FLT_MAX;
    DirectX::XMFLOAT3 rocketPosition = m_pEntity->GetPosition();
    for (Enemy& enemy : enemies) {
        DirectX::XMFLOAT3 enemyPosition = enemy.GetPosition();
        float distanceSq = (enemyPosition.x - rocketPosition.x) * (enemyPosition.x - rocketPosition.x) +
            (enemyPosition.y - rocketPosition.y) * (enemyPosition.y - rocketPosition.y) +
            (enemyPosition.z - rocketPosition.z) * (enemyPosition.z - rocketPosition.z);
        if (distanceSq < closestDistanceSq) {
            closestEnemy = &enemy;
            closestDistanceSq = distanceSq;
        }
    }

    // Si un ennemi est trouvé, diriger la fusée vers lui
    if (closestEnemy != nullptr) {
        DirectX::XMFLOAT3 targetDirection = DirectX::XMFLOAT3(closestEnemy->GetPosition().x - rocketPosition.x,
            closestEnemy->GetPosition().y - rocketPosition.y,
            closestEnemy->GetPosition().z - rocketPosition.z);
        float length = sqrt(targetDirection.x * targetDirection.x + targetDirection.y * targetDirection.y + targetDirection.z * targetDirection.z);
        m_Direction = DirectX::XMFLOAT3(targetDirection.x / length, targetDirection.y / length, targetDirection.z / length);
    }*/

    m_pEntity->Translate(m_Speed * m_Direction.x, m_Speed * m_Direction.y, m_Speed * m_Direction.z);
}