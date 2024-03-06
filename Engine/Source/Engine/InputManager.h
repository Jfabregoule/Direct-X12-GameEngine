#pragma once

#include "../DirectX12/dx12Inst.h"

enum InputState {
    IDLE,
    PRESSED,
    HELD,
    RELEASED
};

class ENGINE_API InputManager {

private:
    struct KeyState {
        InputState previousState;
        InputState currentState;
        InputState newState;
    };

    POINT lastMousePos;
    POINT mousePos;
    KeyState keys[256]; // Stocke les états pour chaque touche

    DirectX12Instance* dx12Inst;

public:

    InputManager(DirectX12Instance* inst);
    ~InputManager();

    void Handle();
    void UpdateState();
    InputState GetCurrentState(int key);
    InputState GetPreviousState(int key);
    void CheckForMovements();
};