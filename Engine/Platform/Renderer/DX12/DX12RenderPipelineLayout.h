#pragma once

#include"Core/Renderer/RenderPipelineLayout.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;

    class VI_API DX12RenderPipelineLayout : public RenderPipelineLayout {
        DECLARE_RTTI
    public:
        DX12RenderPipelineLayout(RendererContext* rendererContext, const RenderPipelineLayoutAttribute& attribute);
        ~DX12RenderPipelineLayout();
        VI_FORCE_INLINE ID3D12RootSignature* GetRootSignature() const { return mRootSignature.Get(); } 
        VI_FORCE_INLINE const std::vector<D3D12_ROOT_PARAMETER>& GetRootParameters() const { return mRootParameters; }
    private:
        DX12RendererContext* mRendererContext;
        WRLComPtr<ID3D12RootSignature> mRootSignature;
        std::vector<D3D12_ROOT_PARAMETER> mRootParameters;
    };
}