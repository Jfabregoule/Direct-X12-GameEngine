#include "Engine.h"
#include "dx12Inst.h"

DirectX12Instance* DirectX12Instance::inst;

DirectX12Instance::DirectX12Instance(HWND handle)
{

	inst = this;

	m_handle = handle;
}

DirectX12Instance::~DirectX12Instance()
{
}
