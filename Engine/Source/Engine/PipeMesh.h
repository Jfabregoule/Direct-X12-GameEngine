#pragma once

#include "Engine.h"

#include <vector>
#include <DirectXColors.h>

#include "DirectX12/Vertex.h"

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

	PipeMesh(UINT partCount) {
		pipeVerticesCount = partCount * 2 + 2;
		pipe = new Vertex[pipeVerticesCount];
		pipeIndicesCount = partCount * 4 * 3;
		pipeIndices = new UINT[pipeIndicesCount];
		m_PartCount = partCount;
		int index = 0;

		// Top Disk
		for (UINT i = 0; i < m_PartCount; i++) {
			pipeIndices[index++] = 0;
			if (i == m_PartCount - 1)
				pipeIndices[index++] = 1;
			else
				pipeIndices[index++] = i + 2;
			pipeIndices[index++] = i + 1;
		}

		// Bottom Disk
		UINT start = pipeVerticesCount / 2;
		for (UINT i = start, j = 0; j < m_PartCount; i++, j++) {
			pipeIndices[index++] = start;
			pipeIndices[index++] = i + 1;
			if (j == m_PartCount - 1)
				pipeIndices[index++] = start + 1;
			else
				pipeIndices[index++] = i + 2;
		}

		// Side Rectangles
		for (UINT i = 0; i < m_PartCount; i++) {
			pipeIndices[index++] = i + 1;
			if (i == m_PartCount - 1)
				pipeIndices[index++] = 1;
			else
				pipeIndices[index++] = i + 2;
			pipeIndices[index++] = i + start + 1;

			if (i == m_PartCount - 1)
			{
				pipeIndices[index++] = 1;
				pipeIndices[index++] = 1 + start;
			}
			else
			{
				pipeIndices[index++] = i + 2;
				pipeIndices[index++] = i + start + 2;
			}
			pipeIndices[index++] = i + start + 1;

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

	UINT m_PartCount;

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
		// Center Vertices
		pipe[0] = Vertex(XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(Colors::AntiqueWhite));
		pipe[pipeVerticesCount / 2] = Vertex(XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(Colors::Red));

		// Disks Vertcies
		int index = 1;
		float step = XM_2PI / m_PartCount;
		for (int disc = 0; disc < 2; disc++)
		{
			for (float angle = 0.0f; angle < XM_2PI; angle += step, index++)
			{
				x = cos(angle);
				z = sin(angle);
				pipe[index] = Vertex(XMFLOAT3(x, disc == 0 ? 1.0f : -1.0f, z), XMFLOAT4(Colors::LightSkyBlue));
			}
			index++;
		}

	};

#pragma endregion

};

#pragma endregion