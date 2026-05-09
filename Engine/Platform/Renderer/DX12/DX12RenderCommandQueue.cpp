#include"Platform/Renderer/DX12/DX12RenderCommandQueue.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12RenderCommand.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12RenderCommandQueue, RenderCommandQueue::RunTimeType)

    RenderCommandQueue* RenderCommandQueue::Create(RendererContext* rendererContext, const CommandQueueAttribute& attribute) {
        // TODO: Allocate by memory allocator
        return new DX12RenderCommandQueue(rendererContext, attribute);
    }

    DX12RenderCommandQueue::DX12RenderCommandQueue(RendererContext* rendererContext, const CommandQueueAttribute& attribute)
        : RenderCommandQueue(attribute), mCommandQueue(), mPendingCommands(), mFenceValue(0)
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);

        D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
        cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        cmdQueueDesc.NodeMask = 0;
        cmdQueueDesc.Priority = EngineToDX12QueuePriority(mAttribute.Priority);
        cmdQueueDesc.Type = EngineToDX12RenderCommand(mAttribute.Type);
        DX12CheckException(mRendererContext->mDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&mCommandQueue)));
        DX12CheckException(mRendererContext->mDevice->CreateFence(mFenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));
    }

    DX12RenderCommandQueue::~DX12RenderCommandQueue() {

    }

    void DX12RenderCommandQueue::SubmitImpl(RenderCommand** renderCommand, uint64_t count) {
        for (uint64_t i = 0; i < count; ++i) {
            DX12RenderCommand* command = static_cast<DX12RenderCommand*>(renderCommand[i]); 
            mPendingCommands.push_back(command);
        }
    }

    void DX12RenderCommandQueue::ExecuteImpl() {
        std::vector<ID3D12CommandList*> commandList;
        commandList.reserve(mPendingCommands.size());
        for (auto& pendingCommand : mPendingCommands) {
            commandList.push_back(pendingCommand->GetGraphicCommandList());
        }
        mCommandQueue->ExecuteCommandLists(commandList.size(), commandList.data());
        mCommandQueue->Signal(mFence.Get(), ++mFenceValue);
        if (mFence->GetCompletedValue() != mFenceValue) {
			HANDLE completeEvent = CreateEvent(nullptr, false, false, nullptr);
			mFence->SetEventOnCompletion(mFenceValue, completeEvent);
			WaitForSingleObject(completeEvent, INFINITE);
			CloseHandle(completeEvent);
		}
        for (auto& pendingCommand : mPendingCommands) {
            pendingCommand->Reset();
        }
        mPendingCommands.clear();
    }
}