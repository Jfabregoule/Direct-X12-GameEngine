#include "BlankProject.h"
#include "GameManager.h"
#include "Engine/DirectX12Utils.h"
#include "DirectX12/dx12Inst.h"
#include "Engine/MeshRenderer.h"
#include "Engine/InputManager.h"
#include "HandleInputs.h"
#include "BulletScript.h"
#include "Engine/Collider.h"
#include "HandleCollisions.h"
#include "Player.h"
#include "Ship.h"
#include "Time.h"
#include "Enemy.h"
#include "Map.h"

GameManager::GameManager() {
    
}

GameManager::~GameManager() {}

VOID GameManager::Initialize(HWND handle) {
    m_WinHandle = handle;

    m_pDX12Inst = new DirectX12Instance(handle);
    m_pDX12Inst->Init();

    m_State = PLAYING;

    Player* mainPlayer = new Player();
    mainPlayer->Initialize(m_pDX12Inst);

    SetAsMainPlayer(mainPlayer, m_pDX12Inst);

    m_pInputsHandle = new HandleInputs(m_pDX12Inst, this);
    m_pCollisionsHandle = new HandleCollisions(m_pDX12Inst);

    Map m_Map;


    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(0)->InitObject("cube", "textured", "bark");
    //m_pDX12Inst->m_ListEntities.at(0)->SetCollider();
    //m_pDX12Inst->m_ListEntities.at(0)->Translate(20.0f, -20.0f, 2.0f);
    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(1)->InitObject("pyramid");
    //m_pDX12Inst->m_ListEntities.at(1)->Translate(2.0f, 0.0f, 10.0f);
    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(2)->InitObject("cube", "textured", "victor");
    //m_pDX12Inst->m_ListEntities.at(2)->SetCollider();
    //m_pDX12Inst->m_ListEntities.at(2)->Translate(10.0f, 0.0f, 20.0f);
    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(0)->InitObject("skybox", "textured", "sky");
    m_pDX12Inst->m_ListEntities.at(0)->Scale(9.0f, 9.0f, 9.0f);
    //m_pDX12Inst->m_ListEntities.at(3)->SetCollider();

    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(3)->InitObject("cube");
    //m_pDX12Inst->m_ListEntities.at(3)->Translate(5.0f, 0.0f, 5.0f);
    //m_pDX12Inst->m_ListEntities.at(3)->Scale(0.1f, 0.1f, 0.1f);
    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(4)->InitObject("cube");
    //m_pDX12Inst->m_ListEntities.at(4)->Translate(10.0f, 0.0f, 5.0f);
    //m_pDX12Inst->m_ListEntities.at(4)->Scale(0.1f, 0.1f, 0.1f);
    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(5)->InitObject("cube");
    //m_pDX12Inst->m_ListEntities.at(5)->Translate(10.0f, 0.0f, 10.0f);
    //m_pDX12Inst->m_ListEntities.at(5)->Scale(0.1f, 0.1f, 0.1f);
    //m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    //m_pDX12Inst->m_ListEntities.at(6)->InitObject("cube");
    //m_pDX12Inst->m_ListEntities.at(6)->Translate(5.0f, 0.0f, 10.0f);
    //m_pDX12Inst->m_ListEntities.at(6)->Scale(0.1f, 0.1f, 0.1f);

    m_Map.GenerateEntities(m_pDX12Inst);

    Enemy* enemy = new Enemy();
    DirectX::XMFLOAT3 tab[4] = {
        XMFLOAT3(40.0f,0.0f,0.0f),
        XMFLOAT3(10.0f,0.0f,5.0f),
        XMFLOAT3(5.0f,0.0f,0.0f),
        XMFLOAT3(5.0f,0.0f,10.0f)
    };
    enemy->InitializeEnemy(m_pDX12Inst, tab);
    m_pDX12Inst->m_ListEntities.push_back(enemy->GetEntity());



    m_LastUpdateTime = Time::GetCurrentTime();
    m_GameSpeed = 1.0f;
}

VOID GameManager::Update() {
    float currentTime = Time::GetCurrentTime();
    m_DeltaTime = currentTime - m_LastUpdateTime;
    m_LastUpdateTime = currentTime;

    m_pInputsHandle->Update(m_DeltaTime, &m_GameSpeed);
    m_pCollisionsHandle->UpdateCollisions(m_DeltaTime, &m_GameSpeed);
    m_pDX12Inst->Update(m_DeltaTime, &m_GameSpeed);
}

VOID GameManager::Clear() {
    m_pDX12Inst->ReleaseFrame();
    m_pDX12Inst->Cleanup();
}
