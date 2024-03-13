#pragma once
#include "Engine.h"
#include "DirectX12/MathHelper.h"
#include "Engine/transform.h"
#include "Engine/CubeMesh.h"
#include "Engine/Component.h"

using namespace DirectX;
class Entity;

class ENGINE_API Atom : public Component
{ //Créer un CubeMesh dans l'atom afin de pouvoir le draw ultérieurement
public:

	Entity* m_Self;
	float m_StartingLifeTime;
	float m_LifeTime;//Life time of the atom
	float m_Speed;//Movement speed of the atom
	XMFLOAT3 m_Direction;//Vector made of float coordinates for the direction of the atom 
	Transform* m_Transform;
	bool m_ToDraw, m_ToDestroy;

	Atom(Entity* self);
	virtual ~Atom();

	void InitializeAtom(float speed, float lifeTime, float xDir, float yDir, float zDir);

	void Update(float dt, float* gameSpeed) override;
};