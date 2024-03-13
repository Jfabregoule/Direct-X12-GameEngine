#include "Engine.h"
#include "dx12Inst.h"
#include "Engine/Entity.h"
#include "Engine/Mesh.h"
#include "Engine/MeshRenderer.h"
#include "Engine/Texture.h"
#include "Engine/Camera.h"

#include <DirectXMath.h>
#include "DirectX12/MathHelper.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")


DirectX12Instance* DirectX12Instance::inst;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                            Constructor/Destructor                                   |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Constructor And Destructor

DirectX12Instance::DirectX12Instance(HWND handle)
{

    inst = this;

    m_handle = handle;

}

DirectX12Instance::~DirectX12Instance()
{
}

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                      Inits                                          |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Inits

VOID DirectX12Instance::InitGraphics() {
    // Initialisation du débogueur
    m_hresult = D3D12GetDebugInterface(IID_PPV_ARGS(&debug_interface));
    CheckSucceeded(m_hresult);
    OutputDebugString(L"Debug layer enabled.\n");

    // Initialisation de la fabrique DXGI
    m_hresult = CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgi_factory)); // Use CreateDXGIFactory2 for IDXGIFactory4
    CheckSucceeded(m_hresult);
    OutputDebugString(L"DXGI Factory created.\n");

    // Création du périphérique DirectX 12
    m_hresult = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
    CheckSucceeded(m_hresult);
    OutputDebugString(L"DirectX 12 device created.\n");


}

VOID DirectX12Instance::CreateCommandListQueue()
{

    // Création de la file de commandes graphiques
    m_graphics_command_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    m_hresult = device->CreateCommandQueue(&m_graphics_command_queue_desc, IID_PPV_ARGS(&graphics_command_queue));
    CheckSucceeded(m_hresult);
    OutputDebugString(L"Graphics command queue created.\n");

    device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&command_allocator));

    device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        command_allocator, // Associated command allocator
        nullptr,                   // Initial PipelineStateObject
        IID_PPV_ARGS(&mCommandList));

    // Start off in a closed state.  This is because the first time we refer 
    // to the command list we will Reset it, and it needs to be closed before
    // calling Reset.
    mCommandList->Close();
};

VOID DirectX12Instance::CreateSwapChain() {

    RECT windowRect;
    GetClientRect(m_handle, &windowRect);
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    // Initialisation de la description de la chaîne d'échange

    m_swap_chain_desc.Width = width;
    m_swap_chain_desc.Height = height;
    m_swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_swap_chain_desc.SampleDesc.Count = 1;
    m_swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    m_swap_chain_desc.BufferCount = FRAMES;
    m_swap_chain_desc.Scaling = DXGI_SCALING_STRETCH;
    m_swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    m_swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    IDXGISwapChain1* tempSwapChain;
    dxgi_factory->CreateSwapChainForHwnd(graphics_command_queue, m_handle, &m_swap_chain_desc, nullptr, nullptr, &tempSwapChain);


    // Convertir la chaîne d'échange en IDXGISwapChain4
    tempSwapChain->QueryInterface(IID_PPV_ARGS(&swap_chain));
    tempSwapChain->Release(); // Libérer la référence temporaire

    OutputDebugString(L"Swap chain created.\n");
};

VOID DirectX12Instance::CreateViewportScissor() {

    // Initialisation du viewport et de la zone de découpage
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<float>(m_swap_chain_desc.Width);
    viewport.Height = static_cast<float>(m_swap_chain_desc.Height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    scissor.right = static_cast<LONG>(m_swap_chain_desc.Width);
    scissor.bottom = static_cast<LONG>(m_swap_chain_desc.Height);
    OutputDebugString(L"Viewport and scissor initialized.\n");
};

VOID DirectX12Instance::CreateRTVDescHeap()
{
    // Initialisation du tas de descripteurs de cible de rendu
    render_target_descriptor_heap_desc.NumDescriptors = FRAMES;
    render_target_descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    m_hresult = device->CreateDescriptorHeap(&render_target_descriptor_heap_desc, IID_PPV_ARGS(&mRTVheap));
    CheckSucceeded(m_hresult);
    OutputDebugString(L"Render target descriptor heap created.\n");

}

VOID DirectX12Instance::CreateRTVBuffers()
{
    size_t render_target_descriptor_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE render_target_descriptor = mRTVheap->GetCPUDescriptorHandleForHeapStart();

    // Initialisation des buffers de cible de rendu
    for (UINT frame = 0; frame < FRAMES; frame++) {
        ID3D12Resource* buffer;
        swap_chain->GetBuffer(frame, IID_PPV_ARGS(&buffer));
        render_target_buffers[frame] = buffer;
        device->CreateRenderTargetView(buffer, 0, render_target_descriptor);
        render_target_descriptors[frame] = render_target_descriptor;
        render_target_descriptor.ptr += render_target_descriptor_size;

    }
    OutputDebugString(L"Render target buffers initialized.\n");
}

VOID DirectX12Instance::CreateRtvAndDsvDescriptorHeaps()
{
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    dsvHeapDesc.NodeMask = 0;
    device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&mDsvHeap));
}

