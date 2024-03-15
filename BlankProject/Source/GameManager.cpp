#include "BlankProject.h"
#include "GameManager.h"
#include "Engine/DirectX12Utils.h"
#include "DirectX12/dx12Inst.h"
#include "Engine/MeshRenderer.h"
#include "Engine/InputManager.h"
#include "Engine/Tags.h"
#include "Engine/Collider.h"
#include "HandleInputs.h"
#include "BulletScript.h"
#include "EnemyScript.h"
#include "HandleCollisions.h"
#include "PlayerScript.h"
#include "ShipScript.h"
#include "Time.h"
#include "Map.h"

GameManager::GameManager() {
    
}

GameManager::~GameManager() {}

VOID GameManager::Initialize(HWND handle) {
    m_WinHandle = handle;

    m_pDX12Inst = new DirectX12Instance(handle);
    m_pDX12Inst->Init();

    m_State = PLAYING;

    Entity* mainPlayer = new Entity(m_pDX12Inst);
    PlayerScript* playerScript = new PlayerScript();
    ShipScript* shipScript = new ShipScript();
    mainPlayer->AttachComponent(playerScript);
    shipScript->Initialize(m_pDX12Inst, mainPlayer);
    mainPlayer->AttachComponent(shipScript);
    mainPlayer->AddComponentByName("tags");
    dynamic_cast<Tags*>(mainPlayer->GetComponentByName("tags"))->AddTags("ally");

    SetAsMainPlayer(mainPlayer, m_pDX12Inst);

    m_pInputsHandle = new HandleInputs(m_pDX12Inst, this);
    m_pCollisionsHandle = new HandleCollisions(m_pDX12Inst);

    Map m_Map(m_pMainPlayer,m_pDX12Inst);

    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(0)->InitObject("skybox", "textured", "sky");
    m_pDX12Inst->m_ListEntities.at(0)->Scale(9.0f, 9.0f, 9.0f);

    m_Map.GenerateEntities();



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
