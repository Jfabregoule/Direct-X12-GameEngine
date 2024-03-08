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
  
    //Window
    HWND m_handle;

    BOOL GameRunning = TRUE;

    ID3D12Debug* debug_interface;
    ID3D12Device* device;
    IDXGIFactory4* dxgi_factory; // Use IDXGIFactory4

    //Swap Chain
    DXGI_SWAP_CHAIN_DESC1 m_swap_chain_desc = {};
    IDXGISwapChain4* swap_chain; // Use IDXGISwapChain4

    enum {
        FRAMES = 3
    };

    //Descriptor HeapDesc
    ID3D12DescriptorHeap* mRTVheap;
    ID3D12DescriptorHeap* mDsvHeap;
    ID3D12DescriptorHeap* mSrvHeap;

    //Command List queue allocator
    D3D12_COMMAND_QUEUE_DESC m_graphics_command_queue_desc = {};
    ID3D12CommandQueue* graphics_command_queue;
    ID3D12CommandAllocator* command_allocator;
    ID3D12GraphicsCommandList* mCommandList;

    //RTV 
    D3D12_CPU_DESCRIPTOR_HANDLE render_target_descriptors[FRAMES];
    ID3D12Resource* render_target_buffers[FRAMES];
    UINT m_CurrentBufferIndex = 0;

    //Viewport/scissor
    D3D12_VIEWPORT viewport = { 0 };
    D3D12_RECT scissor = { 0 };

    //Fences
    ID3D12Fence* fence[FRAMES] = { nullptr };
    UINT64 fence_value[FRAMES] = { 0 };
    HANDLE fence_event[FRAMES] = { nullptr };

    ID3D12PipelineState* pipeline_state;

    D3D12_DESCRIPTOR_HEAP_DESC render_target_descriptor_heap_desc = {};
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;

    //DepthStencilBuffer
    ID3D12Resource* mDepthStencilBuffer;

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

    TextureManager* m_pTextureManager;

    Camera* m_pMainCamComponent;

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

    VOID Init() {

        InitGraphics();
        CreateCommandListQueue();
        CreateSwapChain();
        CreateViewportScissor();
        CreateRTVDescHeap();
        CreateRTVBuffers();
        CreateRtvAndDsvDescriptorHeaps();
        CreateDepthStencilBuffer();
        CreateDepthStencilView();
        CreateFencesAndEvents();
        BuildShaderResourceView();
        CreateCamera();
        CreateTextureManager();
        InitializePostCommand();
    }

    VOID InitGraphics();
    VOID CreateCommandListQueue();
    VOID CreateSwapChain();
    VOID CreateViewportScissor();
    VOID CreateRTVDescHeap();
    VOID CreateRTVBuffers();
    VOID CreateRtvAndDsvDescriptorHeaps();
    VOID CreateDepthStencilBuffer();
    VOID CreateDepthStencilView();
    VOID CreateFencesAndEvents();
    VOID BuildShaderResourceView();
    VOID FlushCommandQueue();

    VOID CreateCamera();
    VOID CreateTextureManager();
    VOID InitializePostCommand();
    VOID InitTextures();

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
        if (mRTVheap) {
            mRTVheap->Release();
            mRTVheap = nullptr;
        }
        if (swap_chain) {
            swap_chain->Release();
            swap_chain = nullptr;
        }
        if (command_allocator) {
            command_allocator->Release();
            command_allocator = nullptr;
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
        if (mCommandList) {
            mCommandList->Release();
            mCommandList = nullptr;
        }
        if (mDepthStencilBuffer) {
            mDepthStencilBuffer->Release();
            mDepthStencilBuffer = nullptr;
        }
    }

#pragma endregion

};

#pragma endregion