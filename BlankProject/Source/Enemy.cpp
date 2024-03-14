#include "BlankProject.h"
#include "Enemy.h"
#include "../../Engine/Source/Engine/Entity.h"
#include "EnemyScript.h"
#include "Engine/Maths.h" 
#include "DirectX12/dx12Inst.h"
#include "Engine/Tags.h"

Enemy::Enemy() {

};

Enemy::~Enemy() {

};

VOID Enemy::InitializeEnemy(DirectX12Instance* inst, DirectX::XMFLOAT3 path [4] ) {

    InitPath(path);

    //Set de l'entité
    m_pEntity = new Entity(inst);
    m_pEntity->InitObject("pyramid");
    m_pEntity->SetCollider();
    dynamic_cast<Tags*>(m_pEntity->AddComponentByName("tags"))->AddTags("enemy");
    //m_pEntity->Rotate(0.0f,0.0f,1.5f);
    m_pInst = inst;


    m_pTransform = m_pEntity->GetTransform();
    m_pEntity->Translate(m_Path[m_pathState].x, m_Path[m_pathState].y, m_Path[m_pathState].z);
    m_pTransform->UpdateMatrix();
    //ChangeDirection(m_Path[m_nextPathState]);
    m_Spawn = m_Path[0];

    //m_pTransform->Rotate(0.0f,1.5f,0.0f);


    m_LastPos = m_pTransform->m_VectorPosition;

    
    //Set du script
    m_Script = new EnemyScript(this);
    m_Script->InitEnemyScript(4, m_pTransform->GetForwardVector());
    m_pEntity->AttachComponent(m_Script);

    m_pPlayer = m_pInst->m_pMainCamera;

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

VOID Enemy::CheckDistancePath() {
    
    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_Path[m_nextPathState]) <= 0.1) {

        OutputDebugString(L"zob");


        m_pathState = m_nextPathState;
        m_nextPathState = (m_pathState + 1) % 4;

        ChangeDirection(m_Path[m_nextPathState]);

        //Shoot();
        m_Script->SetCurrentState(PATHING);

    }
};

VOID Enemy::CheckDistancePlayer() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_pPlayer->GetTransform()->m_VectorPosition) <= 10) {

        OutputDebugString(L"Ennemy spoted");


        FocusOnPlayer();

        m_Script->SetCurrentState(TRIGGERED);

        //Shoot();
    }
};

VOID Enemy::FocusOnPlayer() {

    ChangeDirection(m_pPlayer->GetTransform()->m_VectorPosition);
    m_pTransform->UpdateMatrix();

};

VOID Enemy::CheckDistancePlayerOutOfRange() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_pPlayer->GetTransform()->m_VectorPosition) >= 20) {

        ChangeDirection(m_Spawn);

        m_Script->SetCurrentState(RETREAT);

    }

}

VOID Enemy::CheckDistanceSpawn() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_Spawn) <= 1) {

        m_Script->SetCurrentState(PATHING);

    }
};

VOID Enemy::ChangeDirection(DirectX::XMFLOAT3 pos) {

    m_pTransform->SetDirection(pos);
};
