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

void ParticleSystem::InitializeParticleSystem(Entity* particlesystem)
{
	m_SelfEntity = particlesystem;
	SetName("particle-system");
}

void ParticleSystem::CreateAtomsGroup(DirectX12Instance* inst, float speed, float lifeTime, int atomsNumber, DirectX::XMFLOAT3 direction)
{
	m_DeltaTime = 0.1f;
	m_AtomsNumber = atomsNumber;
	int atomSpeed = speed + 1;
	int atomLifeTime = lifeTime + 1;
	Entity* atom;
	srand(timeGetTime());
	DWORD old = timeGetTime();
	for (int i = 0; i < m_AtomsNumber; i++)
	{
		XMFLOAT3	position = m_SelfEntity->GetTransform()->m_VectorPosition;
		atom = new Entity(inst);
		atom->Translate(position.x, position.y, position.z);
		atom->InitObject("cube");
		Atom* atomComponent = dynamic_cast<Atom*>(atom->AddComponentByName("atom"));
		if (direction.x == 0 && direction.y == 0 && direction.z == 0)
			atomComponent->InitializeAtom(-5.0f + rand() % 5, 1.0f + rand() % 5, -5.0f + rand() % 10, -5.0f + rand() % 10, -5.0f + rand() % 10);
		else
			atomComponent->InitializeAtom(1.0f + rand() % atomSpeed, 1.0f + rand() % atomLifeTime, ((direction.x - direction.x * 0.2f) * 100000 + rand() % int((direction.x - direction.x * 1.2f) * 100000)) * 0.00001, ((direction.y - direction.y * 0.2f) * 100000 + rand() % int((direction.y - direction.y * 1.2f) * 100000)) * 0.00001, ((direction.z - direction.z * 0.2f) * 100000 + rand() % int((direction.z - direction.z * 1.2f) * 100000)) * 0.00001);
		m_Atoms.push_back(atom);
	}
	DWORD newt = timeGetTime();
}

void ParticleSystem::Update() 
{
	for (int i = 0; i < m_Atoms.size(); i++)
		m_Atoms.at(i)->UpdateEntity();
	if (m_Atoms.size() == 0)
		m_SelfEntity->SetDestroyValue(true);

}