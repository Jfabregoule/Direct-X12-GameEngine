#pragma once

#include "Engine.h"

#include <iostream>
#include <vector>

#include "Engine/Component.h"
#include "Engine/Atom.h"

class Entity;
class DirectX12Instance;

class ENGINE_API ParticleSystem : public Component
{
public:
	std::vector<Entity*>	m_Atoms;
	int						m_AtomsNumber;
	Entity*					m_SelfEntity;

	ParticleSystem();
	~ParticleSystem();

	void InitializeParticleSystem(Entity* particlesystem);

	void CreateAtomsGroup(DirectX12Instance* inst, int atomsNumber = 50 + rand() % 100);

	void Update(float dt, float* gameSpeed) override;
};