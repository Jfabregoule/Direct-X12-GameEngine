#include "Engine.h"
#include "Engine/Entity.h"
#include <vector>
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Script.h"
#include "Engine/Collider.h"
#include "Engine/Tags.h"
#include "Engine/Atom.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

Entity::Entity(DirectX12Instance* inst) {
	m_ListComponent = {};
	m_pParent = nullptr;
	m_Transform = struct Transform();
	m_Transform.Identity();
	m_pInst = inst;
	m_ToDestroy = false;
};

Entity::~Entity() {

};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Getters/Setters 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Getters And Setters

std::string Entity::GetName()
{
	return m_Name;
}

void Entity::SetName(std::string entityName)
{
	m_Name = entityName;
}

Entity* Entity::GetParent()
{
	return m_pParent;
}

void Entity::SetParent(Entity* parentEntity)
{
	m_pParent = parentEntity;
}

std::vector<Entity*> Entity::GetChildren()
{
	return m_Children;
}

void Entity::AddChildren(Entity* childEntity)
{
	m_Children.push_back(childEntity);
}

Transform* Entity::GetTransform()
{
	return &m_Transform;
}

DirectX::XMFLOAT4X4* Entity::GetTransformConvert()
{
	return &m_Transform.m_Matrix;
}

bool	Entity::GetDestroyValue()
{
	return m_ToDestroy;
}

void	Entity::SetDestroyValue(bool destroy)
{
	m_ToDestroy = destroy;
}

Component* Entity::GetComponentByName(std::string name) {
	if (m_ListComponent.size() > 0 && m_ListComponent.size() < 5000)
	{
		for (int i = 0; i < m_ListComponent.size(); i++) {
			if (m_ListComponent.at(i)->GetName() == name) {
				return m_ListComponent.at(i);
			}
		}
	}
	return nullptr;
}

std::vector<Component*> Entity::GetAllComponents()
{
	return m_ListComponent;
}

Component* Entity::AddComponentByName(std::string componentName)
{

	if (std::strcmp(componentName.c_str(), "camera") == 0) {
		if (GetComponentByName("camera") == nullptr)
		{
			Camera* camera = new Camera(GetTransform());
			m_ListComponent.push_back(camera);
			return camera;
		}
	}
	else if (std::strcmp(componentName.c_str(), "mesh_renderer") == 0)
	{
		if (GetComponentByName("mesh_renderer") == nullptr)
		{
			MeshRenderer* meshRenderer = new MeshRenderer();
			m_ListComponent.push_back(meshRenderer);
			return meshRenderer;
		}

	}
	else if (std::strcmp(componentName.c_str(), "script") == 0)
	{

		Script* scriptComponent = new Script();
		m_ListComponent.push_back(scriptComponent);
		return scriptComponent;

	}
	else if (std::strcmp(componentName.c_str(), "collider") == 0)
	{
		Collider* colliderComponent = new Collider();
		m_ListComponent.push_back(colliderComponent);
		return colliderComponent;
	}
	else if (std::strcmp(componentName.c_str(), "tags") == 0)
	{
		Tags* TagsComponent = new Tags();
		m_ListComponent.push_back(TagsComponent);
		return TagsComponent;
	}
	else if (std::strcmp(componentName.c_str(), "particle-system") == 0)
	{
		ParticleSystem* particleSystem = new ParticleSystem();
		m_ListComponent.push_back(particleSystem);
		return particleSystem;
	}
	else if (std::strcmp(componentName.c_str(), "atom") == 0)
	{
		Atom* atom = new Atom(this);
		m_ListComponent.push_back(atom);
		return atom;
	}
}

void Entity::AttachComponent(Component* component)
{
	m_ListComponent.push_back(component);
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Methods 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Methods

void	Entity::Translate(float postionX, float positionY, float positionZ) {
	m_Transform.Translate(postionX, positionY, positionZ);
};

void	Entity::Rotate(float yaw, float pitch, float roll) {
	m_Transform.Rotate(yaw, pitch, roll);
};

void	Entity::Scale(float scaleX, float scaleY, float scaleZ) {
	m_Transform.Scale(scaleX, scaleY, scaleZ);
};

#pragma region movment 

void Entity::Forward(float speed, float dT) {
	DirectX::XMFLOAT3 forwardVect = m_Transform.GetForwardVector();	
	Translate(forwardVect.x * speed * dT, forwardVect.y * speed * dT, forwardVect.z * speed * dT);
};
void Entity::Backward(float speed, float dT) {
	DirectX::XMFLOAT3 forwardVect = m_Transform.GetForwardVector();
	Translate(-forwardVect.x * speed * dT, -forwardVect.y * speed * dT, -forwardVect.z * speed * dT);
};
void Entity::StrafeLeft(float speed, float dT) {
	DirectX::XMFLOAT3 rightVect;
	DirectX::XMStoreFloat3(&rightVect, m_Transform.GetRightVector());
	Translate(-rightVect.x * speed * dT, -rightVect.y * speed * dT, -rightVect.z * speed * dT);
};
void Entity::StrafeRight(float speed, float dT) {
	DirectX::XMFLOAT3 rightVect;
	DirectX::XMStoreFloat3(&rightVect, m_Transform.GetRightVector());
	Translate(rightVect.x * speed * dT, rightVect.y * speed * dT, rightVect.z * speed * dT);
};
void Entity::Down(float speed, float dT) {
	Translate(0.0f, -1.0f * speed * dT, 0.0f);
};
void Entity::Up(float speed, float dT) {
	Translate(0.0f, 1.0f * speed * dT, 0.0f);
};

#pragma endregion

void Entity::InitObject(std::string type, std::string shader_type, std::string texture_name)
{
	if (type == "camera")
	{
		AddComponentByName("camera");
		Translate(0.0f, 0.0f, 0.0f);
	}
	else if (type == "cube" || type == "pyramid" || type == "pipe" || type == "sphere" || type == "skybox")
	{
		Component* meshRenderer = AddComponentByName("mesh_renderer");
		dynamic_cast<MeshRenderer*>(meshRenderer)->InitMeshRenderer(m_pInst, type, shader_type,texture_name);
	}
	else {
		return;
	}
};

void Entity::UpdateEntity(float dt) {

	for (int i = 0; i < m_ListComponent.size(); i++)
	{
		m_ListComponent.at(i)->Update(dt);
	}
	m_Transform.UpdateMatrix();

};

void Entity::SetCollider() {
	Collider* oue = dynamic_cast<Collider*>(AddComponentByName("collider"));
	oue->InitCollider(this, m_pInst->m_ListEntities);
}

bool Entity::HasTag(std::string tag)
{
	Tags* tagComponent = dynamic_cast<Tags*>(GetComponentByName("tags"));
	if (tagComponent != nullptr)
	{
		return tagComponent->HasTag(tag);
	}
	return false;
}

#pragma endregion