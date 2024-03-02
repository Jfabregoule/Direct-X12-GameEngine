#include "Engine.h"
#include "Component.h"

Component::Component()
{
	m_Name = "default";
}

Component::~Component()
{
	std::cout << "Destroying component : " << m_Name;
}

VOID Component::SetName(const char* name) {
	m_Name = name;

}