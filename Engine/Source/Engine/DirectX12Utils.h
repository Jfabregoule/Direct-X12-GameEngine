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

namespace DX12Utils {

    void PrintCompileErrorMessages(ID3DBlob* error) {
        char temp[1024];
        sprintf_s(temp, sizeof(temp), "%.*s", (int)error->GetBufferSize(), (char*)error->GetBufferPointer());
        OutputDebugStringA(temp);
    }

    HRESULT CompileShader(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code) {
        ID3DBlob* error;
        HRESULT result = D3DCompileFromFile(filename, 0, 0, entrypoint, profile, D3DCOMPILE_DEBUG, 0, out_code, &error);
        if (result != S_OK) {
            PrintCompileErrorMessages(error);
        }
        return result;
    }

    void ReportLiveObjects()
    {
        // Obtenez une instance de l'interface de débogage DirectX
        IDXGIDebug1* dxgiDebug;
        HRESULT hr = DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));
        if (SUCCEEDED(hr))
        {
            // Appeler ReportLiveObjects()
            dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
            dxgiDebug->Release(); // N'oubliez pas de libérer l'interface après utilisation
        }
        else
        {
            // Gérer l'échec de l'obtention de l'interface de débogage
        }
    }

}