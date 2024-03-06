#include "Engine.h"
#include "Engine/ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	m_Atoms = { };
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::CreateAtomsGroup(Atom* atom)
{
	m_Atoms.push_back(atom);
}

void ParticleSystem::CycleAtoms(float deltaTime)
{
	for (Atom* atom : m_Atoms)
	{
		atom->CycleLife(deltaTime);
	}
}