#pragma once

#include "../DirectX12/dx12Inst.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                     Inputs Enum                                     |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Inputs Enum

enum InputState {
    IDLE,
    PRESSED,
    HELD,
    RELEASED
};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                 InputManager Class                                  |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Input Manager

class ENGINE_API InputManager {

private:

        /*
        *  -------------------------------------------------------------------------------------
        * |                                                                                     |
        * |                                     Attributs                                       |
        * |                                                                                     |
        *  -------------------------------------------------------------------------------------
        */

#pragma region Attributs

    struct KeyState {
        InputState previousState;
        InputState currentState;
        InputState newState;
    };

    POINT lastMousePos;
    POINT mousePos;
    KeyState keys[256]; // Stocke les �tats pour chaque touche
    float    mouseDelta[2];

    DirectX12Instance* dx12Inst;

#pragma endregion

public:

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                               Constructor/Destructor                                |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Constructor And Destructor

    InputManager(DirectX12Instance* inst);
    ~InputManager();

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                       Methods                                       |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Methods

    void Handle();
    POINT* GetLastMousePos();
    POINT* GetCurrentMousePos();
    float *GetMouseDelta();
    void UpdateState();
    InputState GetCurrentState(int key);
    InputState GetPreviousState(int key);
    void CheckForMovements();

#pragma endregion

};

#pragma endregion