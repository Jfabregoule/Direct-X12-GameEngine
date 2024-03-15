#include "Engine.h"

#include "Tags.h"

Tags::Tags()
{
	m_Name = "tags";
}

Tags::~Tags()
{
}

bool Tags::HasTag(std::string tag)
{
	for (int i = 0; i < m_Tags.size(); i++)
		if (m_Tags.at(i) == tag)
			return true;
	return false;
}
