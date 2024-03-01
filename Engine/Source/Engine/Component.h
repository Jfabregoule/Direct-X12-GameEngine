#pragma once
#include <string>
#include <iostream>

class Component
{
private:

	std::string m_Name;

public:

	Component(std::string name);

	~Component();

	std::string GetName() { return m_Name; };

	void SetName(std::string name) { m_Name = name; };
};