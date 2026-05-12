#pragma once

#include"Core/Type/Object/RTTI.h"

namespace VIEngine {
    class GPUBuffer;

    class VI_API GPUIndexBufferAccessor {
        DECLARE_RTTI
    public:
        static GPUIndexBufferAccessor* Create(class GPUBuffer* indexBuffer);
    public:
        virtual ~GPUIndexBufferAccessor() = default;
    protected:
        GPUIndexBufferAccessor() = default;
    };
}