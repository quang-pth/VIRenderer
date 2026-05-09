#pragma once

#include"Core/Renderer/GPUVertexBuffer.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"

namespace VIEngine {
    class VI_API DX12VertexBuffer : public GPUVertexBuffer {
        DECLARE_RTTI
    public:
        DX12VertexBuffer() = default;
        DX12VertexBuffer(RendererContext* rendererContext, VertexBuffer* cpuBuffer, EBufferUsage usage = EBufferUsage::STATIC);
        ~DX12VertexBuffer() = default;
        VI_FORCE_INLINE const D3D12_VERTEX_BUFFER_VIEW* GetBufferView() const { return &mBufferView; } 
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12Resource> mResource;
        D3D12_VERTEX_BUFFER_VIEW mBufferView;
    };
}