#include "BlankProject.h"
#include "HandleCollisions.h"
#include "Engine/Entity.h"
#include "Engine/ParticleSystem.h"

HandleCollisions::HandleCollisions(DirectX12Instance* inst)
{
	m_DX12Instance = inst;
}

HandleCollisions::~HandleCollisions()
{
}

void HandleCollisions::UpdateCollisions(float dt, float* gameSpeed)
{
	for (int i = 0; i < m_DX12Instance->m_ListEntities.size(); i++)
	{
		if (m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider") != nullptr &&
			dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingValue() == true)
		{
			for (int j = 0; j < dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().size(); j++)
			{
				if ((m_DX12Instance->m_ListEntities.at(i)->HasTag("ally") && dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().at(j)->HasTag("enemy")) ||
					(m_DX12Instance->m_ListEntities.at(i)->HasTag("enemy") && dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().at(j)->HasTag("ally")))
				{
					XMFLOAT3 position = dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().at(j)->GetTransform()->m_VectorPosition;
					dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().at(j)->SetDestroyValue(true);
					m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
					m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(position.x, position.y, position.z);
					ParticleSystem* particleSys = dynamic_cast<ParticleSystem*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("particle-system"));
					particleSys->InitializeParticleSystem(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1));
					particleSys->CreateAtomsGroup(m_DX12Instance);
					m_DX12Instance->m_ListEntities.at(i)->SetDestroyValue(true);
				}
			}
		}
	}
}
