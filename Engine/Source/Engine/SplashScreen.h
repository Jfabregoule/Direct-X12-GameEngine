#pragma once

#include "Platform/Win32/Window.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									SplashScreen Namespace 								|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region SplashScreen Namespace

namespace SplashScreen {

	VOID ENGINE_API Open();
	VOID ENGINE_API Close();
	VOID ENGINE_API AddMessage(CONST WCHAR* message);

}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									SplashWindow Class 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region SplashWindow Class

class ENGINE_API SplashWindow : public Win32::Window {
private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Attributs 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	WCHAR m_outputMessage[MAX_NAME_STRING];

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |								Constructor/Destructor 									|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	SplashWindow();
	~SplashWindow();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Methods 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	virtual			LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

#pragma endregion

};

#pragma endregion