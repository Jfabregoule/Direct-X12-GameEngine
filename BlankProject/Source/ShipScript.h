#pragma once 

#include "Engine/Script.h"

class Entity;
class DirectX12Instance;
struct Transform;

class ShipScript : public Script {
protected:

	Entity* m_pEntity;
	DirectX12Instance* m_pInst;
	Transform* m_pTransform;
	int m_Life;

public:

	ShipScript();
	~ShipScript();

	Entity* GetEntity() { return m_pEntity; };

	void Initialize(DirectX12Instance* inst, Entity* self);
	void Shoot();
	void RocketShoot();
	void LaserShoot();
	void DecreaseLife(int dmg);
};