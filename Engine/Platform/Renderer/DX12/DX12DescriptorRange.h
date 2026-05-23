#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/DescriptorRange.h"

namespace VIEngine {
    class VI_API DX12DescriptorRange final : public DescriptorRange {
        DECLARE_RTTI
    public:
        DX12DescriptorRange(const DescriptorRangeAttribute& attribute);
        ~DX12DescriptorRange() = default;
    };
}