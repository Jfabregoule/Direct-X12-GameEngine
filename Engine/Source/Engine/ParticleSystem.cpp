#include "Engine.h"
#include "Engine/ParticleSystem.h"
#include <time.h>
//
//ParticleSystem::ParticleSystem()
//{
//	//m_Atoms = { };
//	m_AtomsNumber = 0;
//	srand(time(0)); 
//}
//
//ParticleSystem::~ParticleSystem()
//{
//}
//
//void ParticleSystem::CreateAtomsGroup(ID3D12Device* device, int atomsNumber)
//{
//	m_AtomsNumber = atomsNumber;
//	Atom* atom;
//	for (int i = 0; i < m_AtomsNumber; i++)
//	{
//		srand(time(0));  
//		atom = new Atom(device);
//		atom->InitializeAtom(0.1f + rand() % 5, 0.1f + rand() % 5, 0.1f + rand() % 10, 0.1f + rand() % 10, 0.1f + rand() % 10);
//		m_Atoms.push_back(atom);
//	}
//}
//
//void ParticleSystem::CycleAtoms(float deltaTime)
//{
//	for (Atom* atom : m_Atoms)
//	{
//		atom->CycleLife(deltaTime);
//	}
//
//	for (int j = 0; j < m_Atoms.size(); j++)
//	{
//		if (m_Atoms[j]->m_LifeTime <= 0)
//			m_Atoms.erase(m_Atoms.begin() + j);
//	}
//}