VOID DirectX12Instance::CreateDepthStencilView()
{
    // Create descriptor to mip level 0 of entire resource using the format of the resource.
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.Texture2D.MipSlice = 0;
    device->CreateDepthStencilView(mDepthStencilBuffer, &dsvDesc, mDsvHeap->GetCPUDescriptorHandleForHeapStart());

}

VOID DirectX12Instance::CreateDepthStencilBuffer()
{
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
        IID_PPV_ARGS(&mDepthStencilBuffer));
};

VOID DirectX12Instance::CreateFencesAndEvents() 
{    {
        for (int i = 0; i < FRAMES; ++i) {
            device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence[i]));
            fence_event[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
            if (fence_event[i] == nullptr) {
                // Handle event creation failure
            }
        }
        OutputDebugString(L"Fences and events created.\n");
    }
}

VOID DirectX12Instance::FlushCommandQueue()
{

    UINT frame = m_CurrentBufferIndex;

    fence_value[frame]++;
    graphics_command_queue->Signal(fence[frame], fence_value[frame]);

    //Regarde si le cpu doit attendre avant d'envoyer les instructions au gpu
    if (fence[frame]->GetCompletedValue() < fence_value[frame]) {
        fence[frame]->SetEventOnCompletion(fence_value[frame], fence_event[frame]);
        WaitForSingleObject(fence_event[frame], INFINITE);
    }
}

VOID DirectX12Instance::SetEntityAsMainCamera(Entity* entity) {

    float aspectRatio = static_cast<float>(mClientWidth) / static_cast<float>(mClientHeight);

    if (entity == nullptr)
        m_pMainCamera = new Entity(this);
    else
        m_pMainCamera = entity;

    m_pMainCamera->InitObject("camera");
    m_pMainCamComponent = dynamic_cast<Camera*>(m_pMainCamera->GetComponentByName("camera"));
    m_pMainCamComponent->Init(aspectRatio);
};

VOID DirectX12Instance::CreateTextureManager() {
    m_pTextureManager = new TextureManager(this);
    m_pTextureManager->InitDescHeap();
};

VOID DirectX12Instance::InitializePostCommand()
{
    command_allocator->Reset();
    mCommandList->Reset(command_allocator, nullptr);

    InitTextures();

    mCommandList->Close();

    ID3D12CommandList* cmdsLists[] = { mCommandList };
    graphics_command_queue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    FlushCommandQueue();


}

VOID DirectX12Instance::InitTextures() {
    //Ici ajouter toutes les textures utilisées
    
    m_pTextureManager->AddTexture("bark", L"Content/Images/bark.dds");
    m_pTextureManager->AddTexture("victor", L"Content/Images/image.dds");
    m_pTextureManager->AddTexture("sky", L"Content/Images/sky.dds");
    
}


VOID DirectX12Instance::InitMesh() {
    m_ListMesh["cube"] = std::move(new Mesh());
    m_ListMesh.find("cube")->second->InitializeMesh(device, "cube");
    m_ListMesh["pyramid"] = std::move(new Mesh());
    m_ListMesh.find("pyramid")->second->InitializeMesh(device, "pyramid");
    m_ListMesh["pipe"] = std::move(new Mesh());
    m_ListMesh.find("pipe")->second->InitializeMesh(device, "pipe");
    /*m_ListMesh["sphere"] = std::move(new Mesh());
    m_ListMesh.find("sphere")->second->InitializeMesh(device, "sphere");*/
    m_ListMesh["skybox"] = std::move(new Mesh());
    m_ListMesh.find("skybox")->second->InitializeMesh(device, "skybox");


};

