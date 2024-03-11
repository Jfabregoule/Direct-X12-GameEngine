#pragma once
#include <DirectXMath.h>

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                  Vertex Struct                                      |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Vertex Struct

struct Vertex {
    Vertex() :
        position(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)),
        color(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)),
        text(DirectX::XMFLOAT2(0.0f, 0.0f)) {}
    Vertex(
        const DirectX::XMFLOAT3 p,
        const DirectX::XMFLOAT4 c,
        const DirectX::XMFLOAT2 t) :
        position(p),
        color(c),
        text(t) {}

    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;
    DirectX::XMFLOAT2 text;
};

#pragma endregion