#include "BlankProject.h"
#include "HandleCollisions.h"

HandleCollisions::HandleCollisions(DirectX12Instance* inst)
{
	m_DX12Instance = inst;
}

HandleCollisions::~HandleCollisions()
{
}

void HandleCollisions::UpdateCollisions()
{
	for (int i = 0; i < m_DX12Instance->m_ListEntities.size(); i++)
	{
		if (m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider") != nullptr &&
			dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingValue() == true)
		{
			for (int j = 0; j < dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().size(); j++)
			{
				dynamic_cast<Collider*>(m_DX12Instance->m_ListEntities.at(i)->GetComponentByName("collider"))->GetCollidingEntities().at(j)->SetDestroyValue(true);
			}
			m_DX12Instance->m_ListEntities.at(i)->SetDestroyValue(true);
		}
	}
}
