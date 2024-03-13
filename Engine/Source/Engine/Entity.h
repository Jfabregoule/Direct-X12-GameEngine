#pragma once
#include <vector>
#include <string>
#include "Engine/Component.h"
#include "Engine/transform.h"
#include "DirectX12/Vertex.h"
#include "Engine/Camera.h"
#include "Engine/ParticleSystem.h"

class DirectX12Instance;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                   Entity Class		                                |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Entity Class

class ENGINE_API Entity {
private:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                                   Attributs											|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributs

	std::string					m_Name;
	std::vector <Component*>	m_ListComponent;//remplacer les int par la classe component quand elle sera faite
	Entity* m_pParent;
	std::vector<Entity*>		m_Children;
	Transform					m_Transform;
	DirectX12Instance* m_pInst;

	bool						m_ToDestroy;
	bool						m_isSlide;

	DirectX::XMFLOAT3			m_Velocity;

#pragma endregion

public:

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |                               Constructor/Destructor                                |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor And Destructor

	Entity(DirectX12Instance* inst);
	~Entity();

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |										 Methods									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	std::string				GetName();
	void					SetName(std::string entityName);

	Entity* GetParent();
	void					SetParent(Entity* parentEntity);

	std::vector<Entity*>	GetChildren();
	void					AddChildren(Entity* childEntity);

	Transform* GetTransform();
	DirectX::XMFLOAT4X4* GetTransformConvert();

	bool					GetDestroyValue();
	void					SetDestroyValue(bool destroy);

	bool					GetSlide() { return m_isSlide; };
	void					SetSlide(bool slide) { m_isSlide = slide; };

	std::vector<Component*>	GetAllComponents();
	Component*				AddComponentByName(std::string componentName);
	void					AttachComponent(Component* component);
	Component*				GetComponentByName(std::string name);

	void					Translate(float postionX, float positionY, float positionZ);
	void					Rotate(float yaw, float pitch, float roll);
	void					Scale(float scaleX, float scaleY, float scaleZ);

	float					CalculateNorm(DirectX::XMFLOAT3* vector);
	void					CalculateVelocity(DirectX::XMFLOAT3* direction, float speed);

	void					Forward(float speed, float dT, float* gameSpeed);
	void					Backward(float speed, float dT, float* gameSpeed);
	void					StrafeLeft(float speed, float dT, float* gameSpeed);
	void					StrafeRight(float speed, float dT, float* gameSpeed);
	void					Down(float speed, float dT, float* gameSpeed);
	void					Up(float speed, float dT, float* gameSpeed);

	void					UpdateEntity(float dt, float* gameSpeed);
	void					InitObject(std::string type, std::string shader_type = "default", std::string texture_name = "bark");

	void					SetCollider();
	bool					HasTag(std::string tag);

#pragma endregion

};

#pragma endregion