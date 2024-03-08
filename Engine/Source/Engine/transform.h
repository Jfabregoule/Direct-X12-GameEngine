#pragma once

#include <DirectXMath.h>

using namespace DirectX;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									Transform Struct 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Transform Struct

struct Transform
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
    XMFLOAT3    m_VectorScale;
    XMFLOAT4X4  m_MatrixScale;

    // Rotation
    XMFLOAT3    m_VectorRotation;
    XMFLOAT3    m_VectorDirection;
    XMFLOAT3    m_VectorRight;
    XMFLOAT3    m_VectorUp;
    XMFLOAT4    m_QuaternionRotation;
    XMFLOAT4X4  m_MatrixRotation;

    // Position
    XMFLOAT3    m_VectorPosition;
    XMFLOAT4X4  m_MatrixPosition;

    // Result
    XMFLOAT4X4  m_Matrix;

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

#pragma endregion

};

#pragma endregion