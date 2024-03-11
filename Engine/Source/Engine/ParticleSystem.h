#pragma once
#include "Engine.h"
#include "Engine/Atom.h"
#include "Engine/Component.h"
<<<<<<< HEAD
=======
#include "DirectX12/d3dUtil.h"
>>>>>>> 3d3a4e4ea15fe5db6593c9b8ab5d7c0bf5dd9bdd
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

	void CreateAtomsGroup(ID3D12Device* device, int atomsNumber = 20 + rand() % 100);

	void Update() override;
};