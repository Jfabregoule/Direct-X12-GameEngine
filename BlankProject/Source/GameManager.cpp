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

	SetAsMainCamera(mainPlayer->GetEntity(), m_pDX12Inst);

    m_pInputsHandle = new HandleInputs(m_pDX12Inst, this);
    m_pCollisionsHandle = new HandleCollisions(m_pDX12Inst);

    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(0)->InitObject("cube");
    m_pDX12Inst->m_ListEntities.at(0)->SetCollider();
    m_pDX12Inst->m_ListEntities.at(0)->Translate(-5.5f, -3.0f, 6.0f);
    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(1)->InitObject("pyramid");
    m_pDX12Inst->m_ListEntities.at(1)->SetCollider();
    m_pDX12Inst->m_ListEntities.at(1)->Translate(-1.5f, -3.0f, 6.0f);
    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(2)->InitObject("pipe");
    m_pDX12Inst->m_ListEntities.at(2)->Translate(2.5f, -3.0f, 6.0f);
    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(3)->InitObject("sphere");
    m_pDX12Inst->m_ListEntities.at(3)->Translate(6.5f, -3.0f, 6.0f);
    //m_pDX12Inst->m_ListEntities.at(3)->InitObject("skybox", "textured", "sky");
    //m_pDX12Inst->m_ListEntities.at(3)->Scale(9.0f, 9.0f, 9.0f);
    //m_pDX12Inst->m_ListEntities.at(3)->SetCollider();

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
