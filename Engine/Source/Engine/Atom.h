#pragma once
#include "Engine.h"
#include "DirectX12/MathHelper.h"
#include "Engine/transform.h"
#include "Engine/CubeMesh.h"
#include "Engine/Component.h"

using namespace DirectX;

class ENGINE_API Atom : public Component
{ //Cr�er un CubeMesh dans l'atom afin de pouvoir le draw ult�rieurement
public:
	float m_LifeTime;//Life time of the atom
	float m_Speed;//Movement speed of the atom
	XMFLOAT3 m_Direction;//Vector made of float coordinates for the direction of the atom 
	Transform m_Transform;
	bool m_ToDraw, m_ToDestroy;

	Atom();
	virtual ~Atom();

	void InitializeAtom(float speed, float lifeTime, float xDir, float yDir, float zDir);

	void CycleLife(float deltaTime);
};