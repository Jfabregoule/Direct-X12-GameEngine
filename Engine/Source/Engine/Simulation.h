#pragma once

#include "Engine/Shader.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                   Engine Namespace                                  |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Engine Namespace

namespace Engine {

	class ENGINE_API Simulation : public Win32::IApplication, public Win32::Window {

	public:
		Simulation();
		~Simulation();

		virtual VOID PreInitialize() override;

		virtual LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;


	};
}

#pragma endregion

