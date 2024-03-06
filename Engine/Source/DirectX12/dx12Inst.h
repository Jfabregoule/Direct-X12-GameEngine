#pragma once
#include "Engine/DirectX12Utils.h"
#include "Engine/Entity.h"
#include <dxgi1_4.h> // Include for DXGI interfaces

#pragma region Classe

class ENGINE_API DirectX12Instance {

private:

    /* - Singleton reference to static class - */

    static DirectX12Instance* inst;

    static DirectX12Instance* Instance() { return inst; }


public:

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                               Contructor/Destructor                                 |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Constructor And Destructor

    DirectX12Instance(HWND handle);
    ~DirectX12Instance();

#pragma endregion

public:

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                     Attributes                                      |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Attributes
  
    HWND m_handle;

    BOOL GameRunning = TRUE;

    ID3D12Debug* debug_interface;
    ID3D12Device* device;
    IDXGISwapChain4* swap_chain; // Use IDXGISwapChain4
    IDXGIFactory4* dxgi_factory; // Use IDXGIFactory4
    ID3D12CommandQueue* graphics_command_queue;
    ID3D12RootSignature* root_signature;

    enum {
        FRAMES = 3
    };

    ID3D12DescriptorHeap* render_target_descriptor_heap;
    ID3D12CommandAllocator* command_allocators[FRAMES];
    D3D12_CPU_DESCRIPTOR_HANDLE render_target_descriptors[FRAMES];
    ID3D12Resource* render_target_buffers[FRAMES];
    D3D12_COMMAND_QUEUE_DESC graphics_command_queue_desc = {};
    UINT m_CurrentBufferIndex = 0;
    D3D12_VIEWPORT viewport = { 0 };
    D3D12_RECT scissor = { 0 };
    ID3DBlob* vertex_shader;
    ID3DBlob* pixel_shader;

    ID3D12Fence* fence[FRAMES] = { nullptr };
    UINT64 fence_value[FRAMES] = { 0 };
    HANDLE fence_event[FRAMES] = { nullptr };

    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
    ID3D12PipelineState* pipeline_state;

    D3D12_DESCRIPTOR_HEAP_DESC render_target_descriptor_heap_desc = {};
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;

    Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;
    Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> mRtvHeap;
    Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> mDsvHeap;

    Entity* m_pMainCamera;

    std::vector <Entity*> m_ListEntities;

    XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    XMMATRIX m_worldViewProjMatrix;

    int mClientWidth = 1280;
    int mClientHeight = 720;

    float count = 0;
    float mTheta = 1.5f * XM_PI;
    float mPhi = XM_PIDIV4;
    float mRadius = 5.0f;

    bool      m4xMsaaState = false;    // 4X MSAA enabled
    UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA


    ID3D12Resource* m_constantBufferGPU;
    // Méthode pour initialiser le tampon de constantes sur le GPU
    CD3DX12_HEAP_PROPERTIES test = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    Camera* m_pMainCamComponent;
    UINT8* m_pConstantBufferData;

    HRESULT m_hresult;

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                       Inits                                         |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Init

