#include"Platform/Renderer/DX12/DX12Shader.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12ShaderCompiler.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12Shader, Shader::RunTimeType)

    Shader* Shader::Create(const ShaderAttribute& attribute) {
        // TODO: Allocate with memory management system
        return new DX12Shader(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12Shader::DX12Shader(RendererContext* rendererContext, const ShaderAttribute& attribute) 
        : Shader(attribute), mShaderResourceMap() 
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
        mShaderResourceMap.reserve(attribute.Stages.size());

        for (const ShaderStage& shaderStage : mAttribute.Stages) {
            if (mShaderResourceMap.count(shaderStage.Flags) > 0) {
                CORE_LOG_WARN("Found duplicated shader stage in the same shader. Skip compile");
                continue;
            }
            ID3DBlob* resource = nullptr;
            // TODO: 既存シェーダーチェック、あった場合、返し、参照カウント増やす
            if (shaderStage.Flags == EShaderStageFlag::VERTEX) {
                resource = mRendererContext->GetDefaultVertexShaderCompiler()->Compile(shaderStage);
            }
            else if (shaderStage.Flags == EShaderStageFlag::PIXEL) {
                resource = mRendererContext->GetDefaultPixelShaderCompiler()->Compile(shaderStage);
            }
            if (resource != nullptr) {
                mShaderResourceMap[shaderStage.Flags].Attach(resource);
            }
            else {
                OutputDebugString(AnsiToWString("Failed to compile shader: " + shaderStage.SourceFile).c_str());
            }
        }
    }

    DX12Shader::~DX12Shader() {
        mShaderResourceMap.clear();
    }

    ID3D10Blob* DX12Shader::GetResource(EShaderStageFlag stageFlag) const {
        if (mShaderResourceMap.count(stageFlag) <= 0) {
            return nullptr;
        }

        return mShaderResourceMap.at(stageFlag).Get();
    }

    const void* DX12Shader::GetShaderByteCode(EShaderStageFlag stage) const {
        if (mShaderResourceMap.count(stage) <= 0) {
            return nullptr;
        }
        return mShaderResourceMap.at(stage)->GetBufferPointer();
    }

    size_t DX12Shader::GetShaderByteCodeSize(EShaderStageFlag stage) const {
        if (mShaderResourceMap.count(stage) <= 0) {
            return 0;
        }
        return mShaderResourceMap.at(stage)->GetBufferSize();
    }
}