#pragma once 

class Entity;
class DirectX12Instance;
struct Transform;

class Ship {
protected:

	Entity* m_pEntity;
	DirectX12Instance* m_pInst;
	Transform* m_pTransform;
	int m_life;

public:

	Ship();
	~Ship();

	Entity* GetEntity() { return m_pEntity; };

	VOID Initialize(DirectX12Instance* inst);
	VOID Shoot();
	VOID RocketShoot();
	VOID LaserShoot();
};