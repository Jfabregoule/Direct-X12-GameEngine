#include "Engine.h"
#include "Engine/ParticleSystem.h"
#include "Engine/Entity.h"
#include <time.h>

ParticleSystem::ParticleSystem() : Component()
{
	m_Name = "particle-system";
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::InitializeParticleSystem()
{
	SetName("particle-system");
}

void ParticleSystem::CreateAtomsGroup(ID3D12Device* device, int atomsNumber)
{
	m_DeltaTime = 0.001f;
	m_AtomsNumber = atomsNumber;
	Entity* atom;
	srand(timeGetTime());
	DWORD old = timeGetTime();
	for (int i = 0; i < m_AtomsNumber; i++)
	{
		atom = new Entity(device);
		atom->InitObject("cube");
		Atom* atomComponent = dynamic_cast<Atom*>(atom->AddComponentByName("atom"));
		atomComponent->InitializeAtom(-5.0f + rand() % 5, 1.0f + rand() % 5, -5.0f + rand() % 10, -5.0f + rand() % 10, -5.0f + rand() % 10);
		m_Atoms.push_back(atom);
	}
	DWORD newt = timeGetTime();
	OutputDebugStringA(std::to_string(newt - old).c_str());
	OutputDebugStringA("\n");
}

void ParticleSystem::Update() 
{
	for (int � = 0; � < m_Atoms.size(); �++)
	{
		m_Atoms.at(�)->UpdateEntity();
		if (dynamic_cast<Atom*>(m_Atoms.at(�)->GetComponentByName("atom"))->m_LifeTime <= 0) 
			m_Atoms.at(�)->SetDestroyValue(true); 
	}

}