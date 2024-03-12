#pragma once
#include "Engine.h"
#include "Engine/Atom.h"
#include "Engine/Component.h"
#include "DirectX12/d3dUtil.h"
#include <iostream>
#include <vector>

class Entity;

class ENGINE_API ParticleSystem : public Component
{
public:
	std::vector<Entity*> m_Atoms;
	int m_AtomsNumber;
	float m_DeltaTime;

	ParticleSystem();
	~ParticleSystem();

	void InitializeParticleSystem();

	void CreateAtomsGroup(ID3D12Device* device, int atomsNumber = 50 + rand() % 100);

	void Update() override;
};