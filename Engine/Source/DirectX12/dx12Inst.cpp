#include "Engine.h"
#include "dx12Inst.h"

class MeshRenderer;
class Entity;

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
    UINT frame = swap_chain->GetCurrentBackBufferIndex();

    //Met la command list en mode "écoute"
    command_allocators[frame]->Reset();
    command_list.Reset();

    HRESULT hresult = device->CreateCommandList(0, graphics_command_queue_desc.Type, command_allocators[frame], 0, IID_PPV_ARGS(command_list.GetAddressOf()));
    CheckSucceeded(hresult);

    //Couleur du fond
    
    float clear_color[4] = { 1.0f, 0.18f, 0.18f, 1.0f };

    auto transitionToRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(render_target_buffers[frame], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    command_list->ResourceBarrier(1, &transitionToRenderTarget);

    command_list->RSSetViewports(1, &viewport);
    //command_list->RSSetScissorRects(1, &scissor);
    command_list->ClearRenderTargetView(current_render_target_descriptor, clear_color, 0, 0);

    // Set pipeline state and root signature
    command_list->SetGraphicsRootSignature(root_signature);
    command_list->SetPipelineState(pipeline_state);

    //         DRAW         //
    DrawAll();

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

VOID DirectX12Instance::Draw(Entity* entity) {

    MeshRenderer* mesh_ref = entity.GetComponentByName("mesh_ref");

    // Apply camera's view matrix
    command_list->SetGraphicsRootConstantBufferView(0, m_pMainCamera.GetComponnentByName(L"Camera").GetViewMatrixGpuAddress(m_pMainCamera.GetComponnentByName(L"Camera").viewMatrix));
    command_list->SetGraphicsRootConstantBufferView(1, m_pMainCamera.GetComponnentByName(L"Camera").camera.GetProjectionMatrixGpuAddress(m_pMainCamera.GetComponnentByName(L"Camera").projectionMatrix));

    command_list->IASetVertexBuffers(0, 1, &(mesh_ref->m_vertexBufferView));
    command_list->IASetIndexBuffer(&(mesh_ref->m_indexBufferView));

    command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw the triangle built by BuildBoxGeometry
    command_list->OMSetRenderTargets(1, &current_render_target_descriptor, 0, 0);
    command_list->DrawInstanced(mesh_ref.m_numIndices, 1, 0, 0);
};

VOID DirectX12Instance::DrawAll() {
    for (int i = 0; i < m_ListEntities.size(); i++) {
        Draw(m_ListEntities[i]);
    }
};

VOID DirectX12Instance::SetBackground(float r,float g,float b,float a) {

    UINT frame = swap_chain->GetCurrentBackBufferIndex();
    float clear_color[4] = { r, g, b, a };

    D3D12_CPU_DESCRIPTOR_HANDLE current_render_target_descriptor = render_target_descriptors[frame];
    command_list->ClearRenderTargetView(current_render_target_descriptor, clear_color, 0, 0);
};


#pragma endregion

