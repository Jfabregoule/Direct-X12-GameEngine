#pragma once
#include "../../Engine/Source/DirectX12/dx12Inst.h"

class Entity;

class GameManager {
private:

	Entity* m_pMainCamera;

public: 

	GameManager();
	~GameManager();



	Entity* GetMainCamera() { return m_pMainCamera; };
	VOID SetAsMainCamera(Entity* entity, DirectX12Instance* inst) { m_pMainCamera = entity; inst->m_pMainCamera = entity; };


};
	
