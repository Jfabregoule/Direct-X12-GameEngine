#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"
#include "GameManager.h"

BOOL GameRunning = TRUE;

POINT lastMousePos;

class BlankProject : public Engine::Simulation {

    // Application

public:

    /* - Application Constructor - */

    BlankProject() {};

    /* - Application Deconstructor - */

    ~BlankProject() {};


public:

    /* - Called to Setup our PerGameSettings - */

    VOID SetupPerGameSettings();

    /* - Called to Initialize the Application - */

    VOID Initialize() {
        //Shader shader;
        HWND handle;
        handle = Handle();
        Window *window = GetWindow();

        GameManager* gameManager = new GameManager();
        gameManager->Initialize(handle);

        DX12Inst.m_ListEntities.push_back(new Entity(&DX12Inst));
        DX12Inst.m_ListEntities.at(3)->InitObject("cube", "textured", "sky");
        DX12Inst.m_ListEntities.at(3)->SetCollider();
        DX12Inst.m_ListEntities.at(3)->Translate(10.0f, 10.0f, 2.0f);

        MSG message;
        while (GameRunning) {
            while (PeekMessage(&message, handle, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);     
                DispatchMessage(&message);
            }

            // Rendre la frame
            gameManager->Update();

            GameRunning = window->IsRunning();
        }
    };


    /* - Game Loop - Called on a loop while running - */

    VOID Update() { };

    VOID Close() { GameRunning = FALSE; }
};


ENTRYAPP(BlankProject)

VOID BlankProject::SetupPerGameSettings()
{
    /* - Set the Per Game Settings - */
    PerGameSettings::SetGameName(IDS_PERGAMENAME);
    PerGameSettings::SetShortName(IDS_SHORTNAME);
    PerGameSettings::SetMainIcon(IDI_MAINICON);
    PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}
