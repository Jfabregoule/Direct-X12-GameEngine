#pragma once
#include "Engine.h"
#include "Engine/Atom.h"
#include "Engine/Component.h"
#include <iostream>
#include <vector>

class Entity;
class DirectX12Instance;

class ENGINE_API ParticleSystem : public Component
{
public:
	std::vector<Entity*>	m_Atoms;
	int						m_AtomsNumber;
	float					m_DeltaTime;
	Entity*					m_SelfEntity;

	ParticleSystem();
	~ParticleSystem();

	void InitializeParticleSystem(Entity* particlesystem);

	void CreateAtomsGroup(DirectX12Instance* inst, float speed, float lifeTime, int atomsNumber = 50 + rand() % 100,  DirectX::XMFLOAT3 direction = {0, 0, 0});

	void Update() override;
};