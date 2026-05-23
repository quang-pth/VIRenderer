#pragma once

#include"Core/Renderer/InputAssembler.h"
#include"Platform/Renderer/Dx12/DX12IndexBufferAccessor.h"

namespace VIEngine {
    class DX12RendererContext;
    class DX12VertexBufferAccessor;

    class VI_API DX12InputAssembler final : public InputAssembler {
        DECLARE_RTTI
    public:
        DX12InputAssembler() = default;
        DX12InputAssembler(class RendererContext* rendererContext, const InputAssemblerAttribute& attribute);
        ~DX12InputAssembler();
        VI_FORCE_INLINE const std::vector<DX12VertexBufferAccessor*>& GetVertexBufferAccessors() const { return mVertexBufferAccessors; }
        VI_FORCE_INLINE DX12IndexBufferAccessor* GetIndexBufferAccessor() const { return mIndexBufferAccessor; }
        VI_FORCE_INLINE const std::vector<D3D12_INPUT_ELEMENT_DESC>& GetElementDesc() const { return mElementDesc; }
    private:
        DX12RendererContext* mRendererContext;
        std::vector<DX12VertexBufferAccessor*> mVertexBufferAccessors;
        DX12IndexBufferAccessor* mIndexBufferAccessor;
        std::vector<D3D12_INPUT_ELEMENT_DESC> mElementDesc;
    };
}