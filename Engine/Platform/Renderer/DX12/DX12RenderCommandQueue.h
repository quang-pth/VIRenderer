#pragma once

#include"Core/Renderer/RenderCommandQueue.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;
    class DX12RenderCommand;
    class Application;

    class VI_API DX12RenderCommandQueue : public RenderCommandQueue {
        DECLARE_RTTI
    public:
        DX12RenderCommandQueue(RendererContext* rendererContext, const CommandQueueAttribute& attribute);
        ~DX12RenderCommandQueue();
        VI_FORCE_INLINE ID3D12CommandQueue* GetNative() { return mCommandQueue.Get(); }
    protected:
        virtual void SubmitImpl(RenderCommand** renderCommand, uint64_t count) override;
        virtual void ExecuteImpl() override;
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12CommandQueue> mCommandQueue;
        std::vector<DX12RenderCommand*> mPendingCommands;
        WRLComPtr<ID3D12Fence> mFence;
        UINT64 mFenceValue;
    };
}