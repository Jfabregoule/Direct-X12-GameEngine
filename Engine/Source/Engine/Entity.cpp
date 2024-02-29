#include "Engine/Entity.h"
#include <vector>
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"

class Component;
class MeshRenderer;

#ifndef Vertex

struct Vertex {
	DirectX::XMFLOAT3 position;
};

#endif

Entity::Entity() {
	m_ListComponent = {};
	m_Parent = nullptr;
	m_Transform = struct Transform();
};

Entity::~Entity() {

};

void Entity::SetPosition() {
	m_Transform.SetPosition();
};

void Entity::SetRotate() {
	m_Transform.SetRotate();
};

void Entity::SetScale() {
	m_Transform.SetScale();
};

Component* Entity::GetComponentByName(std::string name) {
	for (int i = 0; i < m_ListComponent.size(); i++) {
		if (m_ListComponent[i].m_Name == name) {
			return m_ListComponent[i];
		}
	}
}

void Entity::SetMeshRenderer(Vertex Vertices) {
	m_ListComponent.push_back(new MeshRenderer(Vertices));
};