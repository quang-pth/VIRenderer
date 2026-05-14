#pragma once

#include"Core/Type/Object/RTTI.h"

namespace VIEngine {
    class VI_API Buffer {
        DECLARE_RTTI
    public:
        static Buffer* Create(void* data, uint64_t sizeBytes);
    public:
        Buffer() = default;
        explicit Buffer(void* data, uint64_t sizeBytes) noexcept : mData(data), mSize(sizeBytes) {}
        virtual ~Buffer() = default;
        VI_FORCE_INLINE const void* GetData() const { return mData; }
        VI_FORCE_INLINE void SetData(void* data) { mData = data; }
        VI_FORCE_INLINE uint64_t GetSize() const { return mSize; }
        VI_FORCE_INLINE void SetSize(uint64_t size) { mSize = size; }
    protected:
        void* mData;
        uint64_t mSize;
    };
}