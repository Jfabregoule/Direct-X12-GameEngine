#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <DirectXColors.h>
#include <vector>

using namespace DirectX;

struct ENGINE_API SphereMesh
{
	UINT sphereVerticesCount; // Taille du tableau sphere

	Vertex* sphere;

	UINT* sphereIndices; // 102 indices = nbPointsCercle * 4 * 3

	UINT sphereIndicesCount;
	UINT m_PartCount;

	SphereMesh() {
	};

	void InitSphereMesh(UINT partCount)
	{
		sphereVerticesCount = partCount * 2 + 2;
		sphere = new Vertex[sphereVerticesCount];
		sphereIndicesCount = partCount * 4 * 3;
		sphereIndices = new UINT[sphereIndicesCount];
		m_PartCount = partCount;
		int index = 0;

		// Top Disk
		for (UINT i = 0; i < m_PartCount; i++) {
			sphereIndices[index++] = 0;
			if (i == m_PartCount - 1)
				sphereIndices[index++] = 1;
			else
				sphereIndices[index++] = i + 2;
			sphereIndices[index++] = i + 1;
		}

		for (UINT i = 0; i < m_PartCount; i++) {
			sphereIndices[index++] = i + m_PartCount;
			if (i == m_PartCount - 1)
				sphereIndices[index++] = 1;
			else
				sphereIndices[index++] = i + 1 + m_PartCount;
			sphereIndices[index++] = 11;
		} // Début demi cercle omg omg omg
	}

	void GenerateSphere()
	{
		float x, y, z, xangle, yangle;
		// Center Vertices
		sphere[0] = Vertex(XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(Colors::AntiqueWhite));
		sphere[11] = Vertex(XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(Colors::AntiqueWhite));
		
		// Disks Vertcies
		int index = 1;
		float stepx = XM_PI / m_PartCount;
		float stepy = 2.0f*XM_PI / m_PartCount;
		for (int disc = 0; disc < 2; disc++)
		{
			for (float xangle = 0.0f; xangle < XM_2PI; xangle += stepx, index++)
			{
				for (float yangle = 0.0f; yangle < XM_PIDIV2; yangle += stepy)
				{
					x = sin(xangle) * sin(yangle);
					y = -sin(xangle);
					z = cos(xangle) * cos(yangle);
					sphere[index] = Vertex(XMFLOAT3(x, y, z), XMFLOAT4(Colors::LightSkyBlue));
				}
			}
			index++;
		}
	};
};