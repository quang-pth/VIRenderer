#include"Platform/Renderer/DX12/DX12DescriptorRangeLayout.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12DescriptorRangeLayout, DescriptorRangeLayout::RunTimeType)

    DescriptorRangeLayout* DescriptorRangeLayout::Create(const DescriptorRangeLayoutAttribute& attribute) {
        return new DX12DescriptorRangeLayout(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12DescriptorRangeLayout::DX12DescriptorRangeLayout(RendererContext* rendererContext, const DescriptorRangeLayoutAttribute& attribute)
        : DescriptorRangeLayout(attribute), mRootParameter({}), mDescriptorRanges()
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);

        mRootParameter.ParameterType = EngineToDX12RootParameterType(EDescriptorRangeLayoutType::DESCRIPTOR_TABLE);
        mRootParameter.ShaderVisibility = EngineToDX12ShaderVisbility(mAttribute.ShaderVisibilityFlag);
        mRootParameter.DescriptorTable.NumDescriptorRanges = mAttribute.BindingList.size();
        mDescriptorRanges.reserve(mAttribute.BindingList.size());

        for (const DescriptorRangeLayoutBinding& layoutBinding : mAttribute.BindingList) {
            mDescriptorRanges.emplace_back(D3D12_DESCRIPTOR_RANGE{
                EngineToDX12DescriptorRangeType(layoutBinding.RangeType), 
                (UINT)layoutBinding.Count,
                (UINT)layoutBinding.BaseRegister,
                (UINT)layoutBinding.RegisterSpace,
                (UINT)layoutBinding.Offset,
            });
        }

        mRootParameter.DescriptorTable.pDescriptorRanges = mDescriptorRanges.data(); 
    }

    DX12DescriptorRangeLayout::~DX12DescriptorRangeLayout() {

    }
}