#include "Engine.h"
#include "DirectX12/MathHelper.h"
#include <Windowsnumerics.h>
#include "Engine/transform.h"

using namespace Windows::Foundation::Numerics;

class ENGINE_API Atom
{ //Créer un CubeMesh dans l'atom afin de pouvoir le draw ultérieurement
public:
	float m_LifeTime;//Life time of the atom
	float m_Speed;//Movement speed of the atom
	float3 m_Direction;//Vector made of float coordinates for the direction of the atom
	Transform m_Transform;//Transform instance for the scale and translation of the atom

	Atom();
	virtual ~Atom();

	void InitializeAtom(float speed, float lifeTime, float xDir, float yDir, float zDir);

	void CycleLife(float deltaTime);
};