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
		sphereVerticesCount = partCount * 3 + 2;
		sphere = new Vertex[sphereVerticesCount];
		sphereIndicesCount = partCount * 18;
		sphereIndices = new UINT[sphereIndicesCount];
		m_PartCount = partCount;

		int index = 0;
		int basicIndex = 1;
		int ringVertexCount = m_PartCount + 1;

		for (int i = 1; i <= m_PartCount; i++)
		{
			sphereIndices[index++] = 0;
			sphereIndices[index++] = i + 1;
			sphereIndices[index++] = i;
		}

		// Top semi-circle
		for (UINT slice = 0; slice < m_PartCount - 2; slice++) 
		{ 
			for (UINT stack = 0; stack < m_PartCount; stack++) 
			{ 
				sphereIndices[index++] = basicIndex + slice * ringVertexCount + stack; 
				sphereIndices[index++] = basicIndex + slice * ringVertexCount + stack + 1;  
				sphereIndices[index++] = basicIndex + (slice + 1) * ringVertexCount + stack;   

				sphereIndices[index++] = basicIndex + (slice + 1) * ringVertexCount + stack;  
				sphereIndices[index++] = basicIndex + slice * ringVertexCount + stack + 1;  
				sphereIndices[index++] = basicIndex + (slice + 1) * ringVertexCount + stack + 1;	
			}
		}

		int southPoleIndex = sphereVerticesCount - 1; 
		basicIndex = southPoleIndex - ringVertexCount; 
		for (int j = 0; j < m_PartCount; j++)
		{
			sphereIndices[index++] = southPoleIndex;
			sphereIndices[index++] = basicIndex + j;
			sphereIndices[index++] = basicIndex + j + 1;
		}
	}

	void GenerateSphere()
	{
		float x, y, z, phi, theta, phiStep, thetaStep;
		// Center Vertices
		sphere[0] = Vertex(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT4(Colors::AntiqueWhite));
		sphere[sphereVerticesCount - 1] = Vertex(XMFLOAT3(0.0f, 2.0f, 0.0f), XMFLOAT4(Colors::AntiqueWhite));
		
		// Defining angles Steps
		phiStep = XM_PI / m_PartCount;
		thetaStep = 2.0f * XM_PI / m_PartCount;

		// Disks Vertcies
		int index = 1;

		for (int slice = 0; slice < m_PartCount; slice++)
		{
			phi = slice + phiStep;//Polar angle

			for (int stack = 0; stack <= m_PartCount; stack++)
			{
				theta = stack * thetaStep;

				x = sin(phi) * sin(theta);
				y = -sin(phi);
				z = cos(phi) * cos(theta);

				sphere[index++] = Vertex(XMFLOAT3(x, y, z), XMFLOAT4(Colors::LightSkyBlue));
			}
		}
		
		//for (int slice = 0; slice < slices; ++slice) {
		//	float theta = static_cast<float>(slice) * XM_PI / static_cast<float>(slices); // Polar angle

		//	for (int stack = 0; stack <= slices; ++stack) {
		//		float phi = static_cast<float>(stack) * 2.0f * XM_PI / static_cast<float>(slices); // Azimuthal angle

		//		float x = radius * sinf(theta) * cosf(phi);
		//		float y = radius * cosf(theta);
		//		float z = radius * sinf(theta) * sinf(phi);

		//		spherePoints.emplace_back(x, y, z);
		//	}
		//}
	};
};