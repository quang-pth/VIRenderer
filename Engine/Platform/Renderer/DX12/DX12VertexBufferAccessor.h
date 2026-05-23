#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/GPUVertexBufferAccessor.h"

namespace VIEngine {
    class DX12Buffer;

    class VI_API DX12VertexBufferAccessor final : public GPUVertexBufferAccessor {
        DECLARE_RTTI
    public:
        DX12VertexBufferAccessor(const GPUVertexBufferAccessorAttribute& attribute);
        ~DX12VertexBufferAccessor();
        VI_FORCE_INLINE const std::vector<D3D12_VERTEX_BUFFER_VIEW>& GetViews() const  { return mViews; }
    private:
        std::vector<const DX12Buffer*> mVertexBuffers;
        std::vector<D3D12_VERTEX_BUFFER_VIEW> mViews;
    };
}