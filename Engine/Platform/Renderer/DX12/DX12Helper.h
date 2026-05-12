#pragma once

#include"Core/pch.h"
#include"Platform/Renderer/DX12/DX12Exception.h"
#include"Core/Renderer/CommonDefine.h"
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<windows.h>

inline std::wstring AnsiToWString(const std::string& str)
{
    WCHAR buffer[512];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
    return std::wstring(buffer);
}

#define DX12CheckException(f) \
{ \
    HRESULT result = (f); \
    std::wstring wfn = AnsiToWString(__FILE__); \
    if (FAILED(result)) { \
        throw VIEngine::DX12Exception(result, L#f, wfn, __LINE__); \
    } \
}

namespace VIEngine {
    template<typename T> using WRLComPtr = Microsoft::WRL::ComPtr<T>;

    D3D12_HEAP_TYPE EngineToDX12HeapType(EBufferUsage usage);
    D3D12_COMMAND_LIST_TYPE EngineToDX12RenderCommand(ERenderCommandType renderCommandType);
    D3D12_COMMAND_QUEUE_PRIORITY EngineToDX12QueuePriority(EQueuePriority priority);
    DXGI_FORMAT EngineToDX12Format(EFormat format);
    uint64_t EngineToDX12Usage(EUsage format);
    DXGI_SCALING EngineToDX12ScaleMode(EScaleMode mode);
    DXGI_SWAP_EFFECT EngineToDX12SwapMode(ESwapMode mode);
    DXGI_ALPHA_MODE EngineToDX12AlphaMode(EAlphaMode mode);
    UINT EngineToDX12SwapchainFlags(ESwapchainFlag flags);
    bool HasSwapchainFlag(ESwapchainFlag flags, ESwapchainFlag target);
    D3D12_INPUT_CLASSIFICATION EngineToDX12InputType(EInputType type);
}