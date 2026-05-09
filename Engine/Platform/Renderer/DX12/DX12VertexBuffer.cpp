#include"Platform/Renderer/DX12/DX12VertexBuffer.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    DX12VertexBuffer::DX12VertexBuffer(RendererContext* rendererContext, VertexBuffer* cpuBuffer, EBufferUsage usage) 
        : GPUVertexBuffer(cpuBuffer, usage), mResource(), mBufferView() 
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);

        D3D12_HEAP_PROPERTIES heapProperties = {};
        D3D12_HEAP_TYPE heapType = EngineToDX12HeapType(mUsage);
        heapProperties.Type = heapType;
        heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        heapProperties.CreationNodeMask = 1;
        heapProperties.VisibleNodeMask = 1;

        D3D12_RESOURCE_DESC vertexBufferDesc = {};
        vertexBufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        vertexBufferDesc.Alignment = 0;
        vertexBufferDesc.Width = mCPUBuffer->GetSize();
        vertexBufferDesc.Height = 1;
        vertexBufferDesc.DepthOrArraySize = 1;
        vertexBufferDesc.MipLevels = 1;
        vertexBufferDesc.Format = DXGI_FORMAT_UNKNOWN;
        vertexBufferDesc.SampleDesc.Count = 1;
        vertexBufferDesc.SampleDesc.Quality = 0;
        vertexBufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        vertexBufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        ID3D12Device* device = mRendererContext->GetDevice();
        device->CreateCommittedResource(
            &heapProperties,
            D3D12_HEAP_FLAG_NONE,
            &vertexBufferDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&mResource)
        );

        unsigned short* resourceAddress = nullptr;
        mResource->Map(0, nullptr, (void**)&resourceAddress);
        memcpy(resourceAddress, mCPUBuffer->GetData(), mCPUBuffer->GetSize());
        mResource->Unmap(0, nullptr);

        mBufferView.BufferLocation = mResource->GetGPUVirtualAddress();
        mBufferView.SizeInBytes = mCPUBuffer->GetSize();
        mBufferView.StrideInBytes = mCPUBuffer->GetLayout().GetSize();
    }
}