#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API DescriptorRangeLayout {
        DECLARE_RTTI
    public:
        static DescriptorRangeLayout* Create(const DescriptorRangeLayoutAttribute& attribute);
    public:
        virtual ~DescriptorRangeLayout() = default;
        VI_FORCE_INLINE const DescriptorRangeLayoutBindingList& GetBindingList() const { return mAttribute.BindingList; }
    protected:
        DescriptorRangeLayout() = default;
        DescriptorRangeLayout(const DescriptorRangeLayoutAttribute& attribute) noexcept : mAttribute(attribute) {}
    protected:
        DescriptorRangeLayoutAttribute mAttribute;
    };
}