#pragma once
#include "DirectX12/dx12Inst.h"
#include "Engine/Entity.h"
#include <chrono>
#include "Player.h"

enum GameState {

	PLAYING,
	PAUSED,
	END

};

class HandleCollisions;
class HandleInputs;


class GameManager {
private:

	HWND						m_WinHandle;
	GameState					m_State;
	Entity*						m_pMainCamera;
	Player*						m_pMainPlayer;
	DirectX12Instance*			m_pDX12Inst;
	HandleCollisions*			m_pCollisionsHandle;
	HandleInputs*				m_pInputsHandle;

	float						m_LastUpdateTime;
	float						m_DeltaTime;
	float						m_GameSpeed;

public: 

	GameManager();
	~GameManager();

	VOID Initialize(HWND handle);

	VOID Update();

	VOID Clear();

	Player* GetMainPlayer() { return m_pMainPlayer; };
	VOID SetAsMainPlayer(Player* player, DirectX12Instance* inst) { m_pMainPlayer = player; SetAsMainCamera(player->GetEntity(),inst); };

	Entity* GetMainCamera() { return m_pMainCamera; };
	VOID SetAsMainCamera(Entity* entity, DirectX12Instance* inst) { m_pMainCamera = entity; inst->SetEntityAsMainCamera(entity); };

	GameState* GetGameState() { return &m_State; };
	VOID		SetGameState(GameState state) { m_State = state; };

	float		*GetGameSpeed() { return &m_GameSpeed; };
	VOID		SetGameSpeed(float gameSpeed) { m_GameSpeed = gameSpeed; };

	DirectX12Instance* GetInst() { return m_pDX12Inst; };

};
	
