#include "Engine/InputManager.h"


class DirectX12Instance;
class GameManager;

class HandleInputs {

private:

	InputManager*		m_InputManager;
	DirectX12Instance*	m_DX12Instance;
	GameManager*		m_GameManager;
	float				m_DeltaTime;
	float				m_Speed;

public:

	HandleInputs(DirectX12Instance* inst, GameManager* gameManager);
	~HandleInputs();

	void Update(float dt);

	void UpdateInputs();

	VOID UpdateMouse();

};