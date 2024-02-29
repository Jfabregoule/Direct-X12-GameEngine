#pragma once
#include <vector>
#include <string>
#include "Engine/Component.h"
#include "Engine/transform.h"
#include "Engine/DirectX12Utils.h"

class Entity {
public:

	/*
	|---------------------------------------------------------------
	|							Attributs							|
	|---------------------------------------------------------------
	*/

	std::vector <Component*>	m_ListComponent;//remplacer les int par la classe component quand elle sera faite
	Entity* m_Parent;
	Transform					m_Transform;

	/*
	|---------------------------------------------------------------
	|							Methods								|
	|---------------------------------------------------------------
	*/

	Entity();
	~Entity();

	void SetPosition(float positionX, float positionY, float positionZ);
	void SetRotate(float yaw, float pitch, float roll);
	void SetScale(float scaleX, float scaleY, float scaleZ);

	Component* GetComponentByName(std::string name);
	void SetMeshRenderer(Vertex Vertices);
};