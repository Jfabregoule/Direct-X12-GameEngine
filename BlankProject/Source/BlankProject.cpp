#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Win32/WinEntry.h"
#include "Engine/DirectX12Utils.h"
#include "DirectX12/MathHelper.h"

BOOL GameRunning = TRUE;

ID3D12Debug* debug_interface;
ID3D12Device* device;
IDXGISwapChain3* swap_chain;
IDXGIFactory2* dxgi_factory;
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
DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = { 0 };
IDXGISwapChain1* swap_chain1;
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

HWND handle;

struct Vertex {
    DirectX::XMFLOAT3 position;
};

Vertex vertices[] = {
    {DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f)},   // Vertex 0
    {DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f)},  // Vertex 1
    {DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f)}  // Vertex 2
};

using namespace DirectX;

VOID BuildBoxGeometry() {

    // Create vertex buffer
    const UINT vertexBufferSize = sizeof(vertices);
    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
    device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertexBuffer)
    );

    // Upload vertex data to the vertex buffer
    UINT8* pVertexDataBegin;
    CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU
    vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    memcpy(pVertexDataBegin, vertices, sizeof(vertices));
    vertexBuffer->Unmap(0, nullptr);

    // Initialize the vertex buffer view
    vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = sizeof(Vertex);
    vertexBufferView.SizeInBytes = sizeof(vertices);
}

