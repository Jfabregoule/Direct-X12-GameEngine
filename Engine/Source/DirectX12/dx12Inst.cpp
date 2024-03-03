#include "Engine.h"
#include "dx12Inst.h"
#include "Engine/Entity.h"
#include "Engine/Mesh.h"
#include "Engine/MeshRenderer.h"

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
        // Traitez le retrait du p�riph�rique ici
        // Par exemple, vous pouvez journaliser la raison du retrait ou r�initialiser le p�riph�rique
        // Vous pouvez �galement appeler une fonction de gestion de retrait de p�riph�rique d�di�e
        return;
    }

    UINT frame = m_CurrentBufferIndex;

    //Met la command list en mode "�coute"
    command_allocators[frame]->Reset();//Frame d�finit l'index du back buffer sur lequel on va dessiners
    command_list.Reset();

    HRESULT hresult = device->CreateCommandList(0, graphics_command_queue_desc.Type, command_allocators[frame], 0, IID_PPV_ARGS(command_list.GetAddressOf()));
    CheckSucceeded(hresult);

    //Passage du 1er back buffer en mode render target

    //Set la viewport
    command_list->RSSetViewports(1, &viewport);
    command_list->RSSetScissorRects(1, &scissor);

    auto transitionToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    command_list->ResourceBarrier(1, &transitionToRenderTarget);

    // Obtenir l'adresse virtuelle GPU apr�s la transition
    //D3D12_GPU_VIRTUAL_ADDRESS gpuAddress = render_target_buffers[frame]->GetGPUVirtualAddress();

    // Configurer le registre de racine (root parameter) pour le tampon de constantes
    //UINT rootParameterIndex = 1; // Supposons que c'est l'index du registre de racine que vous avez configur� dans votre pipeline de rendu
    //command_list->SetGraphicsRootConstantBufferView(rootParameterIndex, gpuAddress);



    /*
    * |----------------------------------------------
    * |	        D�but des instructions               |
    * |----------------------------------------------
    */

    SetBackground(0.38f, 0.38f, 0.38f, 1.0f);

    DrawAll();

    /*
    * |----------------------------------------------
    * |	        Fermeture des instructions           |
    * |----------------------------------------------
    */

    //Passage du 1er back buffer en mode state present: on peut plus dessiner dessus
    auto transitionToPresent = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    command_list->ResourceBarrier(1, &transitionToPresent);

    //On close la commandList et on l'envoie dans la commandQueue
    command_list->Close();
    ID3D12CommandList* command_lists[] = { command_list.Get() };
    graphics_command_queue->ExecuteCommandLists(_countof(command_lists), command_lists);

    fence_value[frame]++;
    graphics_command_queue->Signal(fence[frame], fence_value[frame]);

    //Regarde si le cpu doit attendre avant d'envoyer les instructions au gpu
    if (fence[frame]->GetCompletedValue() < fence_value[frame]) {
        fence[frame]->SetEventOnCompletion(fence_value[frame], fence_event[frame]);
        WaitForSingleObject(fence_event[frame], INFINITE);
    }
    //Affiche le current Back Buffer
   swap_chain->Present(1, 0);
    m_CurrentBufferIndex = (m_CurrentBufferIndex + 1) % FRAMES;
}

VOID DirectX12Instance::Draw(Entity* entity) {

    MeshRenderer* mesh_renderer = dynamic_cast<MeshRenderer*>(entity->GetComponentByName("mesh_renderer"));

    if (mesh_renderer == nullptr)
        return; // V�rifie si le mesh renderer est valide
    // Set pipeline state and root signature
    //A FAIRE ICI, lorsque la classe shader existera on renseignera la PSO de l'objet dessin�
    //L'objet dessin� aura dans sa PSO les shaders adapt�s pour cet objet
    command_list->SetGraphicsRootSignature(mesh_renderer->GetShader()->GetRootSignature());
    command_list->SetPipelineState(mesh_renderer->GetShader()->GetPipelineState());


    UINT frame = m_CurrentBufferIndex;
    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Apply camera's view matrix
    ID3D12Resource *constantBufferGPU;
    DirectX::XMFLOAT4X4 worldViewProjMatrix; // Donn�es du tampon de constantes

    worldViewProjMatrix._41 = 0.0f;
    worldViewProjMatrix._42 = 0.0f;
    worldViewProjMatrix._43 = 10.0f; // Place l'objet � 10 unit�s en arri�re pour �tre en face du point (0, 0, 0)

    // Matrice identit� pour la rotation et l'�chelle
    worldViewProjMatrix._11 = 1.0f;
    worldViewProjMatrix._22 = 1.0f;
    worldViewProjMatrix._33 = 1.0f;
    worldViewProjMatrix._44 = 1.0f;

    // M�thode pour initialiser le tampon de constantes sur le GPU
    auto test = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto testo = CD3DX12_RESOURCE_DESC::Buffer(sizeof(worldViewProjMatrix));
    HRESULT hresult = device->CreateCommittedResource(
        &test,
        D3D12_HEAP_FLAG_NONE,
        &testo,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&constantBufferGPU));
        CheckSucceeded(hresult);

        // Mappez et copiez la matrice identit� dans le tampon de constantes sur le GPU
        UINT8* pConstantBufferData;
        CD3DX12_RANGE readRange(0, 0);
        hresult = constantBufferGPU->Map(0, &readRange, reinterpret_cast<void**>(&pConstantBufferData));
        CheckSucceeded(hresult);
        constantBufferGPU->Unmap(0, nullptr);

        // D�finissez la vue de tampon de constantes
        D3D12_GPU_VIRTUAL_ADDRESS gpuAddress = constantBufferGPU->GetGPUVirtualAddress();
        command_list->SetGraphicsRootConstantBufferView(0, gpuAddress);
    //command_list->SetGraphicsRootConstantBufferView(0, m_pMainCamera->GetComponentByName("Camera").GetViewMatrixGpuAddress(m_pMainCamera->GetComponentByName("Camera").viewMatrix));
    //command_list->SetGraphicsRootConstantBufferView(1, m_pMainCamera->GetComponentByName("Camera").camera.GetProjectionMatrixGpuAddress(m_pMainCamera->GetComponentByName("Camera").projectionMatrix));

    auto vertexbufftemp = mesh_renderer->GetMesh()->GetVertexBufferView();
    auto Indexbufftemp = mesh_renderer->GetMesh()->GetIndexBufferView();

    command_list->IASetVertexBuffers(0, 1, &vertexbufftemp);
    command_list->IASetIndexBuffer(&Indexbufftemp);



    // Draw the thing
    command_list->OMSetRenderTargets(1, &current_render_target_descriptor, 0, 0);
    command_list->DrawIndexedInstanced(*mesh_renderer->GetMesh()->GetIndexCount(), 1, 0, 0, 0);
};


VOID DirectX12Instance::DrawAll() {
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
};


#pragma endregion