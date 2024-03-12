#pragma once
#include "DirectX12/dx12Inst.h"
#include "Engine/Entity.h"

enum GameState {

	PLAYING,
	PAUSED,
	END

};

class HandleCollisions;
class HandleInputs;


class GameManager {
private:

	HWND				m_WinHandle;
	GameState			m_State;
	Entity*				m_pMainCamera;
	DirectX12Instance*	m_pDX12Inst;
	HandleCollisions*	m_pCollisionsHandle;
	HandleInputs*		m_pInputsHandle;

public: 

	GameManager();
	~GameManager();

	VOID Initialize(HWND handle);

	VOID Update();

	VOID Clear();



	Entity* GetMainCamera() { return m_pMainCamera; };
	VOID SetAsMainCamera(Entity* entity, DirectX12Instance* inst) { m_pMainCamera = entity; inst->SetEntityAsMainCamera(entity); };

	GameState* GetGameState() { return &m_State; };
	VOID		SetGameState(GameState state) { m_State = state; };


};
	
