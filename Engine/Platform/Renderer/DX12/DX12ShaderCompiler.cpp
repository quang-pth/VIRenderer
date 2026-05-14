#include"Platform/Renderer/DX12/DX12ShaderCompiler.h"
#include<d3dcompiler.h>

namespace VIEngine {
    DEFINE_RTTI(DX12ShaderCompiler, ShaderCompiler::RunTimeType)

    ShaderCompiler* ShaderCompiler::Create() {
        // TODO: Allocate with memory management system
        return new DX12ShaderCompiler();
    }
  
    ShaderCompiler* ShaderCompiler::Create(const ShaderCompilerConfig& config) {
        // TODO: Allocate with memory management system
        return new DX12ShaderCompiler(config);
    }

    DX12ShaderCompiler::DX12ShaderCompiler(const ShaderCompilerConfig& config) : ShaderCompiler(config) {

    }

    ID3DBlob* DX12ShaderCompiler::Compile(const ShaderStage& stage) const {
        return Compile(stage, mDefaultConfig);
    }

    ID3DBlob* DX12ShaderCompiler::Compile(const ShaderStage& stage, const ShaderCompilerConfig& compilerConfig) const {
        ID3D10Blob* blob = nullptr;
        std::vector<D3D_SHADER_MACRO> shaderMacros = ConvertMacros(compilerConfig.Macros);
        DX12CheckException(D3DCompileFromFile(
            AnsiToWString(stage.SourceFile).c_str(),
            shaderMacros.size() ? shaderMacros.data() : nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE,
            compilerConfig.EntryPoint.c_str(),
            compilerConfig.Profile.c_str(),
            EngineToDX12ShaderCompileFlag(compilerConfig.Flags),
            0,
            &blob,
            nullptr
        ));
        return blob;
    }

    std::vector<D3D_SHADER_MACRO> DX12ShaderCompiler::ConvertMacros(const std::vector<ShaderMacro>& macros) const {
        std::vector<D3D_SHADER_MACRO> shaderMacro;
        shaderMacro.reserve(macros.size() + 1);
        for (const ShaderMacro& macro : macros) {
            shaderMacro.emplace_back(D3D_SHADER_MACRO{macro.Name.c_str(), macro.Definition.c_str()});
        }
        shaderMacro.emplace_back(D3D_SHADER_MACRO{NULL, NULL});
        return shaderMacro;
    }
}