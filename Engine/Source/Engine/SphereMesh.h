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

		m_PartCount = partCount;
		sphereVerticesCount = (partCount + 1) * (partCount + 2) / 2;
		sphereIndicesCount = partCount * partCount * 10;
		sphere = new Vertex[sphereVerticesCount];

		sphereIndices = new UINT[sphereIndicesCount];

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
		//assert(index == sphereIndicesCount);
	}

	void GenerateSphere()
	{
		float x, y, z, phi, theta, phiStep, thetaStep;
		// Center Vertices
		sphere[0] = Vertex(DirectX::XMFLOAT3(0.0f, 2.0f, 0.0f), DirectX::XMFLOAT4(Colors::AntiqueWhite), DirectX::XMFLOAT2(0,0));
		sphere[sphereVerticesCount - 1] = Vertex(DirectX::XMFLOAT3(0.0f, 2.0f, 0.0f), DirectX::XMFLOAT4(Colors::AntiqueWhite), DirectX::XMFLOAT2(0, 0));

		// Defining angles Steps
		phiStep = XM_PI / m_PartCount;
		thetaStep = 2.0f * XM_PI / m_PartCount;

		// Disks Vertcies
		float radius = 1.0f;
		int index = 1;

		for (int slice = 0; slice < m_PartCount; slice++)
		{
			phi = slice * phiStep; // Polar angle

			for (int stack = 0; stack <= m_PartCount; stack++)
			{
				theta = stack * thetaStep; // Azimuthal angle

				x = radius * sin(phi) * cos(theta);
				y = radius * sin(phi) * sin(theta);
				z = radius * cos(phi);

				sphere[index++] = Vertex(DirectX::XMFLOAT3(x, y, z), DirectX::XMFLOAT4(Colors::LightSkyBlue), DirectX::XMFLOAT2(0, 0));
			}
		}
	};
};

