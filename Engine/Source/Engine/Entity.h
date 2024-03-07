#pragma once
#include <vector>
#include <string>
#include "Engine/Component.h"
#include "Engine/transform.h"
#include "DirectX12/Vertex.h"
#include "Engine/Camera.h"

class ID3D12Device;

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
	Entity*						m_pParent;
	std::vector<Entity*>		m_Children;
	Transform					m_Transform;
	ID3D12Device*				m_pDevice;

	bool						m_ToDestroy;

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

	Entity(ID3D12Device* device);
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

	Entity*					GetParent();
	void					SetParent(Entity* parentEntity);

	std::vector<Entity*>	GetChildren();
	void					AddChildren(Entity* childEntity);

	Transform*				GetTransform();
	DirectX::XMFLOAT4X4*	GetTransformConvert();

	bool					GetDestroyValue();
	void					SetDestroyValue(bool destroy);

	std::vector<Component*>	GetAllComponents();
	Component* AddComponentByName(std::string componentName);
	void AttachComponent(Component* component);
	Component* GetComponentByName(std::string name);

	void Translate(float postionX, float positionY, float positionZ);
	void Rotate(float yaw, float pitch, float roll);
	void Scale(float scaleX, float scaleY, float scaleZ);

	void InitObject(std::string type);

	//void SetMesh(Vertex* vertices = nullptr);

#pragma endregion

};

#pragma endregion