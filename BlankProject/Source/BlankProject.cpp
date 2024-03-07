#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"
#include "Engine/DirectX12Utils.h"
#include "DirectX12/dx12Inst.h"
#include "Engine/Entity.h"
#include "Engine/MeshRenderer.h"
#include "Engine/InputManager.h"
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
        InputManager handleInputs(&DX12Inst);

        Component* addedComponent;

        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(0)->InitObject("cube");
        DX12Inst.m_ListEntities.at(0)->Translate(0.0f, 0.0f, 0.0f);
        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(1)->InitObject("cube");
        DX12Inst.m_ListEntities.at(1)->Translate(0.0f, 0.0f, 2.0f);
        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(2)->InitObject("pyramid");
        DX12Inst.m_ListEntities.at(2)->Translate(2.0f, 0.0f, 10.0f);
        DX12Inst.m_ListEntities.push_back(new Entity(DX12Inst.device));
        DX12Inst.m_ListEntities.at(3)->InitObject("cube");
        DX12Inst.m_ListEntities.at(3)->AttachComponent(new BulletScript(DX12Inst.m_ListEntities.at(3)));
        DirectX::XMFLOAT3 direction;
        DirectX::XMStoreFloat3(&direction, DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f));
        dynamic_cast<BulletScript*>(DX12Inst.m_ListEntities.at(3)->GetAllComponents().at(1))->InitBulletScript(0.1, 9, direction, 0.1);
        DX12Inst.m_ListEntities.at(3)->Translate(3.0f, 0.0f, 0.0f);


        MSG message;
        while (GameRunning) {
            while (PeekMessage(&message, handle, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);     
                DispatchMessage(&message);
            }

            // Rendre la frame
            handleInputs.Handle();
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
