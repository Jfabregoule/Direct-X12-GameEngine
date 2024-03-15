#pragma once

#include "Engine.h"

#include <vector>
#include <DirectXColors.h>

#include "DirectX12/Vertex.h"

using namespace DirectX;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 CubeMesh Struct 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region CubeMesh Struct

struct ENGINE_API CubeMesh {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Attributes 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	Vertex cube[24];
	UINT cubeVerticesCount = 24; // Taille du tableau cube

	UINT cubeIndices[36] = 
	{
		// front face

		0, 1, 2,
		 2, 3, 0,

		 //// left face
		 6, 5, 4,
		 4, 7, 6,

		 //// back face
		 9, 10, 11,
		 11, 8, 9,

		 //////// right face
		 14, 13, 12,
		 12, 15, 14,

		 //////// top face
		 18, 17, 16,
		 16, 19, 18,

		 //////// bottom face
		 20, 21, 22,
		 22, 23, 20,
	};
	UINT cubeIndicesCount = sizeof(cubeIndices) / sizeof(UINT);

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Methods 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void GenerateCube() {
		cube[0] = Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::Orange), XMFLOAT2(0.0f, 0.0f));
		cube[1] = Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::White), XMFLOAT2(1.0f, 0.0f));
		cube[2] = Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red), XMFLOAT2(1.0f, 1.0f));
		cube[3] = Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red), XMFLOAT2(0.0f, 1.0f));

		cube[4] = Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::Orange), XMFLOAT2(0.0f, 0.0f));
		cube[5] = Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::White), XMFLOAT2(1.0f, 0.0f));
		cube[6] = Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::White), XMFLOAT2(1.0f, 1.0f));
		cube[7] = Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Yellow), XMFLOAT2(0.0f, 1.0f));

		cube[8] = Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::White), XMFLOAT2(0.0f, 0.0f));
		cube[9] = Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::Orange), XMFLOAT2(1.0f, 0.0f));
		cube[10] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::Yellow), XMFLOAT2(1.0f, 1.0f));
		cube[11] = Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::White), XMFLOAT2(0.0f, 1.0f));

		cube[12] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::Yellow), XMFLOAT2(0.0f, 0.0f));
		cube[13] = Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::White), XMFLOAT2(1.0f, 0.0f));
		cube[14] = Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red), XMFLOAT2(1.0f, 1.0f));
		cube[15] = Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::Orange), XMFLOAT2(0.0f, 1.0f));

		cube[16] = Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::White), XMFLOAT2(0.0f, 0.0f));
		cube[17] = Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::Orange), XMFLOAT2(1.0f, 0.0f));
		cube[18] = Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(Colors::White), XMFLOAT2(1.0f, 1.0f));
		cube[19] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(Colors::Yellow), XMFLOAT2(0.0f, 1.0f));

		cube[20] = Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::White), XMFLOAT2(0.0f, 0.0f));
		cube[21] = Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Yellow), XMFLOAT2(1.0f, 0.0f));
		cube[22] = Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red), XMFLOAT2(1.0f, 1.0f));
		cube[23] = Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(Colors::Orange), XMFLOAT2(0.0f, 1.0f));
	};

#pragma endregion

};

#pragma endregion