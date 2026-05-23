#pragma once

#include"Core/Renderer/RenderCommand.h"
#include"Platform/Renderer/DX12/DX12Helper.h"
#include<d3d12.h>

namespace VIEngine {
    class DX12RendererContext;
    class DX12RenderCommandQueue;
    class DX12RenderPipeline;

    class VI_API DX12RenderCommand final : public RenderCommand {
        DECLARE_RTTI
    public:
        DX12RenderCommand(RendererContext* rendererContext, ERenderCommandType type);
        ~DX12RenderCommand();
        ID3D12GraphicsCommandList* GetGraphicCommandList() const { return mGraphicCommandList.Get(); }
    protected:
        virtual void SubmitImpl() override;
        virtual void ResetImpl() override;
        virtual void SetRenderTargetImpl() override;
        virtual void SetBackBufferRenderImpl() override;
        virtual void ClearColorImpl(float r, float g, float b, float a) override;
        virtual void SetRenderPipelineImpl(RenderPipeline* renderPipeline) override;
        virtual void SetViewPortImpl(float width, float height, float topLeftX, float topLeftY, float minDepth, float maxDepth) override;
        virtual void SetScissorImpl(float top, float left, float right, float bottom) override;
        virtual void SetBackBufferPresentImpl() override;
        virtual void SetConstantsBufferImpl(UniformBuffer* buffer) override;
        virtual void DrawImpl() override;
    private:
        DX12RendererContext* mRendererContext;
        DX12RenderCommandQueue* mRenderCommandQueue;
        DX12RenderPipeline* mActiveRenderPipeline;
        WRLComPtr<ID3D12CommandAllocator> mCommandAllocator;
        WRLComPtr<ID3D12GraphicsCommandList> mGraphicCommandList;
        union {
            void* mAddress;
            const void* mConstAddress;
        };
    };
}