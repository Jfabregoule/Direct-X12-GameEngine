#include "BlankProject.h"
#include "HandleInputs.h"
#include "DirectXMath.h"
#include "BulletScript.h"

float speed = 0.1f;

HandleInputs::HandleInputs(DirectX12Instance* inst)
{
	m_DX12Instance = inst;
	m_InputManager = new InputManager(m_DX12Instance);

}

HandleInputs::~HandleInputs()
{
}

void	HandleInputs::UpdateInputs() {

    m_InputManager->Handle();
    DirectX::XMFLOAT3 forwardVect;
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMStoreFloat3(&forwardVect, m_DX12Instance->m_pMainCamComponent->GetForwardVector());
    DirectX::XMStoreFloat3(&rightVect, m_DX12Instance->m_pMainCamComponent->GetRightVector());
    if (m_InputManager->GetCurrentState('W') == PRESSED || m_InputManager->GetCurrentState('W') == HELD)
        m_DX12Instance->m_pMainCamera->Translate(forwardVect.x * speed, forwardVect.y * speed, forwardVect.z * speed);
    else if (m_InputManager->GetCurrentState('Z') == PRESSED || m_InputManager->GetCurrentState('Z') == HELD)
        m_DX12Instance->m_pMainCamera->Translate(forwardVect.x * speed, forwardVect.y * speed, forwardVect.z * speed);
    if (m_InputManager->GetCurrentState('S') == PRESSED || m_InputManager->GetCurrentState('S') == HELD)
        m_DX12Instance->m_pMainCamera->Translate(-forwardVect.x * speed, -forwardVect.y * speed, -forwardVect.z * speed);
    if (m_InputManager->GetCurrentState('A') == PRESSED || m_InputManager->GetCurrentState('A') == HELD)
        m_DX12Instance->m_pMainCamera->Translate(-rightVect.x * speed, -rightVect.y * speed, -rightVect.z * speed);
    else if (m_InputManager->GetCurrentState('Q') == PRESSED || m_InputManager->GetCurrentState('Q') == HELD)
        m_DX12Instance->m_pMainCamera->Translate(-rightVect.x * speed, -rightVect.y * speed, -rightVect.z * speed);
    if (m_InputManager->GetCurrentState('D') == PRESSED || m_InputManager->GetCurrentState('D') == HELD)
        m_DX12Instance->m_pMainCamera->Translate(rightVect.x * speed, rightVect.y * speed, rightVect.z * speed);
    if (m_InputManager->GetCurrentState(VK_SPACE) == PRESSED || m_InputManager->GetCurrentState(VK_SPACE) == HELD)
        m_DX12Instance->m_pMainCamera->Translate(0.0f, 1.0f * speed, 0.0f);
    if (m_InputManager->GetCurrentState(VK_CONTROL) == PRESSED || m_InputManager->GetCurrentState(VK_CONTROL) == HELD)
        m_DX12Instance->m_pMainCamera->Translate(0.0f, -1.0f * speed, 0.0f);
    if (m_InputManager->GetCurrentState(VK_SHIFT) == PRESSED || m_InputManager->GetCurrentState(VK_SHIFT) == HELD)
        speed = 0.2f;
    else
        speed = 0.1f;
    if (m_InputManager->GetCurrentState(VK_SPACE) == PRESSED || m_InputManager->GetCurrentState(VK_SPACE) == HELD)
    {
        ShowCursor(TRUE);
    }
    if (m_InputManager->GetCurrentState(VK_LBUTTON) == PRESSED || m_InputManager->GetCurrentState(VK_LBUTTON) == HELD)
    {
        m_DX12Instance->m_ListEntities.push_back(new Entity(m_DX12Instance->device));
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->InitObject("cube");
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->AttachComponent(new BulletScript(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)));
        dynamic_cast<BulletScript*>(m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->GetAllComponents().at(1))->InitBulletScript(0.1, 50, forwardVect, 0.1);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Rotate(forwardVect.x, forwardVect.y, forwardVect.z);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Scale(0.05f, 0.05f, 0.2f);
        m_DX12Instance->m_ListEntities.at(m_DX12Instance->m_ListEntities.size() - 1)->Translate(m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.x, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.y, m_DX12Instance->m_pMainCamera->GetTransform()->m_VectorPosition.z);
    }

    m_DX12Instance->m_pMainCamComponent->ChangePos();
}