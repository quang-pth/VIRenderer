#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/GPUVertexBufferAccessor.h"

namespace VIEngine {
    class DX12Buffer;

    class VI_API DX12VertexBufferAccessor : public GPUVertexBufferAccessor {
        DECLARE_RTTI
    public:
        DX12VertexBufferAccessor(GPUBuffer *const* vertexBuffer, const VertexLayout* layout, uint64_t count);
        ~DX12VertexBufferAccessor();
        VI_FORCE_INLINE const std::vector<D3D12_VERTEX_BUFFER_VIEW>& GetViews() const  { return mViews; }
        D3D12_VERTEX_BUFFER_VIEW* GetView(const DX12Buffer* buffer) const;
    private:
        std::vector<const DX12Buffer*> mVertexBuffers;
        std::vector<D3D12_VERTEX_BUFFER_VIEW> mViews;
        std::unordered_map<const DX12Buffer*, D3D12_VERTEX_BUFFER_VIEW*> mViewMap;
    };
}