#pragma once

#include <string>
#include <iostream>

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Component Class						                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Component Class

class Component
{
protected:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Attributs								        |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	std::string m_Name;

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                               Constructor/Destructor                                |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	Component();
	virtual ~Component();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									Getters/Setters										|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Getters And Setters

	std::string GetName() { return m_Name; };

	void SetName(const char* name);

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	virtual void Update(float dt, float* gameSpeed);

#pragma endregion

};

#pragma endregion