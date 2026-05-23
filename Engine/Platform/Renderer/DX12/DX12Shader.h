#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/Shader.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;

    class VI_API DX12Shader final : public Shader {
        DECLARE_RTTI
    public:
        DX12Shader() = default;
        DX12Shader(RendererContext* rendererContext, const ShaderAttribute& attribute);
        ~DX12Shader();
        ID3D10Blob* GetResource(EShaderStageFlag stageFlag) const;
        virtual const void* GetShaderByteCode(EShaderStageFlag stage) const override;
        virtual size_t GetShaderByteCodeSize(EShaderStageFlag stage) const override;
    private:
        std::unordered_map<EShaderStageFlag, WRLComPtr<ID3DBlob>> mShaderResourceMap;
        DX12RendererContext* mRendererContext;
    };
}