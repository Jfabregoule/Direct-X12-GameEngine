#pragma once

#include "DirectX12/dx12Inst.h"
#include "Engine/Collider.h"

class HandleCollisions {

private:

	DirectX12Instance* m_DX12Instance;

public:

	HandleCollisions(DirectX12Instance* inst);
	~HandleCollisions();

	void UpdateCollisions();
};