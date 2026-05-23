#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API DescriptorRange {
        DECLARE_RTTI
    public:
        static DescriptorRange* Create(const DescriptorRangeAttribute& attribute);
    public:
        virtual ~DescriptorRange() = default;
        // VI_FORCE_INLINE uint64_t GetDescriptorCount() const { return mAttribute.DescriptorCount; }
        // VI_FORCE_INLINE uint64_t GetBaseRegister() const { return mAttribute.BaseRegister; }
        // VI_FORCE_INLINE EDescriptorRangeType GetRangeType() const { return mAttribute.RangeType; }
        // VI_FORCE_INLINE uint64_t GetOffset() const { return mAttribute.Offset; }
    protected:
        DescriptorRange() = default;
        DescriptorRange(const DescriptorRangeAttribute& attribute) noexcept : mAttribute(attribute) {}
    protected:
        DescriptorRangeAttribute mAttribute;
    };
}