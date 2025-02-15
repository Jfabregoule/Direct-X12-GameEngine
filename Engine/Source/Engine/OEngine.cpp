#include "Engine.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									  Engine Namespace 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Engine Namespace

namespace Engine {

	OEngine g_Engine;

	VOID SetMode(EngineMode mode)
	{
		g_Engine.SetEngineMode(mode);
	}


	EngineMode GetMode()
	{
		return g_Engine.GetEngineMode();
	}

	std::wstring ENGINE_API EngineModeToString()
	{
		switch (Engine::GetMode())
		{
		case EngineMode::DEBUG:		return L"Debug";
		case EngineMode::RELEASE:	return L"Release";
		case EngineMode::SERVER:	return L"Server";
		case EngineMode::EDITOR:	return L"Editor";
		default:     return L"None";
		}
	}
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Constructor/Destructor								|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

OEngine::OEngine()
{
#ifdef _DEBUG
	m_EngineMode = EngineMode::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif
}

OEngine::~OEngine()
{
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									   Getters/Setters 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Getters And Setters

EngineMode OEngine::GetEngineMode()
{
	return m_EngineMode;
}

VOID OEngine::SetEngineMode(EngineMode mode)
{
	m_EngineMode = mode;
}

#pragma endregion