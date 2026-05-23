#pragma once

#include"Core/Renderer/RenderPipeline.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;

    class VI_API DX12RenderPipeline : public RenderPipeline {
        DECLARE_RTTI
    public:
        DX12RenderPipeline() = default;
        DX12RenderPipeline(RendererContext* rendererContext, const RenderPipelineAttribute& attribute);
        ~DX12RenderPipeline();
        VI_FORCE_INLINE ID3D12PipelineState* GetPipelineState() const { return mPipelineState.Get(); } 
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12PipelineState> mPipelineState;
    };
}