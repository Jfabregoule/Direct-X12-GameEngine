#include "BlankProject.h"
#include "Enemy.h"s
#include "../../Engine/Source/Engine/Entity.h"
#include "EnemyScript.h"

Enemy::Enemy() {

};

Enemy::~Enemy() {

};

VOID Enemy::InitializeEnemy(DirectX12Instance* inst, DirectX::XMFLOAT3 path [4] ) {

    InitPath(path);

    //Set de l'entité
    m_pEntity = new Entity(inst);
    m_pInst = inst;
    m_pTransform = m_pEntity->GetTransform();
    m_pEntity->Translate(m_Path[0].x, m_Path[0].y, m_Path[0].z);

    m_LastPos = m_pTransform->m_VectorPosition;

    
    //Set du script
    m_Script = new EnemyScript(this);
    m_Script->InitEnemyScript(1, m_pTransform->GetForwardVector());
    m_pEntity->AttachComponent(m_Script);

};

VOID Enemy::InitPath(DirectX::XMFLOAT3 path[4]) {

    m_Path[0] = path[0];
    m_Path[1] = path[1];
    m_Path[2] = path[2];
    m_Path[3] = path[3];

    DirectX::XMVECTOR path1 = DirectX::XMLoadFloat3(&m_Path[0]);
    DirectX::XMVECTOR path2 = DirectX::XMLoadFloat3(&m_Path[1]);
    DirectX::XMVECTOR path3 = DirectX::XMLoadFloat3(&m_Path[2]);
    DirectX::XMVECTOR path4 = DirectX::XMLoadFloat3(&m_Path[3]);

    DirectX::XMVECTOR dir1 = DirectX::XMVectorSubtract(path2, path1);
    DirectX::XMVECTOR dir2 = DirectX::XMVectorSubtract(path3, path2);
    DirectX::XMVECTOR dir3 = DirectX::XMVectorSubtract(path4, path3);
    DirectX::XMVECTOR dir4 = DirectX::XMVectorSubtract(path1, path4);

    DirectX::XMStoreFloat3(&path[0], dir1);
    DirectX::XMStoreFloat3(&path[1], dir2);
    DirectX::XMStoreFloat3(&path[2], dir3);
    DirectX::XMStoreFloat3(&path[3], dir4);

};

VOID Enemy::ChangeLastPos() {
    m_LastPos = m_pTransform->m_VectorPosition;
};

