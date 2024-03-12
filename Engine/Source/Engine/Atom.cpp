#include "Engine.h"
#include "Engine/Atom.h"
#include "DirectX12/MathHelper.h"
#include "Engine/Entity.h"

Atom::Atom(Entity* self) : Component()
{
	m_Self = self;
	m_Transform = self->GetTransform();
	m_Name = "atom";
}

Atom::~Atom()
{
}

void Atom::InitializeAtom(float speed, float lifeTime, float xDir, float yDir, float zDir)
{
	m_Speed = speed;
	m_StartingLifeTime = lifeTime;
	m_LifeTime = lifeTime;
	m_Direction = { xDir, yDir, zDir };
	MathHelper::Normalize(&m_Direction.x, &m_Direction.y, &m_Direction.z);
	m_Transform->Scale(0.2f, 0.2f, 0.2f);
}

void Atom::Update()
{
	float deltaTime = 0.002f;
	m_LifeTime -= deltaTime * 20.0f;

	if (m_LifeTime <= 0)
	{
		m_Self->SetDestroyValue(true);
	}

	XMFLOAT3 currentScale = m_Transform->GetScaleVector();
	XMFLOAT3 newScale = { 1.0f - deltaTime * 10, 1.0f - deltaTime * 10, 1.0f - deltaTime * 10 };

	m_Transform->Scale(newScale.x * m_StartingLifeTime / 5.0f, newScale.y * m_StartingLifeTime / 5.0f, newScale.z * m_StartingLifeTime / 5.0f);
	m_Transform->Translate(m_Direction.x * m_Speed * deltaTime * 10.0f, m_Direction.y * m_Speed * deltaTime * 10.0f, m_Direction.z * m_Speed * deltaTime * 10.0f);
	m_Transform->UpdateMatrix();

	//Après l'appel de cette méthode, vérifier si m_LifeTime est inférieur à 0, dans le cas échéant supprimer l'atom
	//Penser égalament à rescale l'atom sur tous les axes selon la durée de vie
	//Créer une instance transform et translate par rapport à la matrice world, la speed et la direction ?
}