#include "Engine.h"
#include "Component.h"

Component::Component(std::string name)
{
	m_Name = name;
}

Component::~Component()
{
	std::cout << "Destroying component : " << m_Name;
}

VOID Component::SetName(const char* name) {
	m_Name = name;

}