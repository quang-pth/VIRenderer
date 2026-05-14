#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/Shader.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;

    class VI_API DX12Shader : public Shader {
        DECLARE_RTTI
    public:
        DX12Shader() = default;
        DX12Shader(RendererContext* rendererContext, const ShaderAttribute& attribute);
        ~DX12Shader();
        ID3D10Blob* GetResource(EShaderStageFlag stageFlag) const;
    private:
        std::unordered_map<EShaderStageFlag, WRLComPtr<ID3DBlob>> mShaderResourceMap;
        DX12RendererContext* mRendererContext;
    };
}