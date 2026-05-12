#include"Platform/Renderer/DX12/DX12VertexBufferAccessor.h"
#include"Platform/Renderer/DX12/DX12Buffer.h"
#include"Core/Renderer/GPUBuffer.h"
#include"Core/Resource/Buffer.h"

namespace VIEngine {
    DEFINE_RTTI(DX12VertexBufferAccessor, GPUVertexBufferAccessor::RunTimeType)

    GPUVertexBufferAccessor* GPUVertexBufferAccessor::Create(GPUBuffer*const* vertexBuffer, const VertexLayout* layout, uint64_t count) {
        return new DX12VertexBufferAccessor(vertexBuffer, layout, count);
    }

    DX12VertexBufferAccessor::DX12VertexBufferAccessor(GPUBuffer *const* vertexBuffer, const VertexLayout* layout, uint64_t count)  
        : GPUVertexBufferAccessor(layout, count)
    {
        mVertexBuffers.reserve(count);
        mViews.reserve(count);

        for (uint64_t i = 0; i < count; ++i) {
            const DX12Buffer* buffer = static_cast<const DX12Buffer*>(vertexBuffer[i]);
            VI_ASSERT(buffer != nullptr && "DX12Buffer is nullptr");
            VI_ASSERT(buffer->GetResource() != nullptr && "DX12Buffer.GetResource() return nullptr");
            mVertexBuffers.push_back(buffer);
            mViews.emplace_back(
                D3D12_VERTEX_BUFFER_VIEW{buffer->GetResource()->GetGPUVirtualAddress(),
                (UINT)buffer->GetCPUBuffer()->GetSize(),
                (UINT)mLayout[i].GetSize()
            });
            mViewMap[buffer] = &mViews[i];
        }

    }

    DX12VertexBufferAccessor::~DX12VertexBufferAccessor() {

    }

    D3D12_VERTEX_BUFFER_VIEW* DX12VertexBufferAccessor::GetView(const DX12Buffer* buffer) const {
        if (mViewMap.count(buffer) < 0) {
            return nullptr;
        }

        return mViewMap.at(buffer);
    }
}