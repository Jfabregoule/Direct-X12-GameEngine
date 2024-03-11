#pragma once
#include "Engine.h"
#include "Component.h"
#include "CubeMesh.h"
#include "Entity.h"

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                  Component Class                                    |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Component Class

class Collider : public Component {

private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                                     Attributes                                      |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	CubeMesh* m_pBox;

	bool m_IsTrigger;
	bool m_IsTriggering;
	int (*pf)(int i, int b);

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |								Constructor/Destructor                                  |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	Collider();
	~Collider();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                                   Init/Release                                      |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Init and Release

	void InitCollider();
	void ColliderRelease();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                                Getters/Setters                                      |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Getters And Setters

	CubeMesh* GetBox() { return m_pBox; };
	void SetIsTrigger(bool a) { m_IsTrigger = a; };
	bool GetIsTrigger() { return m_IsTrigger; };

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                                    Methods											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void IsTrigger(Entity* entity);
	void CheckVertex();

#pragma endregion

};

#pragma endregion