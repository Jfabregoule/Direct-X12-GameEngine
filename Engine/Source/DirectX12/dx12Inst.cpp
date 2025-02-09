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

    // Param�tres de la projection perspective
    float aspectRatio = static_cast<float>(mClientWidth) / static_cast<float>(mClientHeight);
    float fovAngleY = DirectX::XMConvertToRadians(45.0f);
    float nearZ = 0.1f;
    float farZ = 1000.0f;

    // Cr�ation de la matrice de projection perspective
    XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&mProj, projMatrix);
    
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

    SetBackground(0.6f, 0.6f, 0.6f, 0.0f);

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
        return; // V�rifie si le mesh renderer est valide

    ///////////////////////////////////////////

    //entity->Translate(0.0f,0.01f,0.0f);
    entity->Rotate(0.0f,0.005f,0.0f);
    entity->GetTransform()->UpdateMatrix();
    
    float dx = 0.0f;
    float dy = 0.0f;

    mTheta += dx;
    mPhi += dy;

    // Restrict the angle mPhi.
    mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);

    float x = mRadius * sinf(mPhi) * cosf(mTheta);
    float z = mRadius * sinf(mPhi) * sinf(mTheta);
    float y = mRadius * cosf(mPhi);
     
    XMVECTOR pos = XMVectorSet( x - 1.0f, y - 1.0f, z - 1.0f, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&mView, view);

    XMMATRIX world = XMLoadFloat4x4(entity->GetTransformConvert());
    XMMATRIX proj = XMLoadFloat4x4(&mProj);
    m_worldViewProjMatrix = world * view * proj;
     
    ///////////////////////////////////////////

    
    command_list->SetGraphicsRootSignature(mesh_renderer->GetShader()->GetRootSignature());
    command_list->SetPipelineState(mesh_renderer->GetShader()->GetPipelineState());


    UINT frame = m_CurrentBufferIndex;
    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Apply camera's view matrix
    ID3D12Resource *constantBufferGPU;
    //DirectX::XMFLOAT4X4 temp = MathHelper::Identity4x4();
    //DirectX::XMStoreFloat4x4(&worldViewProjMatrix , temp); // Donn�es du tampon de constantes

    // M�thode pour initialiser le tampon de constantes sur le GPU
    auto test = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto testo = CD3DX12_RESOURCE_DESC::Buffer(sizeof(m_worldViewProjMatrix));
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
        memcpy(pConstantBufferData, &m_worldViewProjMatrix, sizeof(m_worldViewProjMatrix));
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