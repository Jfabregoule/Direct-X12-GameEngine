#include "Engine.h"
#include "Engine/ParticleSystem.h"
#include "Engine/Entity.h"
#include <time.h>

ParticleSystem::ParticleSystem() : Component()
{
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
	m_AtomsNumber = atomsNumber;
	Entity* atom;
	for (int i = 0; i < m_AtomsNumber; i++)
	{
		srand(time(0));
		atom = new Entity(device);
		Atom* atomComponent = dynamic_cast<Atom*>(atom->AddComponentByName("atom"));
		atomComponent->InitializeAtom(0.1f + rand() % 5, 0.1f + rand() % 5, 0.1f + rand() % 10, 0.1f + rand() % 10, 0.1f + rand() % 10);
		m_Atoms.push_back(atom);
		m_Atoms.at(i)->InitObject("cube");
	}
}

void ParticleSystem::Update() 
{
	for (int ù = 0; ù < m_Atoms.size(); ù++)
	{
		dynamic_cast<Atom*>(m_Atoms.at(ù)->GetComponentByName("atom"))->CycleLife(m_DeltaTime);
		if (dynamic_cast<Atom*>(m_Atoms.at(ù)->GetComponentByName("atom"))->m_LifeTime <= 0) 
			m_Atoms.at(ù)->SetDestroyValue(true); 
	}

}