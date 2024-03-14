#pragma once

#include <DirectXMath.h>
/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Transform Struct 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Transform Struct

struct ENGINE_API Transform
{

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |									    Attributs 									    |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Attributs

    // Scale
    DirectX::XMFLOAT3    m_VectorScale;
    DirectX::XMFLOAT4X4  m_MatrixScale;

    // Rotation
    DirectX::XMFLOAT3    m_VectorRotation;
    DirectX::XMFLOAT3    m_VectorDirection;
    DirectX::XMFLOAT3    m_VectorRight;
    DirectX::XMFLOAT3    m_VectorUp;
    DirectX::XMFLOAT4    m_QuaternionRotation;
    DirectX::XMFLOAT4X4  m_MatrixRotation;

    // Position
    DirectX::XMFLOAT3    m_VectorPosition;
    DirectX::XMFLOAT4X4  m_MatrixPosition;

    // Result
    DirectX::XMFLOAT4X4  m_Matrix;

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |									    Methods 									    |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Methods

    void Identity();
    void Scale(float scaleX, float scaleY, float scaleZ);
    void Rotate(float yaw, float pitch, float roll);
    void Translate(float postionX, float positionY, float positionZ);
    void UpdateMatrix();

    void SetRotationVector(DirectX::XMFLOAT3 rotation) { m_VectorRotation = rotation; }
    DirectX::XMFLOAT3 GetRotationVector() const { return m_VectorRotation; }
    DirectX::XMFLOAT3 GetScaleVector() const { return m_VectorScale; }

    DirectX::XMFLOAT3 GetForwardVector();
    DirectX::XMVECTOR GetRightVector();
    DirectX::XMVECTOR GetUpVector();

    void RotateEntityTowardsObject(const DirectX::XMFLOAT3& objectPosition);

#pragma endregion

};

#pragma endregion