    VOID InitGraphics() {
        HRESULT hresult;

        // Initialisation du débogueur
        hresult = D3D12GetDebugInterface(IID_PPV_ARGS(&debug_interface));
        CheckSucceeded(hresult);
        OutputDebugString(L"Debug layer enabled.\n");

        // Initialisation de la fabrique DXGI
        hresult = CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgi_factory)); // Use CreateDXGIFactory2 for IDXGIFactory4
        CheckSucceeded(hresult);
        OutputDebugString(L"DXGI Factory created.\n");

        // Création du périphérique DirectX 12
        hresult = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
        CheckSucceeded(hresult);
        OutputDebugString(L"DirectX 12 device created.\n");

        // Création de la file de commandes graphiques
        graphics_command_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        hresult = device->CreateCommandQueue(&graphics_command_queue_desc, IID_PPV_ARGS(&graphics_command_queue));
        CheckSucceeded(hresult);
        OutputDebugString(L"Graphics command queue created.\n");

        RECT windowRect;
        GetClientRect(m_handle, &windowRect);
        int width = windowRect.right - windowRect.left;
        int height = windowRect.bottom - windowRect.top;

        // Initialisation de la description de la chaîne d'échange
        DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
        swap_chain_desc.Width = width;
        swap_chain_desc.Height = height;
        swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = FRAMES;
        swap_chain_desc.Scaling = DXGI_SCALING_STRETCH;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        IDXGISwapChain1* tempSwapChain;
        hresult = dxgi_factory->CreateSwapChainForHwnd(graphics_command_queue, m_handle, &swap_chain_desc, nullptr, nullptr, &tempSwapChain);
        CheckSucceeded(hresult);

        // Convertir la chaîne d'échange en IDXGISwapChain4
        hresult = tempSwapChain->QueryInterface(IID_PPV_ARGS(&swap_chain));
        tempSwapChain->Release(); // Libérer la référence temporaire
        CheckSucceeded(hresult);

        OutputDebugString(L"Swap chain created.\n");

        // Initialisation du viewport et de la zone de découpage
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = static_cast<float>(swap_chain_desc.Width);
        viewport.Height = static_cast<float>(swap_chain_desc.Height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;

        scissor.right = static_cast<LONG>(swap_chain_desc.Width);
        scissor.bottom = static_cast<LONG>(swap_chain_desc.Height);
        OutputDebugString(L"Viewport and scissor initialized.\n");

        // Initialisation du tas de descripteurs de cible de rendu
        render_target_descriptor_heap_desc.NumDescriptors = FRAMES;
        render_target_descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        hresult = device->CreateDescriptorHeap(&render_target_descriptor_heap_desc, IID_PPV_ARGS(&render_target_descriptor_heap));
        CheckSucceeded(hresult);
        OutputDebugString(L"Render target descriptor heap created.\n");

        size_t render_target_descriptor_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE render_target_descriptor = render_target_descriptor_heap->GetCPUDescriptorHandleForHeapStart();

        // Initialisation des buffers de cible de rendu
        for (UINT frame = 0; frame < FRAMES; frame++) {
            ID3D12Resource* buffer;
            hresult = swap_chain->GetBuffer(frame, IID_PPV_ARGS(&buffer));
            CheckSucceeded(hresult);
            render_target_buffers[frame] = buffer;
            device->CreateRenderTargetView(buffer, 0, render_target_descriptor);
            render_target_descriptors[frame] = render_target_descriptor;
            render_target_descriptor.ptr += render_target_descriptor_size;
            hresult = device->CreateCommandAllocator(graphics_command_queue_desc.Type, IID_PPV_ARGS(&command_allocators[frame]));
            CheckSucceeded(hresult);
        }
        OutputDebugString(L"Render target buffers initialized.\n");

        CreateRtvAndDsvDescriptorHeaps();

        // Create the depth/stencil buffer and view.
        D3D12_RESOURCE_DESC depthStencilDesc;
        depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        depthStencilDesc.Alignment = 0;
        depthStencilDesc.Width = mClientWidth;
        depthStencilDesc.Height = mClientHeight;
        depthStencilDesc.DepthOrArraySize = 1;
        depthStencilDesc.MipLevels = 1;

        depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

        depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
        depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
        depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

        D3D12_CLEAR_VALUE optClear;
        optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        optClear.DepthStencil.Depth = 1.0f;
        optClear.DepthStencil.Stencil = 0;
        CD3DX12_HEAP_PROPERTIES ziziProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        device->CreateCommittedResource(
            &ziziProperties,
            D3D12_HEAP_FLAG_NONE,
            &depthStencilDesc,
            D3D12_RESOURCE_STATE_COMMON,
            &optClear,
            IID_PPV_ARGS(mDepthStencilBuffer.GetAddressOf()));

        // Create descriptor to mip level 0 of entire resource using the format of the resource.
        D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
        dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
        dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        dsvDesc.Texture2D.MipSlice = 0;
        device->CreateDepthStencilView(mDepthStencilBuffer.Get(), &dsvDesc, mDsvHeap->GetCPUDescriptorHandleForHeapStart());
        CreateFencesAndEvents();

        float aspectRatio = static_cast<float>(mClientWidth) / static_cast<float>(mClientHeight);


        m_pMainCamera = new Entity(device);
        Camera* cam = dynamic_cast<Camera*>(m_pMainCamera->AddComponentByName("camera"));
        cam->Init(aspectRatio);
        m_pMainCamera->Translate(0.0f, 3.0f, -10.0f);

        m_pMainCamComponent = dynamic_cast<Camera*>(m_pMainCamera->GetComponentByName("camera"));

        auto testo = CD3DX12_RESOURCE_DESC::Buffer(sizeof(m_worldViewProjMatrix));
        m_hresult = device->CreateCommittedResource(
            &test,
            D3D12_HEAP_FLAG_NONE,
            &testo,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&m_constantBufferGPU));
        CheckSucceeded(m_hresult);

    }

    VOID CreateRtvAndDsvDescriptorHeaps()
    {
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
        rtvHeapDesc.NumDescriptors = 3;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        rtvHeapDesc.NodeMask = 0;
        device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(mRtvHeap.GetAddressOf()));


        D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
        dsvHeapDesc.NumDescriptors = 1;
        dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        dsvHeapDesc.NodeMask = 0;
        device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(mDsvHeap.GetAddressOf()));
    }


    VOID CreateFencesAndEvents() {
        for (int i = 0; i < FRAMES; ++i) {
            HRESULT hresult = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence[i]));
            CheckSucceeded(hresult);
            fence_event[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
            if (fence_event[i] == nullptr) {
                // Handle event creation failure
            }
        }
        OutputDebugString(L"Fences and events created.\n");
    }

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                     Methods                                         |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Methods

    VOID RenderFrame();
    VOID Draw(Entity* entity);
    VOID DrawAll();
    VOID SetBackground(float r, float g, float b, float a = 0.0f);
    VOID UpdateCam(Entity* entity);

