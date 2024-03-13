#include "Engine.h"
#include "Collider.h"
#include "Entity.h"
#include "MeshRenderer.h"

Collider::Collider()
{
	m_Name = "collider";
}

Collider::~Collider()
{
}

void Collider::InitCollider(Entity* self, std::vector<Entity*> listEntity)
{
	m_ListEntity = listEntity;
	m_Self = self;
	m_CenterPoint = {0.0f, 0.0f, 0.0f};
}

bool Collider::CheckCollision(Entity* entity)
{
	DirectX::XMVECTOR	Centertmp;
	DirectX::XMVECTOR	Externtmp;
	float		distance;
	Collider* entityCollider = dynamic_cast<Collider*>(entity->GetComponentByName("collider"));
	if (entityCollider == nullptr || entityCollider == this)
		return false;
	Centertmp = DirectX::XMLoadFloat3(&m_CenterPoint);
	Externtmp = DirectX::XMLoadFloat3(&entity->GetTransform()->m_VectorPosition);
	distance = DirectX::XMVector3Length(XMVectorSubtract(Centertmp, Externtmp)).m128_f32[0];

	m_Radius = ((m_Self->GetTransform()->m_VectorScale.x + entity->GetTransform()->m_VectorScale.x) / 2 +
		(m_Self->GetTransform()->m_VectorScale.y + entity->GetTransform()->m_VectorScale.y) / 2 +
		(m_Self->GetTransform()->m_VectorScale.z + entity->GetTransform()->m_VectorScale.z) / 2) / 3;
	if (m_Radius * 2 > distance)
		return true;
	return false;
}

void Collider::Update(float dt, float* gameSpeed)
{
	m_CenterPoint = m_Self->GetTransform()->m_VectorPosition;
	for (int i = 0; i < m_ListEntity.size(); i++)
	{
		if (m_ListEntity.at(i)->GetDestroyValue() == true)
			m_ListEntity.erase(m_ListEntity.begin() + i);
		else if (CheckCollision(m_ListEntity.at(i)))
		{
			m_IsColliding = true;
			m_CollidingWith.push_back(m_ListEntity.at(i));
		}
	}
}
