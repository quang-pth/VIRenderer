#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/DescriptorRangeLayout.h"

namespace VIEngine {
    class DX12RendererContext;

    class VI_API DX12DescriptorRangeLayout final : public DescriptorRangeLayout {
        DECLARE_RTTI
    public:
        DX12DescriptorRangeLayout() = default;
        DX12DescriptorRangeLayout(class RendererContext* rendererContext, const DescriptorRangeLayoutAttribute& attribute);
        ~DX12DescriptorRangeLayout();
        VI_FORCE_INLINE const D3D12_ROOT_PARAMETER& GetRootParameter() const { return mRootParameter; }
    private:
        D3D12_ROOT_PARAMETER mRootParameter;
        std::vector<D3D12_DESCRIPTOR_RANGE> mDescriptorRanges;
        DX12RendererContext* mRendererContext;
    };
}