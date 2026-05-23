#pragma once

#include"Core/Renderer/GPUBuffer.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"

namespace VIEngine {
    class VI_API DX12Buffer final : public GPUBuffer {
        DECLARE_RTTI
    public:
        DX12Buffer() = default;
        DX12Buffer(RendererContext* rendererContext, Buffer* cpuBuffer, uint64_t count, uint64_t offset, EBufferUsage usage = EBufferUsage::STATIC);
        ~DX12Buffer() = default;
        VI_FORCE_INLINE ID3D12Resource* GetResource() const { return mResource.Get(); }
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12Resource> mResource;
    };
}