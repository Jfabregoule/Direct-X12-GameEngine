#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <DirectXColors.h>
#include <vector>

using namespace DirectX;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 PipeMesh Struct 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region PipeMesh Struct

struct ENGINE_API PipeMesh {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Constructor 									|
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Constructor

	PipeMesh(UINT nbVertices) {
		pipe = new Vertex[nbVertices * 2 + 2];
		pipeVerticesCount = nbVertices * 2 + 2;
		pipeIndices = new UINT[nbVertices * 4 * 3];
		pipeIndicesCount = nbVertices * 4 * 3;
		int index = 0;

		// Top Disk
		for (UINT i = 0; i < nbVertices; i++) { 
			pipeIndices[index++] = 0;
			pipeIndices[index++] = index + i + 1;
			pipeIndices[index++] = index + i;
		}

		// Bottom Disk
		for (UINT i = 0; i < nbVertices; i++) { 
			pipeIndices[index++] = nbVertices / 2;  
			pipeIndices[index++] = index + i; 
			pipeIndices[index++] = index + i + 1; 
		}

		// Side Rectangles
		for (UINT i = 0; i < nbVertices; i++) { 
			pipeIndices[index++] = i + 1; 
			pipeIndices[index++] = (i + 1) % nbVertices + 1; 
			pipeIndices[index++] = nbVertices * 2 - i; 

			pipeIndices[index++] = nbVertices * 2 - i; 
			pipeIndices[index++] = nbVertices * 2 - (i + 1) % nbVertices; 
			pipeIndices[index++] = i + 1; 
		}
	};

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Attributes 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	UINT pipeVerticesCount; // Taille du tableau pipe
	Vertex* pipe;

	UINT* pipeIndices; // 102 indices = nbPointsCercle * 4 * 3

	UINT pipeIndicesCount;

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Methods 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void GeneratePipe() {
		float x, z, angle;
		// Top Center Vertex
		pipe[0] = Vertex(XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(Colors::White), XMFLOAT2(0.0f, 0.0f));

		//Top Vertices
		for (int i = 0; i < pipeVerticesCount; ++i) {
			angle = static_cast<float>(i) * 2.0f * XM_PI / static_cast<float>(pipeVerticesCount);
			x = cos(angle);
			z = sin(angle);
			pipe[i + 1] = Vertex(XMFLOAT3(x, 1.0f, z), XMFLOAT4(Colors::Yellow), XMFLOAT2(0.0f, 0.0f));
		}

		// Bottom Center Vertex
		pipe[pipeVerticesCount + 1] = Vertex(XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(Colors::White), XMFLOAT2(0.0f, 0.0f)); // Center vertex

		// Bottom Vertices
		for (int i = 0; i < pipeVerticesCount; ++i) {
			angle = static_cast<float>(i) * 2.0f * XM_PI / static_cast<float>(pipeVerticesCount);
			x = cos(angle);
			z = sin(angle);
			pipe[i + pipeVerticesCount/2 + 2] = Vertex(XMFLOAT3(x, -1.0f, z), XMFLOAT4(Colors::Yellow), XMFLOAT2(0.0f, 0.0f));
		}
	};

#pragma endregion

};

#pragma endregion