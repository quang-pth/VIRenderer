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
        VI_FORCE_INLINE uint8_t GetStreamSlot() const { return mStreamSlot; }
    protected:
        GPUVertexBufferAccessor(const VertexLayout* layout, uint64_t count, uint32_t streamSlot) noexcept : mLayout(layout), mCount(count), mStreamSlot(streamSlot) {}
    protected:
        const VertexLayout* mLayout;
        uint64_t mCount;
        uint32_t mStreamSlot;
    };
}