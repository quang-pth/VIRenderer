#include"Platform/Renderer/DX12/DX12RenderCommand.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12RenderCommandQueue.h"
#include"Platform/Renderer/DX12/DX12Swapchain.h"
#include"Platform/Renderer/DX12/DX12UniformBufferLayout.h"
#include"Platform/Renderer/DX12/DX12UniformBuffer.h"
#include"Platform/Renderer/DX12/DX12RenderPipeline.h"
#include"Platform/Renderer/DX12/DX12RenderPipelineLayout.h"
#include"Platform/Renderer/DX12/DX12VertexBufferAccessor.h"
#include"Platform/Renderer/DX12/DX12IndexBufferAccessor.h"
#include"Platform/Renderer/DX12/DX12InputAssembler.h"
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

    void DX12RenderCommand::SubmitImpl() {
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

    void DX12RenderCommand::ClearColorImpl(float r, float g, float b, float a) {
        float color[] = {r, g, b, a};
        mGraphicCommandList->ClearRenderTargetView(mRendererContext->mCurrentRTVDescHandle, color, 0, nullptr);
    }

    void DX12RenderCommand::SetRenderPipelineImpl(RenderPipeline* renderPipeline) {
        VI_ASSERT(renderPipeline != nullptr && "renderPipeline is nullptr");
        mActiveRenderPipeline = static_cast<DX12RenderPipeline*>(renderPipeline);
        mGraphicCommandList->SetPipelineState(mActiveRenderPipeline->GetPipelineState());
        DX12RenderPipelineLayout* pipelineLayout = static_cast<DX12RenderPipelineLayout*>(mActiveRenderPipeline->GetPipelineLayout());
        mGraphicCommandList->SetGraphicsRootSignature(pipelineLayout->GetRootSignature());
    }

    void DX12RenderCommand::SetViewPortImpl(float width, float height, float topLeftX, float topLeftY, float minDepth, float maxDepth) {
        D3D12_VIEWPORT viewport = {};
        viewport.Width = width; 
        viewport.Height = height;
        viewport.TopLeftX = topLeftX;
        viewport.TopLeftY = topLeftY;
        viewport.MinDepth = minDepth;
        viewport.MaxDepth = maxDepth;
        mGraphicCommandList->RSSetViewports(1, &viewport);
    }

    void DX12RenderCommand::SetScissorImpl(float top, float left, float right, float bottom) {
        D3D12_RECT scissorRect;
        scissorRect.top = top;
        scissorRect.left = left;
        scissorRect.right = right;
        scissorRect.bottom = bottom;
        mGraphicCommandList->RSSetScissorRects(1, &scissorRect);
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

    void DX12RenderCommand::SetConstantsBufferImpl(UniformBuffer* buffer) {
        VI_ASSERT(mActiveRenderPipeline != nullptr && "mActiveRenderPipeline is null");
        const DX12RenderPipelineLayout* pipelineLayout = static_cast<const DX12RenderPipelineLayout*>(mActiveRenderPipeline->GetPipelineLayout());
        VI_ASSERT(pipelineLayout != nullptr && "pipelineLayout is null");
        const DX12UniformBufferLayout* bufferLayout = static_cast<const DX12UniformBufferLayout*>(buffer->GetLayout());
        uint32_t rootIndex = pipelineLayout->GetLayoutIndex(bufferLayout);
        DX12UniformBuffer* dx12UniformBuffer = static_cast<DX12UniformBuffer*>(buffer);
        mGraphicCommandList->SetGraphicsRootConstantBufferView(rootIndex, dx12UniformBuffer->GetGPUConstantBuffer()->GetGPUVirtualAddress());
    }

    void DX12RenderCommand::DrawImpl() {
        // TODO: 設定可能化
        mGraphicCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        DX12InputAssembler* inputAssembler = static_cast<DX12InputAssembler*>(mActiveRenderPipeline->GetInputAssembler());
        const std::vector<DX12VertexBufferAccessor*>& verterBufferAccessors = inputAssembler->GetVertexBufferAccessors();
        for (DX12VertexBufferAccessor* vertexBufferAccessor : verterBufferAccessors) {
            mGraphicCommandList->IASetVertexBuffers(
                vertexBufferAccessor->GetStreamSlot(), 
                vertexBufferAccessor->GetViews().size(), 
                vertexBufferAccessor->GetViews().data()
            );
        }
        DX12IndexBufferAccessor* indexBufferAccessor = static_cast<DX12IndexBufferAccessor*>(inputAssembler->GetIndexBufferAccessor());
		mGraphicCommandList->IASetIndexBuffer(indexBufferAccessor->GetView());
		mGraphicCommandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
    }
}