#pragma once 

class ENGINE_API OEngine;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                               Namespace Engine                                      |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Namespace Engine

namespace Engine {

	enum  EngineMode : INT {
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_Engine;

	VOID ENGINE_API SetMode(EngineMode mode);
	EngineMode ENGINE_API GetMode();

	std::wstring ENGINE_API EngineModeToString();

}

#pragma endregion

using namespace Engine;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                  OEngine Class                                      |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region OEngine Class

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

#pragma endregion