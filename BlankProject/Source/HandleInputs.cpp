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
#include "../../BlankProject/Source/GameManager.h"

float speed = 0.1f;
float lButtonCD = 0.0f;
float particleCD = 0.0f;

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
    Camera* cam = dynamic_cast<Camera*>(m_GameManager->GetMainCamera()->GetComponentByName("camera"));

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
    {
        if (speed <= 0.15f)
            speed += 0.001f;
        if (m_InputManager->GetCurrentState('S') == PRESSED || m_InputManager->GetCurrentState('S') == HELD ||
            (m_InputManager->GetCurrentState('W') == PRESSED || m_InputManager->GetCurrentState('W') == HELD))
        {
            if (particleCD >= 20.0f)
            {
                DirectX::XMFLOAT3 position = m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition;
                DirectX::XMFLOAT3 direction = m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorDirection;
                DirectX::XMFLOAT3 right;
                DirectX::XMStoreFloat3(&right, m_DX12Instance->m_pMainCamera->GetTransform()->GetRightVector());

                DirectX::XMFLOAT3 forward;
                DirectX::XMStoreFloat3(&forward, m_DX12Instance->m_pMainCamera->GetTransform()->GetForwardVector());

                // Convertir le vecteur forward en XMVECTOR
                DirectX::XMVECTOR forwardVector = XMLoadFloat3(&forward);

                // Obtenir l'inverse du vecteur
                DirectX::XMVECTOR inverseVector = XMVectorNegate(forwardVector);

                // Convertir le r�sultat en XMFLOAT3
                DirectX::XMFLOAT3 inverse;
                DirectX::XMStoreFloat3(&inverse, inverseVector);

                DirectX::XMFLOAT3 inverseRight = { inverse.x + right.x, inverse.y + right.y, inverse.z + right.z };
                DirectX::XMFLOAT3 inverseLeft = { inverse.x - right.x, inverse.y - right.y, inverse.z - right.z };

                m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
                m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(position.x - right.x * 5.0f + forward.x * 5, position.y - right.y * 5.0f + forward.y * 5, position.z - right.z * 5.0f + forward.z * 5);
                ParticleSystem* particleSys = dynamic_cast<ParticleSystem*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("particle-system"));
                particleSys->InitializeParticleSystem(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1));
                particleSys->CreateAtomsGroup(m_DX12Instance, 50.0f, 5.0f, 100 , inverse);
                ///////
                m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
                m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(position.x + right.x * 5.0f + forward.x * 5, position.y + right.y * 5.0f + forward.y * 5, position.z + right.z * 5.0f + forward.z * 5);
                ParticleSystem* particleSys2 = dynamic_cast<ParticleSystem*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("particle-system"));
                particleSys2->InitializeParticleSystem(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1));
                particleSys2->CreateAtomsGroup(m_DX12Instance, 50.0f, 5.0f, 100, inverse);

                particleCD = 0.0f;
            }
            if (cam->GetFov() > DirectX::XMConvertToRadians(60.0f));
                cam->SetFov(cam->GetFov() - DirectX::XMConvertToRadians(0.02f));
        }
        else
        {
            if (speed >= 0.10f)
                speed -= 0.001f;
            if (cam->GetFov() < DirectX::XMConvertToRadians(90.0f))
            {
                cam->SetFov(cam->GetFov() + DirectX::XMConvertToRadians(0.02f));
            }
        }
    }
    else
    {
        if (speed >= 0.10f)
            speed -= 0.001f;
        if (cam->GetFov() < DirectX::XMConvertToRadians(90.0f))
        {
            cam->SetFov(cam->GetFov() + 0.02f);
        }
            
    }
    if ((m_InputManager->GetCurrentState(VK_LBUTTON) == PRESSED || m_InputManager->GetCurrentState(VK_LBUTTON) == HELD) && lButtonCD >= 20.0f && currentstate == PLAYING)
    {
        //Bullet de Gauche
        m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance));
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("cube");
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new BulletScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
        dynamic_cast<BulletScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitBulletScript(0.2, 10, forwardVect, 0.1);
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
        dynamic_cast<BulletScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetComponentByName("script"))->InitBulletScript(0.2, 10, forwardVect, 0.1);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->SetCollider();
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorRotation.z);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(0.02f, 0.02f, 0.2f);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x - rightVect.x / 4 - upVect.x / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y - rightVect.y / 4 - upVect.y / 4, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z - rightVect.z / 4 - upVect.z / 4);
        dynamic_cast<Tags*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AddComponentByName("tags"))->AddTags("bullet");
        lButtonCD = 0.0f;
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
    particleCD += 1.0f;
    lButtonCD += 1.0f;
}

VOID HandleInputs::UpdateMouse() {
    

    // Ajoutez la rotation de la cam�ra en fonction des mouvements de la souris
    // Convertir les valeurs de d�placement en radians et les multiplier par un facteur de sensibilit�
    float sensitivity = 0.001f; // R�glage de la sensibilit� de la souris
    float rotationX = static_cast<float>(m_InputManager->GetMouseDelta()[0]) * sensitivity;
    float rotationY = static_cast<float>(m_InputManager->GetMouseDelta()[1]) * sensitivity;

    m_DX12Instance->m_pMainCamera->Rotate(rotationX, rotationY, 0.0f);

    m_DX12Instance->m_pMainCamComponent->ChangeForward();

    SetCursorPos(m_DX12Instance->mClientWidth / 2, m_DX12Instance->mClientHeight / 2);
    m_InputManager->GetLastMousePos()->x = m_DX12Instance->mClientWidth / 2;
    m_InputManager->GetLastMousePos()->y = m_DX12Instance->mClientHeight / 2;
    ScreenToClient(m_DX12Instance->m_handle, m_InputManager->GetLastMousePos());
}