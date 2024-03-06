#include "Engine.h"
#include "Engine/Atom.h"
#include <iostream>
#include <vector>

class ENGINE_API ParticleSystem
{
public:
	std::vector<Atom*> m_Atoms;

	ParticleSystem();
	~ParticleSystem();

	void CreateAtomsGroup(Atom* atom);

	void CycleAtoms(float deltaTime);
};