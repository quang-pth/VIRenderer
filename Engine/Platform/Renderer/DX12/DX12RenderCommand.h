#pragma once

#include"Core/Renderer/RenderCommand.h"
#include"Platform/Renderer/DX12/DX12Helper.h"
#include<d3d12.h>

namespace VIEngine {
    class DX12RendererContext;
    class DX12RenderCommandQueue;

    class VI_API DX12RenderCommand : public RenderCommand {
        DECLARE_RTTI
    public:
        DX12RenderCommand(RendererContext* rendererContext, ERenderCommandType type);
        ~DX12RenderCommand();
        ID3D12GraphicsCommandList* GetGraphicCommandList() const { return mGraphicCommandList.Get(); }
    protected:
        virtual void BeginRecordImpl() override;
        virtual void EndRecordImpl() override;
        virtual void ResetImpl() override;
        virtual void ClearColorImpl(float r, float g, float b, float a) override;
        virtual void SetRenderTargetImpl() override;
        virtual void SetBackBufferRenderImpl() override;
        virtual void SetBackBufferPresentImpl() override;
    private:
        DX12RendererContext* mRendererContext;
        DX12RenderCommandQueue* mRenderCommandQueue;
        WRLComPtr<ID3D12CommandAllocator> mCommandAllocator;
        WRLComPtr<ID3D12GraphicsCommandList> mGraphicCommandList;
        union {
            void* mAddress;
            const void* mConstAddress;
        };
    };
}