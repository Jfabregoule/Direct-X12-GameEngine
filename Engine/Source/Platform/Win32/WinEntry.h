#include "Engine.h"

#include "IApplication.h"
#include "Common/CmdLineArgs.h"
#include "Engine/SplashScreen.h"


extern Win32::IApplication* EntryApplication();

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |										WinMain 										|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region WinMain

INT CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

	auto EntryApp = EntryApplication();

	PerGameSettings GameSettings;
	EntryApp->SetupPerGameSettings();



	CmdLineArgs::ReadArguments();

	Logger logger;

	EntryApp->PreInitialize();

	SplashScreen::Open(); 


	Sleep(3000);
	
	SplashScreen::Close();

	EntryApp->Initialize();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			EntryApp->Update();
		}
	}
	return 0;
}

#pragma endregion