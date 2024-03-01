#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <vector>
#include <wrl.h>

using namespace DirectX;

VertexColor cube[8];
VertexColor* pCube = cube;

std::vector<UINT> cubeIndices;
std::vector<UINT>* pCubeIndices = &cubeIndices;

void createCube() {

	cube[0] = VertexColor(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	cube[0] = VertexColor(XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	cube[0] = VertexColor(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	cube[0] = VertexColor(XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	cube[0] = VertexColor(XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	cube[0] = VertexColor(XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	cube[0] = VertexColor(XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	cube[0] = VertexColor(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

	cubeIndices = { 0,1,3 , 0,2,3 , 0,2,7 , 0,4,7 , 1,0,4 , 1,5,4 , 1,6,5 , 1,3,6 , 3,2,7 , 3,6,7 , 7,4,5 , 7,6,5 };

};

