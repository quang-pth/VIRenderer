#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/GPUIndexBufferAccessor.h"

namespace VIEngine {
    class DX12Buffer;

    class VI_API DX12IndexBufferAccessor : public GPUIndexBufferAccessor {
        DECLARE_RTTI
    public:
        DX12IndexBufferAccessor(GPUBuffer* indexBuffer);
        ~DX12IndexBufferAccessor();
        VI_FORCE_INLINE const D3D12_INDEX_BUFFER_VIEW& GetView() const  { return mView; }
    private:
        DX12Buffer* mIndexBuffer;
        D3D12_INDEX_BUFFER_VIEW mView;
    };
}