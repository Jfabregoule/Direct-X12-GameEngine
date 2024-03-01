#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"
#include "Engine/DirectX12Utils.h"
#include "DirectX12/dx12Inst.h"
#include "DirectX12/DX12Camera.h"

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
        Shader shader;
        HWND handle;
        handle = Handle();
        Window *window = GetWindow();
        DirectX12Instance DX12Inst(handle);

        DX12Inst.InitGraphics();
        //DX12Inst.InitCamera();
        shader.InitializeShader(DX12Inst.device);
        DX12Inst.CreateFencesAndEvents();
        //DX12Inst.BuildBoxGeometry();


        MSG message;
        while (GameRunning) {
            while (PeekMessage(&message, handle, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);     
                DispatchMessage(&message);
            }

            // Rendre la frame
            DX12Inst.RenderFrame();

            GameRunning = window->IsRunning();
        }
        DX12Inst.ReleaseFrame();
        DX12Utils::ReportLiveObjectsUtils();
        DX12Inst.ReleasePipeline(); 
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
