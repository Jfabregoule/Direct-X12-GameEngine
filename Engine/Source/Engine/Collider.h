#pragma once
#include "Engine.h"
#include "Component.h"
#include "CubeMesh.h"
#include "Entity.h"

class Collider : public Component {

private:

	CubeMesh* m_pBox;

	bool m_IsTrigger;
	bool m_IsTriggering;
	int (*pf)(int i, int b);

public:

	/*
	|---------------------------------------------------------------
	|						Init/Destroy							|
	|---------------------------------------------------------------
	*/

	Collider();
	~Collider();

	void InitCollider();
	void ColliderRelease();

	/*
	|---------------------------------------------------------------
	|						Getters/Setters							|
	|---------------------------------------------------------------
	*/

	CubeMesh* GetBox() { return m_pBox; };
	void SetIsTrigger(bool a) { m_IsTrigger = a; };
	bool GetIsTrigger() { return m_IsTrigger; };

	/*
	|---------------------------------------------------------------
	|						Getters/Setters							|
	|---------------------------------------------------------------
	*/

	void IsTrigger(Entity* entity);
	void CheckVertex();

};