#pragma once
#include "Engine.h"

#include <stdio.h>
#include <d3d12.h>
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"
#include <dxgi.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <dxgidebug.h>

#define Assert(x) \
    if (!(x)) { MessageBoxA(0, #x, "Assertion Failed", MB_OK); __debugbreak(); }
#define Check(x) \
    if (!(x)) { MessageBoxA(0, #x, "Check Failed", MB_OK); __debugbreak(); }

#define CheckSucceeded(hresult) \
    Check(SUCCEEDED(hresult));

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dxguid.lib")


struct Vertex {
    DirectX::XMFLOAT3 position;
};

namespace DX12Utils {

    void PrintCompileErrorMessages(ID3DBlob* error);

    HRESULT CompileShader(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code);

    void ReportLiveObjects();
}