#include "Engine.h"
#include "DirectX12/MathHelper.h"
#include "Engine/transform.h"
#include "Engine/CubeMesh.h"
#include "Engine/Entity.h"
#include <Windowsnumerics.h>

using namespace Windows::Foundation::Numerics;

class ENGINE_API Atom : public Entity
{ //Créer un CubeMesh dans l'atom afin de pouvoir le draw ultérieurement
public:
	float m_LifeTime;//Life time of the atom
	float m_Speed;//Movement speed of the atom
	float3 m_Direction;//Vector made of float coordinates for the direction of the atom

	Atom(ID3D12Device* device);
	virtual ~Atom();

	void InitializeAtom(float speed, float lifeTime, float xDir, float yDir, float zDir);

	void CycleLife(float deltaTime);
};