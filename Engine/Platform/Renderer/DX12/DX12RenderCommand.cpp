#include"Platform/Renderer/DX12/DX12RenderCommand.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12RenderCommandQueue.h"
#include"Platform/Renderer/DX12/DX12Swapchain.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12RenderCommand, RenderCommand::RunTimeType)

    RenderCommand* RenderCommand::Create(ERenderCommandType type) {
        // TODO: Allocate by memory allocator
        return new DX12RenderCommand(Application::Get().GetRenderer()->GetContext(), type);
    }

    DX12RenderCommand::DX12RenderCommand(RendererContext* rendererContext, ERenderCommandType type) 
        : RenderCommand(type), mCommandAllocator(), mGraphicCommandList() 
    {
        mAddress = this;
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
        mRenderCommandQueue = mRendererContext->mRenderCommandQueue;
        // TODO: Get from command list pool
        DX12CheckException(mRendererContext->mDevice->CreateCommandAllocator(
            EngineToDX12RenderCommand(mType), IID_PPV_ARGS(&mCommandAllocator))
        );
        DX12CheckException(mRendererContext->mDevice->CreateCommandList(
            0, EngineToDX12RenderCommand(mType), mCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&mGraphicCommandList))
        );
    }

    DX12RenderCommand::~DX12RenderCommand() {

    }

    void DX12RenderCommand::BeginRecordImpl() {
        // Reset();
    }

    void DX12RenderCommand::EndRecordImpl() {
        mGraphicCommandList->Close();
        if (mRendererContext->mApplication->GetIsCatchUpPhase()) {
            Reset();
        }
        else {
            mRenderCommandQueue->Submit(reinterpret_cast<RenderCommand**>(&mAddress), 1);
        }
    }

    void DX12RenderCommand::ResetImpl() {
        mCommandAllocator->Reset();
        mGraphicCommandList->Reset(mCommandAllocator.Get(), nullptr);
    }

    void DX12RenderCommand::ClearColorImpl(float r, float g, float b, float a) {
        float color[] = {r, g, b, a};
        mGraphicCommandList->ClearRenderTargetView(mRendererContext->mCurrentRTVDescHandle, color, 0, nullptr);
    }

    void DX12RenderCommand::SetRenderTargetImpl() {
        UINT currentBackBufferIdx = mRendererContext->mSwapchain->GetNative()->GetCurrentBackBufferIndex();
        mRendererContext->mCurrentRTVDescHandle = mRendererContext->mRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
        mRendererContext->mCurrentRTVDescHandle.ptr += currentBackBufferIdx * mRendererContext->mRTVDescriptorHeapSize;
        mGraphicCommandList->OMSetRenderTargets(1, &mRendererContext->mCurrentRTVDescHandle, true, nullptr);
    }

    void DX12RenderCommand::SetBackBufferRenderImpl() {
        UINT currentBackBufferIdx = mRendererContext->mSwapchain->GetNative()->GetCurrentBackBufferIndex();
        D3D12_RESOURCE_BARRIER renderTargetBarrier = {};
        renderTargetBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        renderTargetBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        renderTargetBarrier.Transition.pResource = mRendererContext->mBackBuffers[currentBackBufferIdx].Get();
        renderTargetBarrier.Transition.Subresource = 0; 
        renderTargetBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; 
        renderTargetBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        mGraphicCommandList->ResourceBarrier(1, &renderTargetBarrier);
    }

    void DX12RenderCommand::SetBackBufferPresentImpl() {
        UINT currentBackBufferIdx = mRendererContext->mSwapchain->GetNative()->GetCurrentBackBufferIndex();
        D3D12_RESOURCE_BARRIER renderTargetBarrier = {};
        renderTargetBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        renderTargetBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        renderTargetBarrier.Transition.pResource = mRendererContext->mBackBuffers[currentBackBufferIdx].Get();
        renderTargetBarrier.Transition.Subresource = 0; 
        renderTargetBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; 
        renderTargetBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        mGraphicCommandList->ResourceBarrier(1, &renderTargetBarrier);
    }
}