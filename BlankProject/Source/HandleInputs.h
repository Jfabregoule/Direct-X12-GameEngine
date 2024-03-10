#include "Engine/InputManager.h"
#include "DirectX12/dx12Inst.h"

class HandleInputs {

private:

	InputManager*		m_InputManager;
	DirectX12Instance*	m_DX12Instance;

public:

	HandleInputs(DirectX12Instance *inst);
	~HandleInputs();

	void UpdateInputs();

};