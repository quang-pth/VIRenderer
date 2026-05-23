#include"Platform/Renderer/DX12/DX12RenderPipelineLayout.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12UniformBufferLayout.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12RenderPipelineLayout, RenderPipelineLayout::RunTimeType)

    RenderPipelineLayout* RenderPipelineLayout::Create(const RenderPipelineLayoutAttribute& attribute) {
        return new DX12RenderPipelineLayout(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12RenderPipelineLayout::DX12RenderPipelineLayout(RendererContext* rendererContext, const RenderPipelineLayoutAttribute& attribute)
        : RenderPipelineLayout(attribute)
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
        mRootParameters.reserve(mAttribute.UniformBufferLayouts.size());

        for(uint32_t i = 0; i < mAttribute.UniformBufferLayouts.size(); ++i) {
            UniformBufferLayout* uniformBufferLayout = mAttribute.UniformBufferLayouts[i];

            if (uniformBufferLayout == nullptr) {
                CORE_LOG_WARN("UniformBufferLayout is null");
                continue;
            }

            D3D12_ROOT_PARAMETER rootParam = {};
            rootParam.ParameterType = EngineToDX12RootParameterType(uniformBufferLayout->GetLayoutType());
            rootParam.ShaderVisibility = EngineToDX12ShaderVisbility(uniformBufferLayout->GetShaderVisibilityFlag());

            if (uniformBufferLayout->GetLayoutType() == EDescriptorRangeLayoutType::CONSTANTS_32BIT) {
                rootParam.Constants.Num32BitValues = uniformBufferLayout->GetCount();
                rootParam.Constants.ShaderRegister = uniformBufferLayout->GetBaseRegister();
                rootParam.Constants.RegisterSpace = uniformBufferLayout->GetRegisterSpace();
            }
            else {
                rootParam.Descriptor.ShaderRegister = uniformBufferLayout->GetBaseRegister();
                rootParam.Descriptor.RegisterSpace = uniformBufferLayout->GetRegisterSpace();
            }

            mRootParameters.push_back(rootParam);
            
            if (mLayoutIndex.count(uniformBufferLayout) <= 0) {
                mLayoutIndex[uniformBufferLayout] = i;
            }
        }

        // TODO: サンプラークラスを作成
        D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
        samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
        samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
        samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
        samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;

        D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
        rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
        rootSignatureDesc.NumParameters = mRootParameters.size();
        rootSignatureDesc.pParameters = mRootParameters.data();
        rootSignatureDesc.NumStaticSamplers = 1;
        rootSignatureDesc.pStaticSamplers = &samplerDesc;

        WRLComPtr<ID3DBlob> rootSignatureBlob;
        DX12CheckException(D3D12SerializeRootSignature(
            &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, rootSignatureBlob.GetAddressOf(), nullptr
        ));

        DX12CheckException(mRendererContext->GetDevice()->CreateRootSignature(
            0,
            rootSignatureBlob->GetBufferPointer(),
            rootSignatureBlob->GetBufferSize(),
            IID_PPV_ARGS(&mRootSignature)
        ));
        rootSignatureBlob->Release();
    }

    DX12RenderPipelineLayout::~DX12RenderPipelineLayout() {

    }
}