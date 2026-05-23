#include"Platform/Renderer/DX12/DX12DescriptorRange.h"
#include"Core/Renderer/DescriptorRangeLayout.h"

namespace VIEngine {
    DEFINE_RTTI(DX12DescriptorRange, DescriptorRange::RunTimeType)

    DescriptorRange* DescriptorRange::Create(const DescriptorRangeAttribute& attribute) {
        return new DX12DescriptorRange(attribute);
    }

    DX12DescriptorRange::DX12DescriptorRange(const DescriptorRangeAttribute& attribute) 
        : DescriptorRange(attribute)
    {
    }
}