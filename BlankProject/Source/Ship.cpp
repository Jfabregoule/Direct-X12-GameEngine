#include "BlankProject.h"
#include "Ship.h"
#include "Engine/Entity.h"
#include "DirectX12/dx12Inst.h"
#include "BulletScript.h"
#include "Engine/transform.h"
#include "Engine/Tags.h"

Ship::Ship() {
	m_life = 5;
};

Ship::~Ship() {

}

VOID Ship::Initialize(DirectX12Instance* inst){

	m_pEntity = new Entity(inst);
    m_pInst = inst;
    m_pTransform = m_pEntity->GetTransform();

};

VOID Ship::Shoot() {

    DirectX::XMFLOAT3 forwardVect = m_pTransform->GetForwardVector();
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMFLOAT3 upVect;
    DirectX::XMFLOAT3 rotateVect;
    DirectX::XMStoreFloat3(&rightVect, m_pTransform->GetRightVector());
    DirectX::XMStoreFloat3(&upVect, m_pTransform->GetUpVector());

    //Bullet de Gauche

    
    m_pInst->m_ListEntities.push_back(new Entity(m_pInst));
    Entity* entity = m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1);
    entity->InitObject("cube");
    entity->AttachComponent(new BulletScript(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)));
    BulletScript* bullet = dynamic_cast<BulletScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("script"));
    bullet->InitBulletScript(20, 5, forwardVect, 1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.01f, 0.01f, 0.1f);
    entity->Translate(m_pTransform->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_pTransform->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_pTransform->m_VectorPosition.z + rightVect.z/ 4 - upVect.z / 4);
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("bullet");

    /*m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
    m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("cube");
    m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new BulletScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
    dynamic_cast<BulletScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitBulletScript(20, 5, forwardVect, 1);
    m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->SetCollider();
    m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.z);
    m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(0.02f, 0.02f, 0.2f);
    m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z + rightVect.z / 4 - upVect.z / 4);
    dynamic_cast<Tags*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("tags"))->AddTags("bullet");*/
    

    m_pInst->m_ListEntities.push_back(new Entity(m_pInst));
    entity = m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1);
    entity->InitObject("cube");
    entity->AttachComponent(new BulletScript(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)));
    bullet = dynamic_cast<BulletScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("script"));
    bullet->InitBulletScript(20, 5, forwardVect, 1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.01f, 0.01f, 0.1f);
    entity->Translate(m_pTransform->m_VectorPosition.x - rightVect.x / 4 - upVect.x / 4, m_pTransform->m_VectorPosition.y - rightVect.y / 4 - upVect.y / 4, m_pTransform->m_VectorPosition.z - rightVect.z/ 4 - upVect.z / 4);
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("bullet");
    

};