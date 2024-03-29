#include "BlankProject.h"

#include "DirectX12/dx12Inst.h"

#include "Engine/Entity.h"
#include "Engine/Tags.h"
#include "Engine/transform.h"

#include "ShipScript.h"
#include "BulletScript.h"
#include "Rocketscript.h"
#include "LaserScript.h"

ShipScript::ShipScript() {
    m_Name = "shipscript";
    m_Life = 20;
};

ShipScript::~ShipScript() {

}

void ShipScript::Initialize(DirectX12Instance* inst, Entity *self) {

    m_pEntity = self;
    m_pInst = inst;
    m_pTransform = m_pEntity->GetTransform();

};

void ShipScript::Shoot() {

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
    BulletScript* bullet = dynamic_cast<BulletScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("bulletscript"));
    bullet->InitBulletScript(10, 5, forwardVect, 1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.01f, 0.01f, 0.1f);
    entity->Translate(m_pTransform->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_pTransform->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_pTransform->m_VectorPosition.z + rightVect.z / 4 - upVect.z / 4);
    if (m_pEntity->HasTag("ally"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet");
    if (m_pEntity->HasTag("enemy"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("enemy", "enemyBullet");
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("bullet");

    m_pInst->m_ListEntities.push_back(new Entity(m_pInst));
    entity = m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1);
    entity->InitObject("cube");
    entity->AttachComponent(new BulletScript(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)));
    bullet = dynamic_cast<BulletScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("bulletscript"));
    bullet->InitBulletScript(10, 5, forwardVect, 1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.01f, 0.01f, 0.1f);
    entity->Translate(m_pTransform->m_VectorPosition.x - rightVect.x / 4 - upVect.x / 4, m_pTransform->m_VectorPosition.y - rightVect.y / 4 - upVect.y / 4, m_pTransform->m_VectorPosition.z - rightVect.z / 4 - upVect.z / 4);
    if (m_pEntity->HasTag("ally"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet");
    if (m_pEntity->HasTag("enemy"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("enemy", "enemyBullet");
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("bullet");


};

void ShipScript::LaserShoot() {

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
    LaserScript* laser = dynamic_cast<LaserScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("laserscript"));
    laser->InitLaserScript(0.2, 10, forwardVect, 0.1f);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.09f, 0.1f, 4.0f);
    entity->Translate(m_pTransform->m_VectorPosition.x + rightVect.x * 0.8f - upVect.x / 2, m_pTransform->m_VectorPosition.y + rightVect.y * 0.8f - upVect.y / 2, m_pTransform->m_VectorPosition.z + rightVect.z * 0.8f - upVect.z / 2);
    if (m_pEntity->HasTag("ally"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet");
    if (m_pEntity->HasTag("enemy"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("enemy", "enemyBullet");
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("laser");

};

void ShipScript::RocketShoot() {
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
    RocketScript* rocket = dynamic_cast<RocketScript*>(m_pInst->m_ListEntities.at(m_pInst->m_ListEntities.size() - 1)->GetComponentByName("rocketscript"));
    rocket->InitRocketScript(0.4, 10, forwardVect, 0.1);
    entity->SetCollider();
    entity->Rotate(m_pTransform->m_VectorRotation.y, m_pTransform->m_VectorRotation.x, m_pTransform->m_VectorRotation.z);
    entity->Scale(0.3f, 0.3f, 1.5f);
    entity->Translate(m_pTransform->m_VectorPosition.x - rightVect.x * 0.8f - upVect.x / 2, m_pTransform->m_VectorPosition.y - rightVect.y * 0.8f - upVect.y / 2, m_pTransform->m_VectorPosition.z - rightVect.z * 0.8f - upVect.z / 2);
    if (m_pEntity->HasTag("ally"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("ally", "allyBullet");
    if (m_pEntity->HasTag("enemy"))
        dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("enemy", "enemyBullet");
    dynamic_cast<Tags*>(entity->AddComponentByName("tags"))->AddTags("rocket");
};

void ShipScript::DecreaseLife(int dmg) {
    m_Life -= dmg;
    if (m_Life <= 0) {
        m_pEntity->SetDestroyValue(true);
    }
};