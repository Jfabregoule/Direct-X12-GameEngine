#pragma once

#include <stdio.h>
#include <d3d12.h>
#include "Platform/Win32/d3dx12.h"
#include "DirectX12/MathHelper.h"
#include <dxgi1_6.h>
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


namespace DX12Utils {

    

}