#pragma once
#include <string>
#include <iostream>

using namespace std;

class Component
{
protected:

	string m_Name;

public:

	Component();

	virtual ~Component();

	string GetName() { return m_Name; };

	void SetName(string name) { m_Name = name; };
};