#include "Engine.h"
#include "Engine/Entity.h"
#include <vector>
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"
#include "Engine/MeshRenderer.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

Entity::Entity(ID3D12Device* device) {
	m_ListComponent = {};
	m_pParent = nullptr;
	m_Transform = struct Transform();
	m_Transform.Identity();
	m_pDevice = device;
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

Component* Entity::GetComponentByName(std::string name) {
	for (int i = 0; i < m_ListComponent.size(); i++) {
		if (m_ListComponent[i]->GetName() == name) {
			return m_ListComponent[i];
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
			Camera* camera = new Camera();
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

void	Entity::InitObject(string type)
{
	if (type == "camera")
	{
		//
	}
	else if (type == "cube" || type == "pyramid" || type == "pipe")
	{
		Component* meshRenderer = AddComponentByName("mesh_renderer");
		dynamic_cast<MeshRenderer*>(meshRenderer)->InitMeshRenderer(m_pDevice, type);
	}
	else {
		return;
	}
};

void Entity::UpdateEntity() {

	m_Transform.UpdateMatrix();

};

#pragma endregion