void Cleanup() {
    for (int i = 0; i < FRAMES; ++i) {
        if (command_allocators[i]) {
            command_allocators[i]->Release();
            command_allocators[i] = nullptr;
        }
        if (render_target_buffers[i]) {
            render_target_buffers[i]->Release();
            render_target_buffers[i] = nullptr;
        }
    }

    if (render_target_descriptor_heap) {
        render_target_descriptor_heap->Release();
        render_target_descriptor_heap = nullptr;
    }

    if (root_signature) {
        root_signature->Release();
        root_signature = nullptr;
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
}

VOID InitGraphics() {
    HRESULT hresult;

    // Initialisation du débogueur
    hresult = D3D12GetDebugInterface(IID_PPV_ARGS(&debug_interface));
    CheckSucceeded(hresult);
    debug_interface->EnableDebugLayer();

    // Initialisation de la fabrique DXGI
    hresult = CreateDXGIFactory(IID_PPV_ARGS(&dxgi_factory));
    CheckSucceeded(hresult);

    // Création du périphérique DirectX 12
    hresult = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
    CheckSucceeded(hresult);

    // Création de la file de commandes graphiques
    graphics_command_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    hresult = device->CreateCommandQueue(&graphics_command_queue_desc, IID_PPV_ARGS(&graphics_command_queue));
    CheckSucceeded(hresult);

    // Initialisation de la description de la chaîne d'échange
    swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.BufferCount = FRAMES;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    // Création de la chaîne d'échange
    hresult = dxgi_factory->CreateSwapChainForHwnd(graphics_command_queue, handle, &swap_chain_desc, 0, 0, &swap_chain1);
    CheckSucceeded(hresult);

    hresult = swap_chain1->QueryInterface(IID_PPV_ARGS(&swap_chain));
    CheckSucceeded(hresult);

    // Obtention de la description de la chaîne d'échange
    swap_chain1->GetDesc1(&swap_chain_desc);

    // Initialisation du viewport et de la zone de découpage
    viewport.Width = (FLOAT)swap_chain_desc.Width;
    viewport.Height = (FLOAT)swap_chain_desc.Height;

    scissor.right = swap_chain_desc.Width;
    scissor.bottom = swap_chain_desc.Height;

    // Initialisation du tas de descripteurs de cible de rendu
    render_target_descriptor_heap_desc.NumDescriptors = FRAMES;
    render_target_descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hresult = device->CreateDescriptorHeap(&render_target_descriptor_heap_desc, IID_PPV_ARGS(&render_target_descriptor_heap));
    CheckSucceeded(hresult);

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
}

VOID InitShaders() {
    HRESULT hresult;

    UINT compiler_flags = D3DCOMPILE_DEBUG;

    hresult = DX12Utils::CompileShader(L".\\Content\\Shaders\\shader.hlsl", "vs_main", "vs_5_0", &vertex_shader);
    CheckSucceeded(hresult);

    hresult = DX12Utils::CompileShader(L".\\Content\\Shaders\\shader.hlsl", "ps_main", "ps_5_0", &pixel_shader);
    CheckSucceeded(hresult);
}

VOID InitRootSignature() {
    HRESULT hresult;

    CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc;
    root_signature_desc.Init(0, 0, 0, 0, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
    ID3DBlob* root_signature_blob;
    ID3DBlob* root_signature_error_blob;
    hresult = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &root_signature_blob, &root_signature_error_blob);
    CheckSucceeded(hresult);

    hresult = device->CreateRootSignature(0, root_signature_blob->GetBufferPointer(), root_signature_blob->GetBufferSize(), IID_PPV_ARGS(&root_signature));
    CheckSucceeded(hresult);
}

VOID InitPipelineState() {
    HRESULT hresult;

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_state_desc = { 0 };
    pipeline_state_desc.VS.pShaderBytecode = vertex_shader->GetBufferPointer();
    pipeline_state_desc.VS.BytecodeLength = vertex_shader->GetBufferSize();
    pipeline_state_desc.PS.pShaderBytecode = pixel_shader->GetBufferPointer();
    pipeline_state_desc.PS.BytecodeLength = pixel_shader->GetBufferSize();
    pipeline_state_desc.pRootSignature = root_signature;
    pipeline_state_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    pipeline_state_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    pipeline_state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    pipeline_state_desc.SampleMask = UINT_MAX;
    pipeline_state_desc.NumRenderTargets = 1;
    pipeline_state_desc.RTVFormats[0] = swap_chain_desc.Format;
    pipeline_state_desc.SampleDesc.Count = 1;
    pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

    // Définir la configuration de l'assemblage d'entrée
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    // Définir la description de l'assemblage d'entrée
    D3D12_INPUT_LAYOUT_DESC inputLayoutDesc;
    inputLayoutDesc.pInputElementDescs = inputElementDescs;
    inputLayoutDesc.NumElements = _countof(inputElementDescs);

    // Configurer la description de l'assemblage d'entrée dans la description de l'état du pipeline
    pipeline_state_desc.InputLayout = inputLayoutDesc;

    hresult = device->CreateGraphicsPipelineState(&pipeline_state_desc, IID_PPV_ARGS(&pipeline_state));
    CheckSucceeded(hresult);
}

VOID RenderFrame() {
    UINT frame = swap_chain->GetCurrentBackBufferIndex();

    command_allocators[frame]->Reset();
    command_list.Reset();

    HRESULT hresult = device->CreateCommandList(0, graphics_command_queue_desc.Type, command_allocators[frame], 0, IID_PPV_ARGS(command_list.GetAddressOf()));
    CheckSucceeded(hresult);

    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    float clear_color[4] = { 0.18f, 0.18f, 0.18f, 1.0f };

    auto transitionToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    command_list->ResourceBarrier(1, &transitionToRenderTarget);

    command_list->RSSetViewports(1, &viewport);
    command_list->RSSetScissorRects(1, &scissor);
    command_list->ClearRenderTargetView(current_render_target_descriptor, clear_color, 0, 0);

    // Définir l'état du pipeline et la signature racine
    command_list->SetGraphicsRootSignature(root_signature);
    command_list->SetPipelineState(pipeline_state);

    command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Définir le tampon de sommets pour le triangle construit par BuildBoxGeometry
    command_list->IASetVertexBuffers(0, 1, &vertexBufferView);

    // Dessiner le triangle construit par BuildBoxGeometry
    command_list->OMSetRenderTargets(1, &current_render_target_descriptor, 0, 0);
    command_list->DrawInstanced(3, 1, 0, 0);

    auto transitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    command_list->ResourceBarrier(1, &transitionToPresent);

    command_list->Close();
    ID3D12CommandList* command_lists[] = { command_list.Get() };
    graphics_command_queue->ExecuteCommandLists(_countof(command_lists), command_lists);

    fence_value[frame]++;
    graphics_command_queue->Signal(fence[frame], fence_value[frame]);

    if (fence[frame]->GetCompletedValue() < fence_value[frame]) {
        fence[frame]->SetEventOnCompletion(fence_value[frame], fence_event[frame]);
        WaitForSingleObject(fence_event[frame], INFINITE);
    }

    swap_chain->Present(1, 0);
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

VOID ReleasePipeline() {
    if (pipeline_state) {
        pipeline_state->Release();
        pipeline_state = nullptr;
    }
}

VOID CreateFencesAndEvents() {
    for (int i = 0; i < FRAMES; ++i) {
        HRESULT hresult = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence[i]));
        CheckSucceeded(hresult);
        fence_event[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (fence_event[i] == nullptr) {
            // Gérer l'échec de la création de l'événement
        }
    }
}

class BlankProject : public Engine::Simulation {

    // Application

public:

    /* - Application Constructor - */

    BlankProject() {};

    /* - Application Deconstructor - */

    ~BlankProject() {};


public:

    /* - Called to Setup our PerGameSettings - */

    VOID SetupPerGameSettings();

    /* - Called to Initialize the Application - */

    VOID Initialize() {
        handle = Handle();
        Window *window = GetWindow();

        InitGraphics();
        InitRootSignature();
        InitShaders();
        InitPipelineState();
        CreateFencesAndEvents();
        BuildBoxGeometry();

        while (GameRunning) {
            MSG message;
            while (PeekMessage(&message, handle, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            RenderFrame();
            GameRunning = window->IsRunning();
        }
        ReleaseFrame();
        DX12Utils::ReportLiveObjects();
        ReleasePipeline();
        Cleanup();
    };


    /* - Game Loop - Called on a loop while running - */

    VOID Update() { };

    VOID Close() { GameRunning = FALSE; }
};


ENTRYAPP(BlankProject)

VOID BlankProject::SetupPerGameSettings()
{
    /* - Set the Per Game Settings - */
    PerGameSettings::SetGameName(IDS_PERGAMENAME);
    PerGameSettings::SetShortName(IDS_SHORTNAME);
    PerGameSettings::SetMainIcon(IDI_MAINICON);
    PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}
