#pragma once
#include "Component.h"
#include <vector>
#include <DirectXMath.h>

class Entity;

class ENGINE_API Collider : public Component
{
private:

	Entity*					m_Self;
	std::vector<Entity*>	m_ListEntity;

	bool					m_IsColliding;
	std::vector<Entity*>	m_CollidingWith;

	DirectX::XMFLOAT3		m_CenterPoint = { 0.0f, 0.0f, 0.0f };
	float					m_Radius;

public:

	Collider();
	~Collider();

	void					InitCollider(Entity* self, std::vector<Entity*> listEntity);

	bool					GetCollidingValue()		{ return m_IsColliding; };
	std::vector<Entity*>	GetCollidingEntities()	{ return m_CollidingWith; };

	bool					CheckCollision(Entity* entity);

	void					Update(float dt) override;

};