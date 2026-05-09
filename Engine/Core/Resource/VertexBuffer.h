#pragma once

#include"Core/Resource/Buffer.h"
#include"Core/Resource/VertexLayout.h"

namespace VIEngine {
    class VI_API VertexBuffer : public Buffer {
        DECLARE_RTTI
    public:
        VertexBuffer() = default;
        VertexBuffer(const VertexLayout& layout) noexcept : mLayout(layout) {}
        ~VertexBuffer() = default;
        VI_FORCE_INLINE const VertexLayout& GetLayout() const { return mLayout; }
        VI_FORCE_INLINE void SetLayout(const VertexLayout& layout) { mLayout = layout; }
    private:
        VertexLayout mLayout;
    };
}