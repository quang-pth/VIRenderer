#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API UniformBufferLayout {
        DECLARE_RTTI
    public:
        static UniformBufferLayout* Create(const UniformBufferLayoutAttribute& attribute);
    public:
        virtual ~UniformBufferLayout() = default;
        VI_FORCE_INLINE EDescriptorRangeLayoutType GetLayoutType() const { return mAttribute.LayoutType; }
        VI_FORCE_INLINE EShaderStageFlag GetShaderVisibilityFlag() const { return mAttribute.ShaderVisibilityFlag; }
        VI_FORCE_INLINE uint32_t GetBaseRegister() const { return mAttribute.BaseRegister; }
        VI_FORCE_INLINE uint32_t GetRegisterSpace() const { return mAttribute.RegisterSpace; }
        VI_FORCE_INLINE uint32_t GetCount() const { return mAttribute.Count; }
    protected:
        UniformBufferLayout(const UniformBufferLayoutAttribute& attribute) noexcept : mAttribute(attribute) {}
    protected:
        UniformBufferLayoutAttribute mAttribute;
    };
}