#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/ShaderCompiler.h"

namespace VIEngine {
    class VI_API DX12ShaderCompiler final : public ShaderCompiler {
        DECLARE_RTTI
    public:
        DX12ShaderCompiler() = default;
        DX12ShaderCompiler(const ShaderCompilerConfig& config);
        ~DX12ShaderCompiler() = default;
        ID3DBlob* Compile(const ShaderStage& stage) const;
        ID3DBlob* Compile(const ShaderStage& stage, const ShaderCompilerConfig& compilerConfig) const;
    private:
        std::vector<D3D_SHADER_MACRO> ConvertMacros(const std::vector<ShaderMacro>& macros) const;
    };
}