#include"Platform/Renderer/DX12/DX12VertexBufferAccessor.h"
#include"Platform/Renderer/DX12/DX12Buffer.h"
#include"Core/Renderer/GPUBuffer.h"
#include"Core/Resource/Buffer.h"

namespace VIEngine {
    DEFINE_RTTI(DX12VertexBufferAccessor, GPUVertexBufferAccessor::RunTimeType)

    GPUVertexBufferAccessor* GPUVertexBufferAccessor::Create(const GPUVertexBufferAccessorAttribute& attribute) {
        return new DX12VertexBufferAccessor(attribute);
    }

    DX12VertexBufferAccessor::DX12VertexBufferAccessor(const GPUVertexBufferAccessorAttribute& attribute)  
        : GPUVertexBufferAccessor(attribute.Layout, attribute.Count)
    {
        mVertexBuffers.reserve(mCount);
        mViews.reserve(mCount);

        for (uint64_t i = 0; i < mCount; ++i) {
            const DX12Buffer* buffer = static_cast<const DX12Buffer*>(attribute.VertexBuffer[i]);
            VI_ASSERT(buffer != nullptr && "DX12Buffer is nullptr");
            VI_ASSERT(buffer->GetResource() != nullptr && "DX12Buffer.GetResource() return nullptr");
            mVertexBuffers.push_back(buffer);
            mViews.emplace_back(
                D3D12_VERTEX_BUFFER_VIEW{buffer->GetResource()->GetGPUVirtualAddress(),
                (UINT)buffer->GetCPUBuffer()->GetSize(),
                (UINT)mLayout[i].GetSize()
            });
        }

    }

    DX12VertexBufferAccessor::~DX12VertexBufferAccessor() {

    }
}