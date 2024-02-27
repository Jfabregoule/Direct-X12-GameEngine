#pragma once
#include <string>
#include <iostream>

using namespace std;

class Component
{
private:

	string m_Name;

public:

	Component(string name);

	~Component();

	string GetName() { return m_Name; };

	void SetName(string name) { m_Name = name; };
};