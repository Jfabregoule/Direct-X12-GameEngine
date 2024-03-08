#include "Engine.h"
#include "Engine/Atom.h"
#include "DirectX12/MathHelper.h"

Atom::Atom() : Component()
{
}

Atom::~Atom()
{
}

void Atom::InitializeAtom(float speed, float lifeTime, float xDir, float yDir, float zDir)
{
	m_Speed = speed;
	m_LifeTime = lifeTime;
	m_Direction = { xDir, yDir, zDir };
	MathHelper::Normalize(&m_Direction.x, &m_Direction.y, &m_Direction.z);
}

void Atom::CycleLife(float deltaTime)
{
	m_LifeTime -= deltaTime;

	if (m_LifeTime <= 0)
		return;

	XMFLOAT3 currentScale = m_Transform.GetScaleVector();
	XMFLOAT3 newScale = { 1.0f - deltaTime, 1.0f - deltaTime, 1.0f - deltaTime };

	m_Transform.Scale(newScale.x, newScale.y, newScale.z);
	m_Transform.Translate(m_Direction.x * m_Speed * deltaTime, m_Direction.y * m_Speed * deltaTime, m_Direction.z * m_Speed * deltaTime);
	m_Transform.UpdateMatrix();

	//Après l'appel de cette méthode, vérifier si m_LifeTime est inférieur à 0, dans le cas échéant supprimer l'atom
	//Penser égalament à rescale l'atom sur tous les axes selon la durée de vie
	//Créer une instance transform et translate par rapport à la matrice world, la speed et la direction ?
}