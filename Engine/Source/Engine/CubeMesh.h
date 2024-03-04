#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <vector>

using namespace DirectX;

struct ENGINE_API CubeMesh {
	Vertex cube[8];
	UINT cubeVerticesCount = 8; // Taille du tableau cube

	UINT cubeIndices[12] = {
		// front face
		
		0, 1, 2,
		1, 2, 3,

		//// back face
		4, 5, 6,
		5, 6, 7,

		//// left face
		//4, 5, 1,
		//4, 1, 0,

		//// right face
		//3, 2, 6,
		//3, 6, 7,

		//// top face
		//1, 5, 6,
		//1, 6, 2,

		//// bottom face
		//4, 0, 3
		//4, 3, 7
	};
	UINT cubeIndicesCount = sizeof(cubeIndices);

	void GenerateCube() {
		cube[0] = Vertex(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) );
		cube[1] = Vertex(XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) );
		cube[2] = Vertex(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) );
		cube[3] = Vertex(XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) );

		cube[4] = Vertex(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) );
		cube[5] = Vertex(XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) );
		cube[6] = Vertex(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) );
		cube[7] = Vertex(XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f) );
	};
};