#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"
#include "Engine/DirectX12Utils.h"
#include "DirectX12/dx12Inst.h"
#include "Engine/Entity.h"
#include "Engine/MeshRenderer.h"
#include "Engine/InputManager.h"
#include "HandleInputs.h"
#include "BulletScript.h"

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
        DirectX12Instance DX12Inst(handle);

        DX12Inst.Init();
        HandleInputs handleInputs(&DX12Inst);

        Component* addedComponent;

        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(0)->InitObject("pipe");
        DX12Inst.m_ListEntities.at(0)->Translate(0.0f, 0.0f, 0.0f);
        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(1)->InitObject("cube");
        DX12Inst.m_ListEntities.at(1)->Translate(0.0f, 0.0f, 2.0f);
        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(2)->InitObject("pyramid");
        DX12Inst.m_ListEntities.at(2)->Translate(2.0f, 0.0f, 10.0f);

        MSG message;
        while (GameRunning) {
            while (PeekMessage(&message, handle, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);     
                DispatchMessage(&message);
            }

            // Rendre la frame
            handleInputs.UpdateInputs();
            DX12Inst.Update();

            GameRunning = window->IsRunning();
        }
        DX12Inst.ReleaseFrame();
        DX12Inst.Cleanup();
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
