#pragma once
#include <DirectXMath.h>

struct Vertex {
    Vertex() : 
        position(DirectX::XMFLOAT3(0.0f,0.0f,0.0f)),
        color(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f,0.0f)) {}
    Vertex(
        const DirectX::XMFLOAT3 p,
        const DirectX::XMFLOAT4 c) :
        position(p),
        color(c){}

    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;
};