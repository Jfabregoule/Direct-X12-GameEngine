#pragma once
#include "BlankProject.h"
#include <DirectXMath.h>
#include <Math.h>

namespace Maths {

	float GetNorm(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {

		DirectX::XMFLOAT3 e = DirectX::XMFLOAT3(b.x - a.x, b.y - a.y, b.z - a.z);

		float u = sqrt(e.x * e.x + e.y * e.y + e.z * e.z);

		return u;

	};

	DirectX::XMFLOAT3 AngleVectors(DirectX::XMFLOAT3 TargetPosition, DirectX::XMFLOAT3 EntityPosition) {

		DirectX::XMVECTOR VTargetPosition = DirectX::XMLoadFloat3(&TargetPosition);
		DirectX::XMVECTOR VEntityPosition = DirectX::XMLoadFloat3(&EntityPosition);

		//DirectX::XMVECTOR normalizedVector1 = DirectX::XMVector3Normalize(vector1);
		//DirectX::XMVECTOR normalizedVector2 = DirectX::XMVector3Normalize(vector2);

		//DirectX::XMVECTOR projX1 = DirectX::XMVectorSetY(normalizedVector1, 0.0f);
		//DirectX::XMVECTOR projY1 = DirectX::XMVectorSetX(normalizedVector1, 0.0f);
		//DirectX::XMVECTOR projZ1 = DirectX::XMVectorSetZ(normalizedVector1, 0.0f); // Projection sur l'axe Z
		//DirectX::XMVECTOR projX2 = DirectX::XMVectorSetY(normalizedVector2, 0.0f);
		//DirectX::XMVECTOR projY2 = DirectX::XMVectorSetX(normalizedVector2, 0.0f);
		//DirectX::XMVECTOR projZ2 = DirectX::XMVectorSetZ(normalizedVector2, 0.0f); // Projection sur l'axe Z

		//// Calculer les angles entre les projections
		//float angleX = DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(projX1, projX2));
		//float angleY = DirectX::XMVectorGetY(DirectX::XMVector3AngleBetweenNormals(projY1, projY2));
		//float angleZ = DirectX::XMVectorGetZ(DirectX::XMVector3AngleBetweenNormals(projZ1, projZ2));

		//// Retourner les angles pour chaque axe
		//return DirectX::XMFLOAT3(angleX, angleY, angleZ);

		// Calculer la direction vers la cible depuis la position de l'entité
		DirectX::XMVECTOR EntityToTarget = DirectX::XMVectorSubtract(VTargetPosition, VEntityPosition);
		DirectX::XMVECTOR ForwardDirection = DirectX::XMVector3Normalize(EntityToTarget);

		DirectX::XMFLOAT3 floatv;
		DirectX::XMStoreFloat3(&floatv, ForwardDirection);

		return floatv;
	};

};