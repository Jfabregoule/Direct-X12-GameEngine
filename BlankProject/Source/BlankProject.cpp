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
        HWND handle;
        handle = Handle();
        Window *window = GetWindow();
        DirectX12Instance DX12Inst(handle);

        DX12Inst.InitGraphics();
        DX12Inst.InitCamera();
        DX12Inst.InitShaders();
        DX12Inst.InitRootSignature();
        DX12Inst.InitPipelineState();
        DX12Inst.CreateFencesAndEvents();
        DX12Inst.BuildBoxGeometry();


        MSG message;
        while (GameRunning) {
            while (PeekMessage(&message, handle, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            // Gérer les entrées de l'utilisateur pour déplacer la caméra
            HandleInput(DX12Inst);

            // Faire tourner automatiquement la caméra
            float deltaTime = 0.016f; // Par exemple, supposez un temps fixe entre les frames
            DX12Inst.camera.RotateAutomatically(deltaTime);

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

    VOID HandleInput(DirectX12Instance& DX12Inst) {
        // Gérer les entrées du clavier
        if (GetAsyncKeyState('W') & 0x8000) {
            DX12Inst.MoveCamera(0.0f, 0.0f, 0.1f); // Avancer
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            DX12Inst.MoveCamera(0.0f, 0.0f, -0.1f); // Reculer
        }
        if (GetAsyncKeyState('A') & 0x8000) {
            DX12Inst.MoveCamera(-0.1f, 0.0f, 0.0f); // Aller à gauche
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            DX12Inst.MoveCamera(0.1f, 0.0f, 0.0f); // Aller à droite
        }

        // Gérer les entrées de la souris pour le déplacement de la caméra
        POINT currentMousePos;
        GetCursorPos(&currentMousePos);
        float dx = static_cast<float>(currentMousePos.x - lastMousePos.x) * 0.001f;
        float dy = static_cast<float>(currentMousePos.y - lastMousePos.y) * 0.001f;
        DX12Inst.UpdateCamera(dx, dy, 0.0f);

        lastMousePos = currentMousePos;
    }
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
