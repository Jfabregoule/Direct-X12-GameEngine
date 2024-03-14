#include "BlankProject.h"
#include "Ship.h"
#include "Engine/Entity.h"
#include "DirectX12/dx12Inst.h"
#include "BulletScript.h"
#include "Rocketscript.h"
#include "LaserScript.h"
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
    bullet->InitBulletScript(10, 5, forwardVect, 1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.01f, 0.01f, 0.1f);
    entity->Translate(m_pTransform->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_pTransform->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_pTransform->m_VectorPosition.z + rightVect.z/ 4 - upVect.z / 4);
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet", "bullet");

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
    entity->InitObject("cube", "textured", "bark");
    entity->AttachComponent(new BulletScript(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)));
    bullet = dynamic_cast<BulletScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("script"));
    bullet->InitBulletScript(10, 5, forwardVect, 1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.01f, 0.01f, 0.1f);
    entity->Translate(m_pTransform->m_VectorPosition.x - rightVect.x / 4 - upVect.x / 4, m_pTransform->m_VectorPosition.y - rightVect.y / 4 - upVect.y / 4, m_pTransform->m_VectorPosition.z - rightVect.z/ 4 - upVect.z / 4);
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet", "bullet");
    

};

VOID Ship::LaserShoot() {

    DirectX::XMFLOAT3 forwardVect = m_pTransform->GetForwardVector();
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMFLOAT3 upVect;
    DirectX::XMFLOAT3 rotateVect;
    DirectX::XMStoreFloat3(&rightVect, m_pTransform->GetRightVector());
    DirectX::XMStoreFloat3(&upVect, m_pTransform->GetUpVector());

    //Laser
    m_pInst->m_ListEntities.push_back(new Entity(m_pInst));
    Entity* entity = m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1);
    entity->InitObject("cube", "textured", "laser");
    entity->AttachComponent(new LaserScript(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)));
    LaserScript* laser = dynamic_cast<LaserScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("script"));
    laser->InitLaserScript(0.2, 10, forwardVect, 0.1f);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.09f, 0.1f, 4.0f);
    entity->Translate(m_pTransform->m_VectorPosition.x + rightVect.x * 0.8f - upVect.x / 2, m_pTransform->m_VectorPosition.y + rightVect.y * 0.8f - upVect.y / 2, m_pTransform->m_VectorPosition.z + rightVect.z * 0.8f - upVect.z / 2);
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet", "laser");

}; 

VOID Ship::RocketShoot() {
    DirectX::XMFLOAT3 forwardVect = m_pTransform->GetForwardVector();
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMFLOAT3 upVect;
    DirectX::XMFLOAT3 rotateVect;
    DirectX::XMStoreFloat3(&rightVect, m_pTransform->GetRightVector());
    DirectX::XMStoreFloat3(&upVect, m_pTransform->GetUpVector());

    //Rocket
    m_pInst->m_ListEntities.push_back(new Entity(m_pInst));
    Entity* entity = m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1);
    entity->InitObject("pyramid");
    entity->AttachComponent(new RocketScript(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)));
    RocketScript* rocket = dynamic_cast<RocketScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("script"));
    rocket->InitRocketScript(0.4, 20, forwardVect, 0.1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.3f, 0.3f, 1.5f);
    entity->Translate(m_pTransform->m_VectorPosition.x - rightVect.x * 0.8f - upVect.x / 2, m_pTransform->m_VectorPosition.y - rightVect.y * 0.8f - upVect.y / 2, m_pTransform->m_VectorPosition.z - rightVect.z * 0.8f - upVect.z / 2);
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet", "rocket");
}; 