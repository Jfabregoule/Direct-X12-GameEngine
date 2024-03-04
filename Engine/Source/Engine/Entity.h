#pragma once
#include <vector>
#include <string>
#include "Engine/Component.h"
#include "Engine/transform.h"
#include "DirectX12/Vertex.h"

class ID3D12Device;

class ENGINE_API Entity {
private:

	/*
	|---------------------------------------------------------------
	|							Attributs							|
	|---------------------------------------------------------------
	*/

	std::string					m_Name;
	std::vector <Component*>	m_ListComponent;//remplacer les int par la classe component quand elle sera faite
	Entity*						m_pParent;
	std::vector<Entity*>		m_Children;
	Transform					m_Transform;
	ID3D12Device*				m_pDevice;

	/*
	|---------------------------------------------------------------
	|							Methods								|
	|---------------------------------------------------------------
	*/
public:

	Entity(ID3D12Device* device);
	~Entity();

	std::string				GetName();
	void					SetName(std::string entityName);

	Entity*					GetParent();
	void					SetParent(Entity* parentEntity);

	std::vector<Entity*>	GetChildren();
	void					AddChildren(Entity* childEntity);

	Transform*				GetTransform();
	DirectX::XMFLOAT4X4*	GetTransformConvert();

	std::vector<Component*>	GetAllComponents();
	void AddComponentByName(std::string componentName);
	Component* GetComponentByName(std::string name);

	void Translate(float postionX, float positionY, float positionZ);
	void Rotate(float yaw, float pitch, float roll);
	void Scale(float scaleX, float scaleY, float scaleZ);

	void SetMesh(Vertex* vertices = nullptr);
	void UpdateEntity();
};