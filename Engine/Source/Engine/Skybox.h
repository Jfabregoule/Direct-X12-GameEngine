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

	UINT skyboxIndices[36] = {
		// front face

		0, 1, 2,
		0, 2, 3,

		//// back face
		4, 6, 5,
		4, 7, 6,

		//// left face
		4, 5, 1,
		4, 1, 0,

		//// right face
		3, 2, 6,
		3, 6, 7,

		//// top face
		1, 5, 6,
		1, 6, 2,

		//// bottom face
		4, 0, 3,
		4, 3, 7
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

	void GenerateSkybox() {
		skybox[0] = Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White));
		skybox[1] = Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::Black));
		skybox[2] = Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::Red));
		skybox[3] = Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green));

		skybox[4] = Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::Blue));
		skybox[5] = Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::Yellow));
		skybox[6] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::Cyan));
		skybox[7] = Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::Magenta));
	};

#pragma endregion

};

#pragma endregion