VOID DirectX12Instance::InitShader() {
    m_ListShader["default"] = std::move(new Shader());
    m_ListShader.find("default")->second->InitializeShader(device);
    m_ListShader["textured"] = std::move(new Shader());
    m_ListShader.find("textured")->second->InitializeShader(device, "textured");
};

#pragma endregion

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |                                   Rendering                                         |
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Render

VOID DirectX12Instance::LateUpdate()
{
    for (int i = 0; i < m_ListEntities.size(); i++)
    {
        if (m_ListEntities.at(i)->GetDestroyValue() == true)
        {
            Entity* DestroyedEntity = m_ListEntities.at(i);
            m_ListEntities.erase(m_ListEntities.begin() + i);
            delete DestroyedEntity;
        }
        else if (m_ListEntities[i]->GetComponentByName("particle-system") != nullptr)
        {
            for (int j = 0; j < dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.size(); j++)
            {
                if (dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.at(j)->GetDestroyValue() == true)
                {
                    Entity* DestroyedEntity = dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.at(j);
                    dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.erase(dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.begin() + j);
                    delete DestroyedEntity;
                }
            }
        }
    }
}

VOID DirectX12Instance::Update(float dt)
{
    for (int i = 0; i < m_ListEntities.size(); i++)
    {
        m_ListEntities.at(i)->UpdateEntity(dt);
    }
    RenderFrame();
    LateUpdate();
}

VOID DirectX12Instance::RenderFrame() 
{
    /*
    * |----------------------------------------------
    * |	INIT de la render frame: swap chain, PSO,    |
    * |  Resources barrier,  command list,           |
    * |  command allocator, viewport                 |
    * |----------------------------------------------
    */

    HRESULT deviceRemovedReason = device->GetDeviceRemovedReason();
    if (deviceRemovedReason != S_OK) {
        // Traitez le retrait du périphérique ici
        // Par exemple, vous pouvez journaliser la raison du retrait ou réinitialiser le périphérique
        // Vous pouvez également appeler une fonction de gestion de retrait de périphérique dédiée
        return;
    }

    UINT frame = m_CurrentBufferIndex;

    //Met la command list en mode "écoute"
    command_allocator->Reset();//Frame définit l'index du back buffer sur lequel on va dessiner
    mCommandList->Reset(command_allocator, nullptr);


    //Passage du 1er back buffer en mode render target

    //Set la viewport
    mCommandList->RSSetViewports(1, &viewport);
    mCommandList->RSSetScissorRects(1, &scissor);

    auto transitionToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    mCommandList->ResourceBarrier(1, &transitionToRenderTarget);

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    mCommandList->ResourceBarrier(1, &barrier);

    // Obtenir l'adresse virtuelle GPU après la transition
    //D3D12_GPU_VIRTUAL_ADDRESS gpuAddress = render_target_buffers[frame]->GetGPUVirtualAddress();

    // Configurer le registre de racine (root parameter) pour le tampon de constantes
    //UINT rootParameterIndex = 1; // Supposons que c'est l'index du registre de racine que vous avez configuré dans votre pipeline de rendu
    //command_list->SetGraphicsRootConstantBufferView(rootParameterIndex, gpuAddress);



    /*
    * |----------------------------------------------
    * |	        Début des instructions               |
    * |----------------------------------------------
    */

    SetBackground(0.6f, 0.6f, 0.6f, 1.0f);

    ID3D12DescriptorHeap* descriptorHeaps[] = { m_pTextureManager->GetSrvHeap() };
    mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

    DrawAll();

    /*
    * |----------------------------------------------
    * |	        Fermeture des instructions           |
    * |----------------------------------------------
    */

    //Passage du 1er back buffer en mode state present: on peut plus dessiner dessus
    auto transitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    mCommandList->ResourceBarrier(1, &transitionToPresent);

    auto DsvTransitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    mCommandList->ResourceBarrier(1, &DsvTransitionToPresent);

    //On close la commandList et on l'envoie dans la commandQueue
    mCommandList->Close();
    ID3D12CommandList* command_lists[] = { mCommandList };
    graphics_command_queue->ExecuteCommandLists(_countof(command_lists), command_lists);

    //Affiche le current Back Buffer
    swap_chain->Present(1, 0);
    m_CurrentBufferIndex = (m_CurrentBufferIndex + 1) % FRAMES;

    FlushCommandQueue();

}

