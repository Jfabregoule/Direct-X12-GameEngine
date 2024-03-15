#pragma once

#include "Engine.h"

#include <vector>
#include <DirectXColors.h>

#include "DirectX12/Vertex.h"

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
		sphereVerticesCount = (m_PartCount + 2) * (m_PartCount + 2);
		sphereIndicesCount = partCount * partCount * 6;
		sphere = new Vertex[sphereVerticesCount];

		sphereIndices = new UINT[sphereIndicesCount];

		int index = 0;
		int basicIndex = 1;
		int ringVertexCount = m_PartCount + 1;


		// Top semi-circle of first half-sphere
		for (UINT slice = 0; slice < m_PartCount / 2; slice++)
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


		// Bottom semi-circle of second half-sphere
		for (UINT slice = m_PartCount / 2; slice < m_PartCount; slice++)
		{
			for (UINT stock = 0; stock < m_PartCount; stock++)
			{
				sphereIndices[index++] = basicIndex + slice * ringVertexCount + stock;
				sphereIndices[index++] = basicIndex + slice * ringVertexCount + stock + 1;
				sphereIndices[index++] = basicIndex + (slice + 1) * ringVertexCount + stock;

				sphereIndices[index++] = basicIndex + (slice + 1) * ringVertexCount + stock;
				sphereIndices[index++] = basicIndex + slice * ringVertexCount + stock + 1;
				sphereIndices[index++] = basicIndex + (slice + 1) * ringVertexCount + stock + 1;
			}
		}

		assert(index = sphereIndicesCount);
	}

	void GenerateSphere()
	{
		float x, y, z, phi, theta, phiStep, thetaStep;
		// Center Vertices
		sphere[0] = Vertex(DirectX::XMFLOAT3(0.0f, 2.0f, 0.0f), DirectX::XMFLOAT4(Colors::LightSkyBlue), DirectX::XMFLOAT2(0, 0));

		// Defining angles Steps
		phiStep = XM_PI / m_PartCount; // Divided by 2 for half-sphere
		thetaStep = 2.0f * XM_PI / m_PartCount;

		// Disks Vertices
		float radius = 1.0f;
		int index = 1;

		// Premiere demi-sph�re
		for (int slice = m_PartCount; slice >= m_PartCount / 2; slice--)
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

		// Deuxieme demi-sphere (inverse)
		for (int slice = 0; slice <= m_PartCount / 2 + 1; slice++)
		{
			phi = slice * phiStep; // Polar angle

			for (int stack = 0; stack <= m_PartCount; stack++)
			{
				theta = stack * thetaStep; // Azimuthal angle

				// Calcul des coordonnees inversees par rapport a la premiere demi-sphere
				x = radius * sin(phi) * cos(theta);
				y = -radius * sin(phi) * sin(theta);
				z = radius * cos(phi); // Inversion de z

				sphere[index++] = Vertex(DirectX::XMFLOAT3(x, y, z), DirectX::XMFLOAT4(Colors::LightSkyBlue), DirectX::XMFLOAT2(0, 0));
			}
		}
		assert(index = sphereVerticesCount);
	}
};