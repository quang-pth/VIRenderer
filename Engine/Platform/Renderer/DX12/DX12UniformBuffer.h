#pragma once

#include"Core/Renderer/UniformBuffer.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;

    class VI_API DX12UniformBuffer final : public UniformBuffer {
        DECLARE_RTTI
    public:
        DX12UniformBuffer(RendererContext* rendererContext, const UniformBufferAttribute& attribute);
        ~DX12UniformBuffer();
        virtual void Upload() override;
        VI_FORCE_INLINE ID3D12Resource* GetGPUConstantBuffer() { return mGPUConstantBuffer.Get(); }
        VI_FORCE_INLINE ID3D12Resource* GetGPUShaderResourceBuffer() { return mGPUShaderResourceBuffer.Get(); }
        VI_FORCE_INLINE ID3D12Resource* GetGPUUnorderedAccessBuffer() { return mGPUUnorderedAccessBuffer.Get(); }
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12Resource> mGPUConstantBuffer;
        WRLComPtr<ID3D12Resource> mGPUShaderResourceBuffer;
        WRLComPtr<ID3D12Resource> mGPUUnorderedAccessBuffer;
    };
}