VOID DirectX12Instance::Draw(Entity* entity) 
{
    MeshRenderer* mesh_renderer = dynamic_cast<MeshRenderer*>(entity->GetComponentByName("mesh_renderer"));

    if (mesh_renderer == nullptr)
        return; // Vérifie si le mesh renderer est valide

    ///////////////////////////////////////////

    //entity->Rotate(0.0f, 0.001f, 0.0f);
    entity->GetTransform()->UpdateMatrix();

    UpdateCam(entity);

    ///////////////////////////////////////////

    //??
    mCommandList->SetGraphicsRootSignature(mesh_renderer->GetShader()->GetRootSignature());
    mCommandList->SetPipelineState(mesh_renderer->GetShader()->GetPipelineState());


    UINT frame = m_CurrentBufferIndex;
    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    mCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    // Mappez et copiez la matrice identité dans le tampon de constantes sur le GPU

    mesh_renderer->UpdateConstantBuffer(m_worldViewProjMatrix);

    // Définissez la vue de tampon de constantes
    D3D12_GPU_VIRTUAL_ADDRESS gpuAddress = mesh_renderer->GetConstantBufferGPU()->GetGPUVirtualAddress();
    mCommandList->SetGraphicsRootConstantBufferView(mesh_renderer->GetShader()->GetRootParamSize(), gpuAddress);

    auto vertexbufftemp = mesh_renderer->GetMesh()->GetVertexBufferView();
    auto Indexbufftemp = mesh_renderer->GetMesh()->GetIndexBufferView();

    mCommandList->IASetVertexBuffers(0, 1, &vertexbufftemp);
    mCommandList->IASetIndexBuffer(&Indexbufftemp);



    // Draw the thing
    auto DsvHeap = mDsvHeap->GetCPUDescriptorHandleForHeapStart();
    mCommandList->OMSetRenderTargets(1, &current_render_target_descriptor, true, &DsvHeap);

    //??
    if(mesh_renderer->GetShader()->GetIsDescTable() == 1)
        mCommandList->SetGraphicsRootDescriptorTable(0, mesh_renderer->GetTexture()->m_DescriptorHandleGPU);

    mCommandList->DrawIndexedInstanced(*mesh_renderer->GetMesh()->GetIndexCount(), 1, 0, 0, 0);
};

VOID DirectX12Instance::DrawAll() {
    for (int i = 0; i < m_ListEntities.size(); i++) {
        Draw(m_ListEntities[i]);
        if (m_ListEntities[i]->GetComponentByName("particle-system") != nullptr)
        {
            for (int j = 0; j < dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.size(); j++)
            {
                Draw(dynamic_cast<ParticleSystem*>(m_ListEntities.at(i)->GetComponentByName("particle-system"))->m_Atoms.at(j));
            }
        }
    }
};

VOID DirectX12Instance::SetBackground(float r, float g, float b, float a) 
{
    UINT frame = m_CurrentBufferIndex;
    float clear_color[4] = { r, g, b, a };

    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    mCommandList->ClearRenderTargetView(current_render_target_descriptor, clear_color, 0, 0);
    mCommandList->ClearDepthStencilView(mDsvHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
};

VOID DirectX12Instance::UpdateCam(Entity* entity) 
{
    // Calcul de la matrice de projection (dans votre cas, cela semble déjà être fait correctement)
    XMFLOAT4X4 viewMatrix = m_pMainCamComponent->GetMatrixView();
    XMMATRIX view = XMLoadFloat4x4(&viewMatrix);

    // Calcul de la matrice de projection (dans votre cas, cela semble déjà être fait correctement)
    XMFLOAT4X4 monZob = m_pMainCamComponent->GetMatrixProj();
    XMMATRIX proj = XMLoadFloat4x4(&monZob);

    // Calcul de la matrice world (dans votre cas, cela semble déjà être fait correctement)
    XMMATRIX world = XMLoadFloat4x4(entity->GetTransformConvert());

    m_worldViewProjMatrix = world * view * proj;

};

#pragma endregion