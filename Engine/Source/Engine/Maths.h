#pragma once
#include "Engine.h"
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

		DirectX::XMVECTOR EntityToTarget = DirectX::XMVectorSubtract(VEntityPosition,VTargetPosition);
		DirectX::XMVECTOR ForwardDirection = DirectX::XMVector3Normalize(EntityToTarget);

		DirectX::XMFLOAT3 floatv;
		DirectX::XMStoreFloat3(&floatv, ForwardDirection);

		return floatv;
	};

	DirectX::XMFLOAT3 CalculateEulerAnglesFromDirection(const DirectX::XMFLOAT3& direction) {
		float pitch = asinf(direction.y);
		float yaw = atan2f(direction.x, direction.z);
		float roll = atan2f(direction.z, direction.x);

		return DirectX::XMFLOAT3(pitch, yaw, roll);
	}

};