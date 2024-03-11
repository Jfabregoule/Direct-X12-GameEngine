#include "Engine/InputManager.h"


class DirectX12Instance;

class HandleInputs {

private:

	InputManager*		m_InputManager;
	DirectX12Instance*	m_DX12Instance;

public:

	HandleInputs(DirectX12Instance *inst);
	~HandleInputs();

	void UpdateInputs();



};