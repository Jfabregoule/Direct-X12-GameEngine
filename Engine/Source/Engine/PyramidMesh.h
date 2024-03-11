#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <DirectXColors.h>
#include <vector>

using namespace DirectX;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 PyramidMesh Struct 								|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region PyramidMesh Struct

struct ENGINE_API PyramidMesh {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									  Attributes 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	Vertex pyramid[5];
	UINT pyramidVerticesCount = 5; // Taille du tableau cube

	UINT pyramidIndices[18] = {

		//// front face
		0, 3, 1,
		1, 3, 2,

		//// back face
		0, 4, 3,
		3, 4, 2,

		//// left face
		2, 4, 1,
		1, 4, 0,
	};
	UINT pyramidIndicesCount = sizeof(pyramidIndices) / sizeof(UINT);

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Methods 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void GeneratePyramid() {
		pyramid[0] = Vertex(XMFLOAT3(0.5f, 0.0f, -0.5f), XMFLOAT4(Colors::Black));
		pyramid[1] = Vertex(XMFLOAT3(-0.5f, 0.0f, -0.5f), XMFLOAT4(Colors::White));
		pyramid[2] = Vertex(XMFLOAT3(-0.5f, 0.0f, 0.5f), XMFLOAT4(Colors::Red));
		pyramid[3] = Vertex(XMFLOAT3(0.5f, 0.0f, 0.5f), XMFLOAT4(Colors::Green));
		pyramid[4] = Vertex(XMFLOAT3(0.0f, 1.5f, 0.0f), XMFLOAT4(Colors::Magenta));
	};

#pragma endregion

};

#pragma endregion