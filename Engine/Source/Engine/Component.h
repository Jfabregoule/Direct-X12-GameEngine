#pragma once
#include <string>
#include <iostream>

class Component
{
protected:

	std::string m_Name;

public:

	Component();

	virtual ~Component();

	std::string GetName() { return m_Name; };

	void SetName(std::string name) { m_Name = name; };
};