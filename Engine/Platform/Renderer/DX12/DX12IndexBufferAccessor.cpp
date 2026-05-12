#include"Platform/Renderer/DX12/DX12IndexBufferAccessor.h"
#include"Platform/Renderer/DX12/DX12Buffer.h"
#include"Core/Resource/Buffer.h"

namespace VIEngine {
    DEFINE_RTTI(DX12IndexBufferAccessor, GPUIndexBufferAccessor::RunTimeType)

    GPUIndexBufferAccessor* GPUIndexBufferAccessor::Create(GPUBuffer* indexBuffer) {
        // TODO: Allocate with memory mangement system
        return new DX12IndexBufferAccessor(indexBuffer);
    }

    DX12IndexBufferAccessor::DX12IndexBufferAccessor(GPUBuffer* indexBuffer) : mView({}) {
        mIndexBuffer = static_cast<DX12Buffer*>(indexBuffer);
        VI_ASSERT(mIndexBuffer != nullptr && "mIndexBuffer is nullptr");
        VI_ASSERT(mIndexBuffer->GetCPUBuffer() != nullptr && "mIndexBuffer.GetCPUBuffer() return nullptr");
        mView.BufferLocation = mIndexBuffer->GetResource()->GetGPUVirtualAddress();
        mView.SizeInBytes = mIndexBuffer->GetCPUBuffer()->GetSize();
        mView.Format = DXGI_FORMAT_R16_UINT;
    }

    DX12IndexBufferAccessor::~DX12IndexBufferAccessor() {
    }
}