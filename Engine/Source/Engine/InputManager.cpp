#include "Engine.h"
#include "InputManager.h"
#include <cmath> // Inclure la bibliothèque cmath pour utiliser la fonction radians

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
    // Initialise tous les états des touches à IDLE
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
    // Boucle à travers toutes les touches pour détecter les états
    for (int i = 0; i < 256; ++i) {
        if (GetAsyncKeyState(i) & 0x8000) {
            keys[i].newState = PRESSED;
        }
        else {
            keys[i].newState = RELEASED;
        }
    }

    // Obtenez la position actuelle de la souris
    POINT currentMousePos;
    GetCursorPos(&currentMousePos);
    ScreenToClient(dx12Inst->m_handle, &currentMousePos);

    ShowCursor(FALSE);

    // Calculez les différences de position de la souris entre les cadres
    int deltaX = currentMousePos.x - lastMousePos.x;
    int deltaY = currentMousePos.y - lastMousePos.y;

    // Mise à jour de la position précédente de la souris
    lastMousePos = currentMousePos;

    // Ajoutez la rotation de la caméra en fonction des mouvements de la souris
    // Convertir les valeurs de déplacement en radians et les multiplier par un facteur de sensibilité
    float sensitivity = 0.001f; // Réglage de la sensibilité de la souris
    float rotationX = static_cast<float>(deltaX) * sensitivity;
    float rotationY = static_cast<float>(deltaY) * sensitivity;

    dx12Inst->m_pMainCamera->Rotate(rotationX, rotationY, 0.0f);

    dx12Inst->m_pMainCamComponent->ChangeForward();

    SetCursorPos(dx12Inst->mClientWidth / 2, dx12Inst->mClientHeight / 2);
    lastMousePos.x = dx12Inst->mClientWidth / 2;
    lastMousePos.y = dx12Inst->mClientHeight / 2;
    ScreenToClient(dx12Inst->m_handle, &lastMousePos);
    UpdateState();
}


void InputManager::UpdateState() {
    // Met à jour les états des touches
    for (int i = 0; i < 256; ++i) {
        keys[i].previousState = keys[i].currentState;
        keys[i].currentState = keys[i].newState;
    }

    // Traitement des touches selon l'état
    // Vous pouvez ajouter votre traitement ici

    // Gestion des mouvements
    CheckForMovements();
}

InputState InputManager::GetCurrentState(int keyCode) {
    return keys[keyCode].currentState;
}

InputState InputManager::GetPreviousState(int keyCode) {
    return keys[keyCode].previousState;
}

void InputManager::CheckForMovements() {
    DirectX::XMFLOAT3 forwardVect;
    DirectX::XMFLOAT3 rightVect;
    DirectX::XMStoreFloat3(&forwardVect, dx12Inst->m_pMainCamComponent->GetForwardVector());
    DirectX::XMStoreFloat3(&rightVect, dx12Inst->m_pMainCamComponent->GetRightVector());
    if (keys['W'].currentState == PRESSED || keys['W'].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(forwardVect.x * speed, forwardVect.y * speed, forwardVect.z * speed);
    else if (keys['Z'].currentState == PRESSED || keys['Z'].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(forwardVect.x * speed, forwardVect.y * speed, forwardVect.z * speed);
    if (keys['S'].currentState == PRESSED || keys['S'].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(-forwardVect.x * speed, -forwardVect.y * speed, -forwardVect.z * speed);
    if (keys['A'].currentState == PRESSED || keys['A'].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(-rightVect.x * speed, -rightVect.y * speed, -rightVect.z * speed);
    else if (keys['Q'].currentState == PRESSED || keys['Q'].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(-rightVect.x * speed, -rightVect.y * speed, -rightVect.z * speed);
    if (keys['D'].currentState == PRESSED || keys['D'].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(rightVect.x * speed, rightVect.y * speed, rightVect.z * speed);
    if (keys[VK_SPACE].currentState == PRESSED || keys[VK_SPACE].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(0.0f, 1.0f * speed, 0.0f);
    if (keys[VK_CONTROL].currentState == PRESSED || keys[VK_CONTROL].currentState == HELD)
        dx12Inst->m_pMainCamera->Translate(0.0f, -1.0f * speed, 0.0f);
    if (keys[VK_SHIFT].currentState == PRESSED || keys[VK_SHIFT].currentState == HELD)
        speed = 0.2f;
    else
        speed = 0.1f;
    if (keys[VK_ESCAPE].currentState == PRESSED || keys[VK_ESCAPE].currentState == HELD)
    {
        ShowCursor(TRUE);
    }
    if (keys[VK_LBUTTON].currentState == PRESSED || keys[VK_LBUTTON].currentState == HELD)
    {
    }

    dx12Inst->m_pMainCamComponent->ChangePos();
}

#pragma endregion
