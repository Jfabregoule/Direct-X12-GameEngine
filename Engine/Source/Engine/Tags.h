#pragma once
#include "Component.h"
#include <vector>
#include <string>

class ENGINE_API Tags : public Component {

private:

	std::vector<std::string>	m_Tags;

public:

	Tags();
	~Tags();

	std::vector<std::string> GetTags() { return std::vector<std::string>(); };

	template<typename... Args>
	void AddTags(const std::string& tag, Args... args) {
		m_Tags.push_back(tag);
		if constexpr (sizeof...(args) > 0) {
			AddTags(args...);
		}
	}

	bool HasTag(std::string tag);
};