#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"
#include"Core/Resource/Buffer.h"

namespace VIEngine {
    class VI_API UniformBuffer {
        DECLARE_RTTI
    public:
        static UniformBuffer* Create(const UniformBufferAttribute& attribute);
    public:
        virtual ~UniformBuffer() = default;
        VI_FORCE_INLINE const UniformBufferLayout* GetLayout() const { return mAttribute.Layout; }
        virtual void Upload(void* data, uint64_t sizeInBytes) = 0;
    protected:
        UniformBuffer(const UniformBufferAttribute& attribute) noexcept : mAttribute(attribute) {}
    protected:
        UniformBufferAttribute mAttribute;
    };
}