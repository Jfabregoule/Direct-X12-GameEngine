#pragma once
#include <vector>
#include <string>
#include "Engine/Component.h"
#include "Engine/transform.h"
#include "DirectX12/d3dUtil.h"

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

	void Translate(float postionX, float positionY, float positionZ);
	void Rotate(float yaw, float pitch, float roll);
	void Scale(float scaleX, float scaleY, float scaleZ);

	Component* GetComponentByName(std::string name);
	void SetMeshRenderer(Vertex Vertices);
};