#pragma once


enum InputState {
    IDLE,
    PRESSED,
    HELD,
    RELEASED
};

class ENGINE_API InputManager {

public:

    InputState previousStateZ;
    InputState currentStateZ;
    InputState newStateZ;

    InputState previousStateQ;
    InputState currentStateQ;
    InputState newStateQ;

    InputState previousStateS;
    InputState currentStateS;
    InputState newStateS;

    InputState previousStateD;
    InputState currentStateD;
    InputState newStateD;

    InputState previousStateW;
    InputState currentStateW;
    InputState newStateW;

    InputState previousStateA;
    InputState currentStateA;
    InputState newStateA;

    InputManager();
    ~InputManager();

    void Handle();
    void UpdateState();
    InputState GetCurrentState(char m_Key);
    InputState GetPreviousState(char m_Key);
};