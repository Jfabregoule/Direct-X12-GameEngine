#include "Engine/Entity.h"
#include <vector>
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"

class Component;
class MeshRenderer;

Entity::Entity() {
	m_ListComponent = {};
	m_Parent = nullptr;
	m_Transform = struct Transform();
};

Entity::~Entity() {

};

void Entity::SetPosition(float positionX, float positionY, float positionZ) {
	m_Transform.Translate(positionX, positionY, positionZ);
};

void Entity::SetRotate(float yaw, float pitch, float roll) {
	m_Transform.Rotate(yaw, pitch, roll);
};

void Entity::SetScale(float scaleX, float scaleY, float scaleZ) {
	m_Transform.Scale(scaleX, scaleY, scaleZ);
};

Component* Entity::GetComponentByName(std::string name) {
	for (int i = 0; i < m_ListComponent.size(); i++) {
		if (m_ListComponent[i]->GetName() == name) {
			return m_ListComponent[i];
		}
	}
}

void Entity::SetMeshRenderer(Vertex Vertices) {
	m_ListComponent.push_back(new MeshRenderer(Vertices));
};