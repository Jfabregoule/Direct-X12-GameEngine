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

GameManager::GameManager() {
};

GameManager::~GameManager() {

};

VOID	GameManager::Initialize(HWND handle) {
	m_WinHandle = handle;

	m_pDX12Inst = new DirectX12Instance(handle);
	m_pDX12Inst->Init();

    m_State = PLAYING;

	SetAsMainCamera(new Entity(m_pDX12Inst), m_pDX12Inst);

    m_pInputsHandle = new HandleInputs(m_pDX12Inst, this);
    m_pCollisionsHandle = new HandleCollisions(m_pDX12Inst);



    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(0)->InitObject("cube", "textured", "bark");
    m_pDX12Inst->m_ListEntities.at(0)->SetCollider();
    m_pDX12Inst->m_ListEntities.at(0)->Translate(0.0f, 0.0f, 2.0f);
    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(1)->InitObject("pyramid");
    m_pDX12Inst->m_ListEntities.at(1)->SetCollider();
    m_pDX12Inst->m_ListEntities.at(1)->Translate(2.0f, 0.0f, 10.0f);
    m_pDX12Inst->m_ListEntities.push_back(new Entity(m_pDX12Inst));
    m_pDX12Inst->m_ListEntities.at(2)->InitObject("cube", "textured", "victor");
    m_pDX12Inst->m_ListEntities.at(2)->SetCollider();
    m_pDX12Inst->m_ListEntities.at(2)->Translate(10.0f, 0.0f, 2.0f);


}

VOID    GameManager::Update() {

    m_pInputsHandle->Update();
    m_pCollisionsHandle->UpdateCollisions();
    m_pDX12Inst->Update();

}

VOID    GameManager::Clear() {

    m_pDX12Inst->ReleaseFrame();
    m_pDX12Inst->Cleanup();

}