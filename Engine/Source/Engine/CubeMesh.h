#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <vector>
#include <wrl.h>

using namespace DirectX;

struct CubeMesh {
	Vertex cube[8];
	UINT cubeVerticesCount = 8; // Taille du tableau cube

	UINT cubeIndices[36] = {
		0,1,2 , 2,1,3 , // Face avant
		4,0,6 , 6,0,2 , // Face gauche
		5,4,7 , 7,4,6 , // Face arrière
		1,5,3 , 3,5,7 , // Face droite
		4,5,0 , 0,5,1 , // Face supérieure
		2,3,6 , 6,3,7   // Face inférieure
	};
	UINT cubeIndicesCount = 36;

	void GenerateCube() {
		cube[0] = Vertex(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
		cube[1] = Vertex(XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
		cube[2] = Vertex(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
		cube[3] = Vertex(XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

		cube[4] = Vertex(XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
		cube[5] = Vertex(XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
		cube[6] = Vertex(XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
		cube[7] = Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	};
};