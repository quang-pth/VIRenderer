#pragma once

#include"Core/Type/Object/RTTI.h"

namespace VIEngine {
    class VI_API Buffer {
        DECLARE_RTTI
    public:
        static Buffer* Create(void* data, uint64_t sizeBytes, uint64_t count, uint64_t offset = 0);
    public:
        Buffer() = default;
        explicit Buffer(void* data, uint64_t sizeBytes, uint64_t count, uint64_t offset = 0) noexcept : mData(data), mSize(sizeBytes), mCount(count), mOffset(offset) {}
        virtual ~Buffer() = default;
        VI_FORCE_INLINE const void* GetData() const { return mData; }
        VI_FORCE_INLINE void SetData(void* data) { mData = data; }
        VI_FORCE_INLINE uint64_t GetSize() const { return mSize; }
        VI_FORCE_INLINE void SetSize(uint64_t size) { mSize = size; }
        VI_FORCE_INLINE uint64_t GetCount() const { return mCount; }
        VI_FORCE_INLINE void SetCount(uint64_t count) { mCount = count; }
        VI_FORCE_INLINE uint64_t GetOffset() const { return mOffset; }
        VI_FORCE_INLINE void SetOffset(uint64_t offset) { mOffset = offset; }
    protected:
        void* mData;
        uint64_t mSize;
        uint64_t mCount;
        uint64_t mOffset;
    };
}