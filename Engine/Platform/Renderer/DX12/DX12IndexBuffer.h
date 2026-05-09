#pragma once

#include"Core/Renderer/GPUIndexBuffer.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"

namespace VIEngine {
    class VI_API DX12IndexBuffer : public GPUIndexBuffer {
        DECLARE_RTTI
    public:
        DX12IndexBuffer() = default;
        DX12IndexBuffer(RendererContext* rendererContext, IndexBuffer* cpuBuffer, EBufferUsage usage = EBufferUsage::STATIC);
        ~DX12IndexBuffer() = default;
        VI_FORCE_INLINE const D3D12_INDEX_BUFFER_VIEW* GetBufferView() const { return &mBufferView; } 
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12Resource> mResource;
        D3D12_INDEX_BUFFER_VIEW mBufferView;
    };
}