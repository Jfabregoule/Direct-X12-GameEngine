#include "Engine.h"
#include "Component.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |								Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

Component::Component()
{
	m_Name = "default";
}

Component::~Component()
{
	std::cout << "Destroying component : " << m_Name;
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Getters/Setters 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Getters And Setters

VOID Component::SetName(const char* name) {
	m_Name = name;

}

void Component::Update(float dt, float* gameSpeed)
{
}

#pragma endregion