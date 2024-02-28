#include "Engine.h"
#include "Component.h"

Component::Component(string name)
{
	m_Name = name;
}

Component::~Component()
{
	cout << "Destroying component : " << m_Name;
}