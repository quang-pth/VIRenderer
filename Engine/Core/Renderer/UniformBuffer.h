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
        VI_FORCE_INLINE const Buffer* GetConstantBuffers() const { return mConstantBuffers.data(); }
        VI_FORCE_INLINE uint64_t GetConstantBuffersSize() const { return mConstantBuffersSize; }
        void Push(void* data, uint64_t sizeInBytes);
        virtual void Upload() = 0;
    protected:
        UniformBuffer(const UniformBufferAttribute& attribute) noexcept : mAttribute(attribute), mConstantBuffers(), mConstantBuffersSize(0) {}
    protected:
        UniformBufferAttribute mAttribute;
        std::vector<Buffer> mConstantBuffers;
        uint64_t mConstantBuffersSize;
    };
}