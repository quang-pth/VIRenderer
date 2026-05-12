#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Resource/VertexLayout.h"

namespace VIEngine {
    class GPUBuffer;

    class VI_API GPUVertexBufferAccessor {
        DECLARE_RTTI
    public:
        static GPUVertexBufferAccessor* Create(class GPUBuffer *const* vertexBuffer, const VertexLayout* layout, uint64_t count);
    public:
        virtual ~GPUVertexBufferAccessor() = default;
    protected:
        GPUVertexBufferAccessor(const VertexLayout* layout, uint64_t count) noexcept : mLayout(layout), mCount(count) {}
    protected:
        const VertexLayout* mLayout;
        uint64_t mCount;
    };
}