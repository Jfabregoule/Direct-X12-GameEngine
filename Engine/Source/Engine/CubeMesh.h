#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <vector>
#include <wrl.h>

using namespace DirectX;

struct CubeMesh {
	Vertex cube[8];
	Vertex* pCube = cube;

	UINT cubeIndices[36] = { 0,1,3 , 0,2,3 , 0,2,7 , 0,4,7 , 1,0,4 , 1,5,4 , 1,6,5 , 1,3,6 , 3,2,7 , 3,6,7 , 7,4,5 , 7,6,5 };
	UINT* pCubeIndices = cubeIndices;

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

