#include "BlankProject.h"
#include "EnemyScript.h"
#include "Engine/Tags.h"
#include "Engine/Maths.h"
#include "ShipScript.h"

EnemyScript::EnemyScript()
{
	m_Name = "enemyscript";
}

EnemyScript::~EnemyScript()
{
}

void EnemyScript::InitEnemyScript(float speed, Entity* self, Entity* player) {

	m_Speed = speed;
    m_pSelf = self;
    m_pPlayer = player;
	m_CurrentState = AFK;
	m_pTransform = m_pSelf->GetTransform();

}

void EnemyScript::Update(float dt, float* gameSpeed)
{

	switch (m_CurrentState) {
		case AFK:
			UpdateAFK(dt, gameSpeed);
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

void EnemyScript::UpdateAFK(float dt, float* gameSpeed)
{
	CheckDistancePlayer();
}

void EnemyScript::UpdatePATHING(float dt, float* gameSpeed)
{
	m_pSelf->Forward(m_Speed, dt, gameSpeed);

	CheckDistancePath();

	CheckDistancePlayer();
}

void EnemyScript::UpdateTRIGGERED(float dt, float* gameSpeed)
{
	FocusOnPlayer();

	m_pTransform->UpdateMatrix();

    m_pSelf->Forward(m_Speed, dt, gameSpeed);

	CheckDistancePlayerOutOfRange();

	if(InternClock(dt))
		dynamic_cast<ShipScript*>(m_pSelf->GetComponentByName("shipscript"))->RocketShoot();
}

void EnemyScript::UpdateRETREAT(float dt, float* gameSpeed)
{
    m_pSelf->Forward(m_Speed, dt, gameSpeed);

    CheckDistanceSpawn();
}


VOID   EnemyScript::InitializeEnemy(DirectX12Instance* inst, DirectX::XMFLOAT3 path[4]) {

    InitPath(path);

    //Set de l'entité
    m_pSelf->InitObject("pyramid");
    m_pSelf->SetCollider();
    dynamic_cast<Tags*>(m_pSelf->AddComponentByName("tags"))->AddTags("enemy");
    m_pInst = inst;


    m_pTransform = m_pSelf->GetTransform();
    m_pSelf->Translate(m_Path[m_pathState].x, m_Path[m_pathState].y, m_Path[m_pathState].z);
    m_pTransform->UpdateMatrix();
    m_Spawn = m_Path[0];

    m_LastPos = m_pTransform->m_VectorPosition;

};

VOID EnemyScript::InitPath(DirectX::XMFLOAT3 path[4]) {

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

VOID EnemyScript::ChangeLastPos() {
    m_LastPos = m_pTransform->m_VectorPosition;
};

VOID EnemyScript::CheckDistancePath() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_Path[m_nextPathState]) <= 0.1) {

        m_pathState = m_nextPathState;
        m_nextPathState = (m_pathState + 1) % 4;

        ChangeDirection(m_Path[m_nextPathState]);

        //Shoot();
        SetCurrentState(PATHING);

    }
};

VOID EnemyScript::CheckDistancePlayer() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_pPlayer->GetTransform()->m_VectorPosition) <= 10) {

        OutputDebugString(L"Ennemy spoted");


        FocusOnPlayer();

        SetCurrentState(TRIGGERED);

        //Shoot();
    }
};

VOID EnemyScript::FocusOnPlayer() {

    ChangeDirection(m_pPlayer->GetTransform()->m_VectorPosition);
    m_pTransform->UpdateMatrix();

};

VOID EnemyScript::CheckDistancePlayerOutOfRange() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_pPlayer->GetTransform()->m_VectorPosition) >= 20) {

        ChangeDirection(m_Spawn);

        SetCurrentState(RETREAT);

    }

}

VOID EnemyScript::CheckDistanceSpawn() {

    if (Maths::GetNorm(m_pTransform->m_VectorPosition, m_Spawn) <= 1) {

        SetCurrentState(PATHING);

    }
}

VOID EnemyScript::ChangeDirection(DirectX::XMFLOAT3 pos) {

    m_pTransform->SetDirection(pos);
};

bool EnemyScript::InternClock(float dt) {

	m_clock += dt;
	if (m_clock >= 1.5) {
		m_clock = 0;
		return true;
	}

	return false;

}