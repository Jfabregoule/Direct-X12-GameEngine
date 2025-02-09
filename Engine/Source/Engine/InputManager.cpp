#include "Engine.h"
#include "InputManager.h"
#include "Engine/Camera.h"
#include "Engine/Entity.h"
#include <cmath> // Inclure la biblioth�que cmath pour utiliser la fonction radians

float speed = 0.1f;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |							    Constructor/Destructor 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

InputManager::InputManager(DirectX12Instance* inst) {
    // Initialise tous les �tats des touches � IDLE
    for (int i = 0; i < 256; ++i) {
        keys[i].currentState = IDLE;
        keys[i].previousState = IDLE;
    }
    dx12Inst = inst;

    GetCursorPos(&lastMousePos);
    ScreenToClient(dx12Inst->m_handle, &lastMousePos);
    mousePos = lastMousePos;
}

InputManager::~InputManager() {}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Methods 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Methods

void InputManager::Handle() {
    
    
    // Boucle � travers toutes les touches pour d�tecter les �tats
    for (int i = 0; i < 256; ++i) {
        if (GetAsyncKeyState(i) & 0x8000) {
            keys[i].newState = PRESSED;
        }
        else {
            keys[i].newState = RELEASED;
        }
    }

    // Obtenez la position actuelle de la souris
    GetCursorPos(&mousePos);
    ScreenToClient(dx12Inst->m_handle, &mousePos);

    // Calculez les diff�rences de position de la souris entre les cadres
    mouseDelta[0] = mousePos.x - lastMousePos.x;
    mouseDelta[1] = mousePos.y - lastMousePos.y;

    lastMousePos = mousePos;
    // Mise � jour de la position pr�c�dente de la souris

    UpdateState();
}

POINT* InputManager::GetLastMousePos() {
    return &lastMousePos;
}

POINT* InputManager::GetCurrentMousePos() {
    return &mousePos;
}

float *InputManager::GetMouseDelta()
{
    return mouseDelta;
}


void InputManager::UpdateState() {
    // Met � jour les �tats des touches
    for (int i = 0; i < 256; ++i) {
        keys[i].previousState = keys[i].currentState;
        keys[i].currentState = keys[i].newState;
    }

    // Traitement des touches selon l'�tat
    // Vous pouvez ajouter votre traitement ici

    // Gestion des mouvements
    //CheckForMovements();
}

InputState InputManager::GetCurrentState(int keyCode) {
    return keys[keyCode].currentState;
}

InputState InputManager::GetPreviousState(int keyCode) {
    return keys[keyCode].previousState;
}

//void InputManager::CheckForMovements() {
//    DirectX::XMFLOAT3 forwardVect;
//    DirectX::XMFLOAT3 rightVect;
//    DirectX::XMStoreFloat3(&forwardVect, dx12Inst->m_pMainCamComponent->GetForwardVector());
//    DirectX::XMStoreFloat3(&rightVect, dx12Inst->m_pMainCamComponent->GetRightVector());
//    if (keys['W'].currentState == PRESSED || keys['W'].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(forwardVect.x * speed, forwardVect.y * speed, forwardVect.z * speed);
//    else if (keys['Z'].currentState == PRESSED || keys['Z'].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(forwardVect.x * speed, forwardVect.y * speed, forwardVect.z * speed);
//    if (keys['S'].currentState == PRESSED || keys['S'].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(-forwardVect.x * speed, -forwardVect.y * speed, -forwardVect.z * speed);
//    if (keys['A'].currentState == PRESSED || keys['A'].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(-rightVect.x * speed, -rightVect.y * speed, -rightVect.z * speed);
//    else if (keys['Q'].currentState == PRESSED || keys['Q'].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(-rightVect.x * speed, -rightVect.y * speed, -rightVect.z * speed);
//    if (keys['D'].currentState == PRESSED || keys['D'].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(rightVect.x * speed, rightVect.y * speed, rightVect.z * speed);
//    if (keys[VK_SPACE].currentState == PRESSED || keys[VK_SPACE].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(0.0f, 1.0f * speed, 0.0f);
//    if (keys[VK_CONTROL].currentState == PRESSED || keys[VK_CONTROL].currentState == HELD)
//        dx12Inst->m_pMainCamera->Translate(0.0f, -1.0f * speed, 0.0f);
//    if (keys[VK_SHIFT].currentState == PRESSED || keys[VK_SHIFT].currentState == HELD)
//        speed = 0.2f;
//    else
//        speed = 0.1f;
//    if (keys[VK_ESCAPE].currentState == PRESSED || keys[VK_ESCAPE].currentState == HELD)
//    {
//        ShowCursor(TRUE);
//    }
//    if (keys[VK_LBUTTON].currentState == PRESSED || keys[VK_LBUTTON].currentState == HELD)
//    {
//    }
//
//    dx12Inst->m_pMainCamComponent->ChangePos();
//}

#pragma endregion
