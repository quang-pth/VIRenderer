#include"Platform/Renderer/DX12/DX12UniformBuffer.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Core/Application.h"
#include"Core/Memory/CommonDefine.h"

namespace VIEngine {
    DEFINE_RTTI(DX12UniformBuffer, UniformBuffer::RunTimeType)

    UniformBuffer* UniformBuffer::Create(const UniformBufferAttribute& attribute) {
        return new DX12UniformBuffer(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12UniformBuffer::DX12UniformBuffer(RendererContext* rendererContext, const UniformBufferAttribute& attribute) 
        : UniformBuffer(attribute), mGPUConstantBuffer(), mGPUShaderResourceBuffer(), mGPUUnorderedAccessBuffer()
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
    }

    DX12UniformBuffer::~DX12UniformBuffer() {
    }

    void DX12UniformBuffer::Upload(void* data, uint64_t sizeInBytes) {
        uint64_t alignedSize = AlignForward(sizeInBytes, 256);

        // TODO: カスタマイズ可能化
        D3D12_HEAP_PROPERTIES heapProps = {};
        heapProps.Type = D3D12_HEAP_TYPE_UPLOAD; 
        heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

        D3D12_RESOURCE_DESC	resourceDesc = {};
        resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resourceDesc.Alignment = 0;
        resourceDesc.Width = sizeInBytes;
        resourceDesc.Height = 1;
        resourceDesc.DepthOrArraySize = 1;
        resourceDesc.MipLevels = 1;
        resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
        resourceDesc.SampleDesc.Count = 1;
        resourceDesc.SampleDesc.Quality = 0;
        resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

        DX12CheckException(mRendererContext->GetDevice()->CreateCommittedResource(
            &heapProps,
            D3D12_HEAP_FLAG_NONE,
            &resourceDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&mGPUConstantBuffer)
        ));

        void* uploadAddress = nullptr;
        mGPUConstantBuffer->Map(0, nullptr, (void**)&uploadAddress);
        memcpy(uploadAddress, data, sizeInBytes);
        mGPUConstantBuffer->Unmap(0, nullptr);
    }
}