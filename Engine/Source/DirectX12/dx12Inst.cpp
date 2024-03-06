#include "Engine.h"
#include "dx12Inst.h"
#include "Engine/Entity.h"
#include "Engine/Mesh.h"
#include "Engine/MeshRenderer.h"
#include "Engine/InputManager.h"

DirectX12Instance* DirectX12Instance::inst;

DirectX12Instance::DirectX12Instance(HWND handle)
{

    inst = this;

    m_handle = handle;

}

DirectX12Instance::~DirectX12Instance()
{
}

/*
* |-------------------------------------------------
* |						Render						|
* |-------------------------------------------------
*/

#pragma region Render

VOID DirectX12Instance::RenderFrame() {

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
    command_allocators[frame]->Reset();//Frame définit l'index du back buffer sur lequel on va dessiners
    command_list.Reset();

    HRESULT hresult = device->CreateCommandList(0, graphics_command_queue_desc.Type, command_allocators[frame], 0, IID_PPV_ARGS(command_list.GetAddressOf()));
    CheckSucceeded(hresult);

    //Passage du 1er back buffer en mode render target

    //Set la viewport
    command_list->RSSetViewports(1, &viewport);
    command_list->RSSetScissorRects(1, &scissor);

    auto transitionToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    command_list->ResourceBarrier(1, &transitionToRenderTarget);

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    command_list->ResourceBarrier(1, &barrier);

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

    DrawAll();

    /*
    * |----------------------------------------------
    * |	        Fermeture des instructions           |
    * |----------------------------------------------
    */

    //Passage du 1er back buffer en mode state present: on peut plus dessiner dessus
    auto transitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    command_list->ResourceBarrier(1, &transitionToPresent);

    auto DsvTransitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(mDepthStencilBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    command_list->ResourceBarrier(1, &DsvTransitionToPresent);

    //On close la commandList et on l'envoie dans la commandQueue
    command_list->Close();
    ID3D12CommandList* command_lists[] = { command_list.Get() };
    graphics_command_queue->ExecuteCommandLists(_countof(command_lists), command_lists);

    //Affiche le current Back Buffer
    swap_chain->Present(1, 0);
    m_CurrentBufferIndex = (m_CurrentBufferIndex + 1) % FRAMES;

    fence_value[frame]++;
    graphics_command_queue->Signal(fence[frame], fence_value[frame]);

    //Regarde si le cpu doit attendre avant d'envoyer les instructions au gpu
    if (fence[frame]->GetCompletedValue() < fence_value[frame]) {
        fence[frame]->SetEventOnCompletion(fence_value[frame], fence_event[frame]);
        WaitForSingleObject(fence_event[frame], INFINITE);
    }

}

VOID DirectX12Instance::Draw(Entity* entity) {

    MeshRenderer* mesh_renderer = dynamic_cast<MeshRenderer*>(entity->GetComponentByName("mesh_renderer"));

    if (mesh_renderer == nullptr)
        return; // Vérifie si le mesh renderer est valide

    ///////////////////////////////////////////

    entity->GetTransform()->UpdateMatrix();

    UpdateCam(entity);

    ///////////////////////////////////////////


    command_list->SetGraphicsRootSignature(mesh_renderer->GetShader()->GetRootSignature());
    command_list->SetPipelineState(mesh_renderer->GetShader()->GetPipelineState());


    UINT frame = m_CurrentBufferIndex;
    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    // Mappez et copiez la matrice identité dans le tampon de constantes sur le GPU
    
    mesh_renderer->UpdateConstantBuffer(m_worldViewProjMatrix);

    // Définissez la vue de tampon de constantes
    D3D12_GPU_VIRTUAL_ADDRESS gpuAddress = mesh_renderer->GetConstantBufferGPU()->GetGPUVirtualAddress();
    command_list->SetGraphicsRootConstantBufferView(0, gpuAddress);
    
    auto vertexbufftemp = mesh_renderer->GetMesh()->GetVertexBufferView();
    auto Indexbufftemp = mesh_renderer->GetMesh()->GetIndexBufferView();

    command_list->IASetVertexBuffers(0, 1, &vertexbufftemp);
    command_list->IASetIndexBuffer(&Indexbufftemp);



    // Draw the thing
    auto DsvHeap = mDsvHeap->GetCPUDescriptorHandleForHeapStart();
    command_list->OMSetRenderTargets(1, &current_render_target_descriptor, true, &DsvHeap);

    command_list->DrawIndexedInstanced(*mesh_renderer->GetMesh()->GetIndexCount(), 1, 0, 0, 0);
};


VOID DirectX12Instance::DrawAll() {
    m_pMainCamera->Translate(0.05f, 0.05f, 0.05f);
    for (int i = 0; i < m_ListEntities.size(); i++) {
        //OutputDebugString(L"asrstsg");
        Draw(m_ListEntities[i]);
    }
};

VOID DirectX12Instance::SetBackground(float r, float g, float b, float a) {

    UINT frame = m_CurrentBufferIndex;
    float clear_color[4] = { r, g, b, a };

    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    command_list->ClearRenderTargetView(current_render_target_descriptor, clear_color, 0, 0);
    command_list->ClearDepthStencilView(mDsvHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
};


VOID DirectX12Instance::UpdateCam(Entity* entity) {

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