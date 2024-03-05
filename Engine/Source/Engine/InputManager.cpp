#include "Engine.h"
#include "InputManager.h"


InputManager::InputManager() {
    currentStateZ = IDLE;
    previousStateZ = IDLE;

    currentStateQ = IDLE;
    previousStateQ = IDLE;

    currentStateS = IDLE;
    previousStateS = IDLE;

    currentStateD = IDLE;
    previousStateD = IDLE;

    currentStateW = IDLE;
    previousStateW = IDLE;

    currentStateA = IDLE;
    previousStateA = IDLE;
}

InputManager::~InputManager()
{
}

void InputManager::Handle() {

    // Key Detection

#pragma region
    if (GetAsyncKeyState('Z') & 0x8000) {
        newStateZ = PRESSED;
    }
    else {
        newStateZ = RELEASED;
    }
#pragma endregion Z

#pragma region
    if (GetAsyncKeyState('S') & 0x8000) {
        newStateS = PRESSED;
    }
    else {
        newStateS = RELEASED;
    }
#pragma endregion S

#pragma region
    if (GetAsyncKeyState('Q') & 0x8000) {
        newStateQ = PRESSED;
    }
    else {
        newStateQ = RELEASED;
    }
#pragma endregion Q

#pragma region
    if (GetAsyncKeyState('D') & 0x8000) {
        newStateD = PRESSED;
    }
    else {
        newStateD = RELEASED;
    }
#pragma endregion D

#pragma region
    if (GetAsyncKeyState('W') & 0x8000) {
        newStateW = PRESSED;
    }
    else {
        newStateW = RELEASED;
    }
#pragma endregion W

#pragma region
    if (GetAsyncKeyState('A') & 0x8000) {
        newStateA = PRESSED;
    }
    else {
        newStateA = RELEASED;
    }
#pragma endregion A
}

void InputManager::UpdateState() {

    previousStateZ = currentStateZ;
    previousStateQ = currentStateQ;
    previousStateS = currentStateS;
    previousStateD = currentStateD;
    previousStateW = currentStateW;
    previousStateA = currentStateA;



    // State Machine


#pragma region
// Z
    if (newStateZ == PRESSED && previousStateZ == IDLE) {
        currentStateZ = PRESSED;
        OutputDebugString(L"Z PRESSED \n");
    }

    else if (newStateZ == PRESSED && previousStateZ == PRESSED) {
        currentStateZ = HELD;
        OutputDebugString(L"Z HELD \n");
    }

    else if (newStateZ == RELEASED && previousStateZ == HELD) {
        currentStateZ = RELEASED;
        OutputDebugString(L"Z RELEASED \n");
    }

    else if (newStateZ == RELEASED && previousStateZ == RELEASED) {
        currentStateZ = IDLE;
        OutputDebugString(L"Z IDLE \n");
        OutputDebugString(L"\n");
    }
#pragma endregion Z

#pragma region
    // Q
    if (newStateQ == PRESSED && previousStateQ == IDLE) {
        currentStateQ = PRESSED;
        OutputDebugString(L"Q PRESSED \n");
    }

    else if (newStateQ == PRESSED && previousStateQ == PRESSED) {
        currentStateQ = HELD;
        OutputDebugString(L"Q HELD \n");
    }

    else if (newStateQ == RELEASED && previousStateQ == HELD) {
        currentStateQ = RELEASED;
        OutputDebugString(L"Q RELEASED \n");
    }

    else if (newStateQ == RELEASED && previousStateQ == RELEASED) {
        currentStateQ = IDLE;
        OutputDebugString(L"Q IDLE \n");
        OutputDebugString(L"\n");
    }
#pragma endregion Q

#pragma region
    // S
    if (newStateS == PRESSED && previousStateS == IDLE) {
        currentStateS = PRESSED;
        OutputDebugString(L"S PRESSED \n");
    }

    else if (newStateS == PRESSED && previousStateS == PRESSED) {
        currentStateS = HELD;
        OutputDebugString(L"S HELD \n");
    }

    else if (newStateS == RELEASED && previousStateS == HELD) {
        currentStateS = RELEASED;
        OutputDebugString(L"S RELEASED \n");
    }

    else if (newStateS == RELEASED && previousStateS == RELEASED) {
        currentStateS = IDLE;
        OutputDebugString(L"S IDLE \n");
        OutputDebugString(L"\n");
    }
#pragma endregion S

#pragma region
    // D
    if (newStateD == PRESSED && previousStateD == IDLE) {
        currentStateD = PRESSED;
        OutputDebugString(L"D PRESSED \n");
    }

    else if (newStateD == PRESSED && previousStateD == PRESSED) {
        currentStateD = HELD;
        OutputDebugString(L"D HELD \n");
    }

    else if (newStateD == RELEASED && previousStateD == HELD) {
        currentStateD = RELEASED;
        OutputDebugString(L"D RELEASED \n");
    }

    else if (newStateD == RELEASED && previousStateD == RELEASED) {
        currentStateD = IDLE;
        OutputDebugString(L"D IDLE \n");
        OutputDebugString(L"\n");
    }
#pragma endregion D

#pragma region
    // W
    if (newStateW == PRESSED && previousStateW == IDLE) {
        currentStateW = PRESSED;
        OutputDebugString(L"W PRESSED \n");
    }

    else if (newStateW == PRESSED && previousStateW == PRESSED) {
        currentStateW = HELD;
        OutputDebugString(L"W HELD \n");
    }

    else if (newStateW == RELEASED && previousStateW == HELD) {
        currentStateW = RELEASED;
        OutputDebugString(L"W RELEASED \n");
    }

    else if (newStateW == RELEASED && previousStateW == RELEASED) {
        currentStateW = IDLE;
        OutputDebugString(L"W IDLE \n");
        OutputDebugString(L"\n");
    }
#pragma endregion W

#pragma region 
    // A
    if (newStateA == PRESSED && previousStateA == IDLE) {
        currentStateA = PRESSED;
        OutputDebugString(L"A PRESSED \n");
    }

    else if (newStateA == PRESSED && previousStateA == PRESSED) {
        currentStateA = HELD;
        OutputDebugString(L"A HELD \n");
    }

    else if (newStateA == RELEASED && previousStateA == HELD) {
        currentStateA = RELEASED;
        OutputDebugString(L"A RELEASED \n");
    }

    else if (newStateA == RELEASED && previousStateA == RELEASED) {
        currentStateA = IDLE;
        OutputDebugString(L"A IDLE \n");
        OutputDebugString(L"\n");
    }
#pragma endregion A 

}

InputState InputManager::GetCurrentState(char m_Key) {
    if (m_Key == 'Z') {
        return currentStateZ;
    }
    if (m_Key == 'Q') {
        return currentStateQ;
    }
    if (m_Key == 'S') {
        return currentStateS;
    }
    if (m_Key == 'D') {
        return currentStateD;
    }
    if (m_Key == 'W') {
        return currentStateW;
    }
    if (m_Key == 'A') {
        return currentStateA;
    }
}

InputState InputManager::GetPreviousState(char m_Key) {
    if (m_Key == 'Z') {
        return previousStateZ;
    }
    if (m_Key == 'Q') {
        return previousStateQ;
    }
    if (m_Key == 'S') {
        return previousStateS;
    }
    if (m_Key == 'D') {
        return previousStateD;
    }
    if (m_Key == 'W') {
        return previousStateW;
    }
    if (m_Key == 'A') {
        return previousStateA;
    }
}