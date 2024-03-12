#include "BlankProject.h"
#include "DirectX12/dx12Inst.h"
#include "HandleInputs.h"
#include <DirectXMath.h>
#include "BulletScript.h"
#include "RocketScript.h"
#include "LaserScript.h"
#include "Engine/Collider.h"
#include "Engine/Tags.h"
#include "Engine/transform.h"
#include "Engine/Camera.h"
#include "Engine/Entity.h"
#include "../../BlankProject/Source/GameManager.h"

float speed = 0.1f;
float lButtonCD = 0.0f;

HandleInputs::HandleInputs(DirectX12Instance* inst, GameManager* gameManager)
{
	m_DX12Instance = inst;
	m_InputManager = new InputManager(m_DX12Instance);
    m_GameManager = gameManager;
    ShowCursor(FALSE);

}

HandleInputs::~HandleInputs()
{
}

void HandleInputs::Update() {
    UpdateInputs();
    if (*m_GameManager->GetGameState() == PLAYING)
        UpdateMouse();
    m_DX12Instance->m_pMainCamComponent->ChangePos();
}

void HandleInputs::UpdateInputs() {

    GameState currentstate = *m_GameManager->GetGameState();

    m_InputManager->Handle();
    DirectX::XMFLOAT3 forwardVect;
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMFLOAT3 upVect;
    DirectX::XMFLOAT3 rotateVect;
    DirectX::XMStoreFloat3(&forwardVect, m_DX12Instance->m_pMainCamComponent->GetTransform()->GetForwardVector());
    DirectX::XMStoreFloat3(&rightVect, m_DX12Instance->m_pMainCamComponent->GetTransform()->GetRightVector());
    DirectX::XMStoreFloat3(&upVect, m_DX12Instance->m_pMainCamComponent->GetTransform()->GetUpVector());
    if ((m_InputManager->GetCurrentState('W') == PRESSED || m_InputManager->GetCurrentState('W') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Forward(speed);
    else if ((m_InputManager->GetCurrentState('Z') == PRESSED || m_InputManager->GetCurrentState('Z') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Forward(speed);
    if ((m_InputManager->GetCurrentState('S') == PRESSED || m_InputManager->GetCurrentState('S') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Backward(speed);
    if ((m_InputManager->GetCurrentState('A') == PRESSED || m_InputManager->GetCurrentState('A') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->StrafeLeft(speed);
    else if ((m_InputManager->GetCurrentState('Q') == PRESSED || m_InputManager->GetCurrentState('Q') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->StrafeLeft(speed);
    if ((m_InputManager->GetCurrentState('D') == PRESSED || m_InputManager->GetCurrentState('D') == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->StrafeRight(speed);
    if ((m_InputManager->GetCurrentState(VK_SPACE) == PRESSED || m_InputManager->GetCurrentState(VK_SPACE) == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Up(speed);
    if ((m_InputManager->GetCurrentState(VK_CONTROL) == PRESSED || m_InputManager->GetCurrentState(VK_CONTROL) == HELD) && currentstate == PLAYING)
        m_GameManager->GetMainCamera()->Down(speed);
    if ((m_InputManager->GetCurrentState(VK_SHIFT) == PRESSED || m_InputManager->GetCurrentState(VK_SHIFT) == HELD) && currentstate == PLAYING)
        speed = 0.15f;
    else
        speed = 0.1f;


    if ((m_InputManager->GetCurrentState(VK_RSHIFT) == PRESSED || m_InputManager->GetCurrentState(VK_LBUTTON) == HELD) && lButtonCD >= 20.0f && currentstate == PLAYING)
    {
        //Laser
        m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("cube");
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new LaserScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
        dynamic_cast<LaserScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitLaserScript(0.2, 50, forwardVect, 0.1);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->SetCollider();
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.z);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(1.0f, 1.0f, 3.0f);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z + rightVect.z / 4 - upVect.z / 4);
        dynamic_cast<Tags*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("tags"))->AddTags("laser");
    }

    if ((m_InputManager->GetCurrentState(VK_LBUTTON) == PRESSED || m_InputManager->GetCurrentState(VK_LBUTTON) == HELD) && lButtonCD >= 20.0f && currentstate == PLAYING)
    {
        //Bullet de Gauche
        m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("cube");
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new BulletScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
        dynamic_cast<BulletScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitBulletScript(0.2, 50, forwardVect, 0.1);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->SetCollider();
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.z);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(0.02f, 0.02f, 0.2f);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z + rightVect.z / 4 - upVect.z / 4);
        dynamic_cast<Tags*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("tags"))->AddTags("bullet");
        /////////////////////////////////////////////
        //Bullet de Droite
        m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("cube");
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new BulletScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
        dynamic_cast<BulletScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitBulletScript(0.2, 50, forwardVect, 0.1);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->SetCollider();
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.z);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(0.02f, 0.02f, 0.2f);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x - rightVect.x / 4 - upVect.x / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y - rightVect.y / 4 - upVect.y / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z - rightVect.z / 4 - upVect.z / 4);
        dynamic_cast<Tags*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("tags"))->AddTags("bullet");
        lButtonCD = 0.0f;
    }
    if ((m_InputManager->GetCurrentState(VK_RBUTTON) == PRESSED || m_InputManager->GetCurrentState(VK_LBUTTON) == HELD) && lButtonCD >= 20.0f && currentstate == PLAYING)
    {
        //Rocket
        m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("pyramid");
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new RocketScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
        dynamic_cast<RocketScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitRocketScript(0.2, 50, forwardVect, 0.1);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->SetCollider();
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.z);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(1.0f, 1.0f, 1.0f);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x + rightVect.x / 4 - upVect.x / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y + rightVect.y / 4 - upVect.y / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z + rightVect.z / 4 - upVect.z / 4);
        dynamic_cast<Tags*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("tags"))->AddTags("rocket");
    }
    if ((m_InputManager->GetCurrentState(VK_ESCAPE) == PRESSED || m_InputManager->GetCurrentState(VK_ESCAPE) == HELD) && lButtonCD >= 20.0f)
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
    lButtonCD += 1.0f;
}

VOID HandleInputs::UpdateMouse() {
    

    // Ajoutez la rotation de la caméra en fonction des mouvements de la souris
    // Convertir les valeurs de déplacement en radians et les multiplier par un facteur de sensibilité
    float sensitivity = 0.001f; // Réglage de la sensibilité de la souris
    float rotationX = static_cast<float>(m_InputManager->GetMouseDelta()[0]) * sensitivity;
    float rotationY = static_cast<float>(m_InputManager->GetMouseDelta()[1]) * sensitivity;

    m_DX12Instance->m_pMainCamera->Rotate(rotationX, rotationY, 0.0f);

    m_DX12Instance->m_pMainCamComponent->ChangeForward();

    SetCursorPos(m_DX12Instance->mClientWidth / 2, m_DX12Instance->mClientHeight / 2);
    m_InputManager->GetLastMousePos()->x = m_DX12Instance->mClientWidth / 2;
    m_InputManager->GetLastMousePos()->y = m_DX12Instance->mClientHeight / 2;
    ScreenToClient(m_DX12Instance->m_handle, m_InputManager->GetLastMousePos());
}