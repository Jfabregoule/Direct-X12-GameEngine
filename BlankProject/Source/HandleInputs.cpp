#include "BlankProject.h"
#include "DirectX12/dx12Inst.h"
#include "HandleInputs.h"
#include <DirectXMath.h>
#include "BulletScript.h"
#include "Engine/Collider.h"
#include "Engine/Tags.h"
#include "Engine/transform.h"
#include "Engine/Camera.h"
#include "Engine/Entity.h"
#include "GameManager.h"
#include "ShipScript.h"

float lButtonCD = 0.0f;
float rButtonCD = 0.0f;
float eButtonCD = 0.0f;

HandleInputs::HandleInputs(DirectX12Instance* inst, GameManager* gameManager)
{
	m_DX12Instance = inst;
	m_InputManager = new InputManager(m_DX12Instance);
    m_GameManager = gameManager;
    m_Speed = 10.0f;
    ShowCursor(FALSE);

}

HandleInputs::~HandleInputs()
{
}

void HandleInputs::Update(float dt, float *gameSpeed) {
    UpdateInputs(dt, gameSpeed);
    if (*m_GameManager->GetGameState() == PLAYING)
        UpdateMouse(gameSpeed);
    m_DX12Instance->m_pMainCamComponent->ChangePos();
}

void HandleInputs::UpdateInputs(float dt, float *gameSpeed) {

    GameState currentstate = *m_GameManager->GetGameState();

    m_InputManager->Handle();
    DirectX::XMFLOAT3 forwardVect = m_DX12Instance->m_pMainCamComponent->GetTransform()->GetForwardVector();
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMFLOAT3 upVect;
    DirectX::XMFLOAT3 rotateVect;
    DirectX::XMStoreFloat3(&rightVect, m_DX12Instance->m_pMainCamComponent->GetTransform()->GetRightVector());
    DirectX::XMStoreFloat3(&upVect, m_DX12Instance->m_pMainCamComponent->GetTransform()->GetUpVector());
    if ((m_InputManager->GetCurrentState('R') == PRESSED || m_InputManager->GetCurrentState('R') == HELD) && currentstate == PLAYING)
    {
        if (*m_GameManager->GetGameSpeed() == 1.0f)
            m_GameManager->SetGameSpeed(0.5f);
        else
            m_GameManager->SetGameSpeed(1.0f);
    }
        
    if ((m_InputManager->GetCurrentState('W') == PRESSED || m_InputManager->GetCurrentState('W') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Forward(m_Speed, dt, gameSpeed);
    else if ((m_InputManager->GetCurrentState('Z') == PRESSED || m_InputManager->GetCurrentState('Z') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Forward(m_Speed, dt, gameSpeed);
    if ((m_InputManager->GetCurrentState('S') == PRESSED || m_InputManager->GetCurrentState('S') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Backward(m_Speed, dt, gameSpeed);
    if ((m_InputManager->GetCurrentState('A') == PRESSED || m_InputManager->GetCurrentState('A') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->StrafeLeft(m_Speed, dt, gameSpeed);
    else if ((m_InputManager->GetCurrentState('Q') == PRESSED || m_InputManager->GetCurrentState('Q') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->StrafeLeft(m_Speed, dt, gameSpeed);
    if ((m_InputManager->GetCurrentState('D') == PRESSED || m_InputManager->GetCurrentState('D') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->StrafeRight(m_Speed, dt, gameSpeed);
    if ((m_InputManager->GetCurrentState(VK_SPACE) == PRESSED || m_InputManager->GetCurrentState(VK_SPACE) == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Up(m_Speed, dt, gameSpeed);
    if ((m_InputManager->GetCurrentState(VK_CONTROL) == PRESSED || m_InputManager->GetCurrentState(VK_CONTROL) == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Down(m_Speed, dt, gameSpeed);
    if ((m_InputManager->GetCurrentState(VK_SHIFT) == PRESSED || m_InputManager->GetCurrentState(VK_SHIFT) == HELD) && currentstate == PLAYING)
        m_Speed = 7.0f;
    else
        m_Speed = 4.0f;

    //Bullet
    if ((m_InputManager->GetCurrentState(VK_LBUTTON) == PRESSED || m_InputManager->GetCurrentState(VK_LBUTTON) == HELD) && lButtonCD >= 0.1f && currentstate == PLAYING)
    {
        dynamic_cast<ShipScript*>(m_GameManager->GetMainPlayer()->GetComponentByName("shipscript"))->Shoot();

        
        lButtonCD = 0.0f;
    }

    //Laser
    if ((m_InputManager->GetCurrentState('E') == PRESSED || m_InputManager->GetCurrentState('E') == HELD) && eButtonCD >= 1.0f && currentstate == PLAYING)
    {
        dynamic_cast<ShipScript*>(m_GameManager->GetMainPlayer()->GetComponentByName("shipscript"))->LaserShoot();


        eButtonCD = 0.0f;
    }

    //Rocket 
    if ((m_InputManager->GetCurrentState(VK_RBUTTON) == PRESSED || m_InputManager->GetCurrentState(VK_RBUTTON) == HELD) && rButtonCD >= 0.5f && currentstate == PLAYING)
    {
        dynamic_cast<ShipScript*>(m_GameManager->GetMainPlayer()->GetComponentByName("shipscript"))->RocketShoot();


        rButtonCD = 0.0f;
    }


    if ((m_InputManager->GetCurrentState(VK_ESCAPE) == PRESSED || m_InputManager->GetCurrentState(VK_ESCAPE) == HELD) && lButtonCD >= 0.5f)
    {
        switch (currentstate)
        {
        case PLAYING:
            m_GameManager->SetGameState(PAUSED);
            ShowCursor(TRUE);
            break;
        case PAUSED:
            m_GameManager->SetGameState(PLAYING);
            ShowCursor(FALSE);
            break;
        default:
            break;
        }
        lButtonCD = 0.0f;
    }
    lButtonCD += dt * *gameSpeed;
    rButtonCD += dt * *gameSpeed;
    eButtonCD += dt * *gameSpeed;
}

VOID HandleInputs::UpdateMouse(float* gameSpeed) {
    
    float sensitivity = 0.001f; // Réglage de la sensibilité de la souris
    float rotationX = static_cast<float>(m_InputManager->GetMouseDelta()[0]) * sensitivity * *gameSpeed;
    float rotationY = static_cast<float>(m_InputManager->GetMouseDelta()[1]) * sensitivity * *gameSpeed;

    m_DX12Instance->m_pMainCamera->Rotate(rotationX, rotationY, 0.0f);

    m_DX12Instance->m_pMainCamComponent->ChangeForward();

    SetCursorPos(m_DX12Instance->mClientWidth / 2, m_DX12Instance->mClientHeight / 2);
    m_InputManager->GetLastMousePos()->x = m_DX12Instance->mClientWidth / 2;
    m_InputManager->GetLastMousePos()->y = m_DX12Instance->mClientHeight / 2;
    ScreenToClient(m_DX12Instance->m_handle, m_InputManager->GetLastMousePos());
}