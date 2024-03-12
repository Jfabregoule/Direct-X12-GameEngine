#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <DirectXColors.h>
#include <vector>

using namespace DirectX;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 CubeMesh Struct 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region SkyBox Struct

struct ENGINE_API SkyBox {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Attributes 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	Vertex skybox[8];
	UINT skyboxVerticesCount = 8; // Taille du tableau cube

	UINT skyboxIndices[36] =
	{
		// front face
		0, 2, 1,
		0, 3, 2,

		// back face
		4, 5, 6,
		4, 6, 7,

		// left face
		4, 1, 5,
		4, 0, 1,

		// right face
		3, 6, 2,
		3, 7, 6,

		// top face
		1, 6, 5,
		1, 2, 6,

		// bottom face
		4, 3, 0,
		4, 7, 3
	};
	UINT skyboxIndicesCount = sizeof(skyboxIndices) / sizeof(UINT);

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Methods 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void GenerateSkybox() 
	{
		skybox[0] = Vertex(XMFLOAT3(-100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black));
		skybox[1] = Vertex(XMFLOAT3(-100, 100.0f, -100.0f), XMFLOAT4(Colors::Black));
		skybox[2] = Vertex(XMFLOAT3(100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::Black));
		skybox[3] = Vertex(XMFLOAT3(100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black));

		skybox[4] = Vertex(XMFLOAT3(-100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::Black));
		skybox[5] = Vertex(XMFLOAT3(-100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::Black));
		skybox[6] = Vertex(XMFLOAT3(100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::Black));
		skybox[7] = Vertex(XMFLOAT3(100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::Black));
	};

#pragma endregion

};

#pragma endregion