#include "Engine.h"
#include "Engine/Atom.h"
#include "DirectX12/MathHelper.h"

Atom::Atom()
{
	m_LifeTime = 0.0f;
	m_Speed = 0.0f;
	m_Direction = { 0.0f, 0.0f, 0.0f }; 
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
	m_Transform = struct Transform();
	m_Transform.Identity();
}

void Atom::CycleLife(float deltaTime)
{
	float newScale = (m_LifeTime - deltaTime) / deltaTime;

	m_Transform.Scale(newScale, newScale, newScale);
	m_Transform.Translate(m_Direction.x * m_Speed, m_Direction.y * m_Speed, m_Direction.z * m_Speed);
	m_Transform.UpdateMatrix();

	m_LifeTime -= deltaTime;

	//Apr�s l'appel de cette m�thode, v�rifier si m_LifeTime est inf�rieur � 0, dans le cas �ch�ant supprimer l'atom
	//Penser �galament � rescale l'atom sur tous les axes selon la dur�e de vie
	//Cr�er une instance transform et translate par rapport � la matrice world, la speed et la direction ?
}