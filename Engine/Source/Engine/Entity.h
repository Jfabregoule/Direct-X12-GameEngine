#pragma once
#include <vector>
#include <string>

struct Transform {};
class Component;

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

	void SetPosition();
	void SetRotate();
	void SetScale();

	Component* GetComponentByName(std::string name);
};