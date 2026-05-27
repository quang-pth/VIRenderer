#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Resource/VertexLayout.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API GPUVertexBufferAccessor {
        DECLARE_RTTI
    public:
        static GPUVertexBufferAccessor* Create(const GPUVertexBufferAccessorAttribute& attribute);
    public:
        virtual ~GPUVertexBufferAccessor() = default;
        VI_FORCE_INLINE const VertexLayout* GetVertexLayout() const { return mLayout; }
        VI_FORCE_INLINE uint64_t GetCount() const { return mCount; }
    protected:
        GPUVertexBufferAccessor(const VertexLayout* layout, uint64_t count) noexcept : mLayout(layout), mCount(count) {}
    protected:
        const VertexLayout* mLayout;
        uint64_t mCount;
    };
}