#pragma endregion

    /*
    *  -------------------------------------------------------------------------------------
    * |                                                                                     |
    * |                                     Clean Up                                        |
    * |                                                                                     |
    *  -------------------------------------------------------------------------------------
    */

#pragma region Clean Up

    VOID ReleasePipeline() {
        if (pipeline_state) {
            pipeline_state->Release();
            pipeline_state = nullptr;
        }
        OutputDebugString(L"Pipeline state released.\n");
    }


    VOID ReleaseFrame() {
        for (int i = 0; i < FRAMES; ++i) {
            if (fence[i] != nullptr) {
                fence[i]->Release();
                fence[i] = nullptr;
            }
            if (fence_event[i] != nullptr) {
                CloseHandle(fence_event[i]);
                fence_event[i] = nullptr;
            }
        }
    }

    VOID Cleanup() {
        // Libérer les objets de chaque trame
        for (int i = 0; i < FRAMES; ++i) {
            if (command_allocators[i]) {
                command_allocators[i]->Release();
                command_allocators[i] = nullptr;
            }
            if (render_target_buffers[i]) {
                render_target_buffers[i]->Release();
                render_target_buffers[i] = nullptr;
            }
            if (fence[i]) {
                fence[i]->Release();
                fence[i] = nullptr;
            }
            if (fence_event[i]) {
                CloseHandle(fence_event[i]);
                fence_event[i] = nullptr;
            }
        }

        // Libérer le reste des objets
        if (render_target_descriptor_heap) {
            render_target_descriptor_heap->Release();
            render_target_descriptor_heap = nullptr;
        }
        if (swap_chain) {
            swap_chain->Release();
            swap_chain = nullptr;
        }
        if (graphics_command_queue) {
            graphics_command_queue->Release();
            graphics_command_queue = nullptr;
        }
        if (device) {
            device->Release();
            device = nullptr;
        }
        if (dxgi_factory) { 
            dxgi_factory->Release();
            dxgi_factory = nullptr;
        } 
        if (debug_interface) {
            debug_interface->Release();
            debug_interface = nullptr; 
        }
        if (command_list) { 
            command_list.Reset(); 
        }
        if (mDepthStencilBuffer) {
            mDepthStencilBuffer->Release(); 
            mDepthStencilBuffer = nullptr; 
        }
    }

#pragma endregion

};

#pragma endregion