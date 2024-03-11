#include "Engine.h"
#include "Collider.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Constructor/Destructor 								|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

Collider::Collider() {

};

Collider::~Collider() {
	ColliderRelease();
};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Initialize 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Initialize

void Collider::InitCollider() {
	SetName("collider");
	m_pBox = new CubeMesh();
};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									    Methods 									    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Methods

void Collider::ColliderRelease() {
	m_pBox = nullptr;
};

void Collider::IsTrigger(Entity* entity) {
	if (m_IsTriggering == false) {
		return;
	}

	XMFLOAT3 entityPos = entity->GetTransform()->m_VectorPosition;

	Vertex* collideCube = m_pBox->cube;

	if (entityPos.x > collideCube[0].position.x && entityPos.x < collideCube[3].position.x &&
		entityPos.y > collideCube[0].position.y && entityPos.y < collideCube[1].position.y &&
		entityPos.z > collideCube[0].position.z && entityPos.z < collideCube[4].position.z) {



	}
		
};

void Collider::CheckVertex() {

};

#pragma endregion