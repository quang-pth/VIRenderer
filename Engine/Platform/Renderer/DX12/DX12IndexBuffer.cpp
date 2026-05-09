#include"Platform/Renderer/DX12/DX12IndexBuffer.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    DX12IndexBuffer::DX12IndexBuffer(RendererContext* rendererContext, IndexBuffer* cpuBuffer, EBufferUsage usage) 
        : GPUIndexBuffer(cpuBuffer, usage), mResource(), mBufferView()
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);

        D3D12_HEAP_PROPERTIES heapProperties = {};
        D3D12_HEAP_TYPE heapType = EngineToDX12HeapType(mUsage);
        heapProperties.Type = heapType;
        heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        heapProperties.CreationNodeMask = 1;
        heapProperties.VisibleNodeMask = 1;

        D3D12_RESOURCE_DESC indexBufferDesc = {};
        indexBufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        indexBufferDesc.Alignment = 0;
        indexBufferDesc.Width = mCPUBuffer->GetSize();
        indexBufferDesc.Height = 1;
        indexBufferDesc.DepthOrArraySize = 1;
        indexBufferDesc.MipLevels = 1;
        indexBufferDesc.Format = DXGI_FORMAT_UNKNOWN;
        indexBufferDesc.SampleDesc.Count = 1;
        indexBufferDesc.SampleDesc.Quality = 0;
        indexBufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        indexBufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        ID3D12Device* device = mRendererContext->GetDevice();
        device->CreateCommittedResource(
            &heapProperties,
            D3D12_HEAP_FLAG_NONE,
            &indexBufferDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&mResource)
        );

        unsigned short* resourceAddress = nullptr;
        mResource->Map(0, nullptr, (void**)&resourceAddress);
        memcpy(resourceAddress, mCPUBuffer->GetData(), mCPUBuffer->GetSize());
        mResource->Unmap(0, nullptr);

        mBufferView.BufferLocation = mResource->GetGPUVirtualAddress();
        mBufferView.Format = DXGI_FORMAT_R16_UINT;
        mBufferView.SizeInBytes = mCPUBuffer->GetSize();
    }
}