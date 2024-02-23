#pragma once 

class ENGINE_API OEngine;
namespace Engine {

	enum  EngineMode : INT {
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_OlympusEngine;

	VOID ENGINE_API SetMode(EngineMode mode);
	EngineMode ENGINE_API GetMode();

	std::wstring ENGINE_API EngineModeToString();

}

using namespace Engine;
class ENGINE_API OEngine {

public:
	OEngine();
	~OEngine();

private:
	EngineMode m_EngineMode;

public:
	EngineMode GetEngineMode();
	VOID SetEngineMode(EngineMode mode);

};