#pragma once
#include "DirectX12/dx12Inst.h"
#include "Engine/Entity.h"


class GameManager {
private:

	Entity* m_pMainCamera;

public: 

	GameManager();
	~GameManager();



	Entity* GetMainCamera() { return m_pMainCamera; };
	VOID SetAsMainCamera(Entity* entity, DirectX12Instance* inst) { m_pMainCamera = entity; inst->SetEntityAsMainCamera(entity); };


};
	
