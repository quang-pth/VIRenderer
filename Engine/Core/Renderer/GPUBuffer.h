#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/RendererContext.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class Buffer;

    class VI_API GPUBuffer {
        DECLARE_RTTI
    public:
        static GPUBuffer* Create(void* data, uint64_t sizeBytes, uint64_t count, uint64_t offset, EBufferUsage usage = EBufferUsage::STATIC);
    public:
        GPUBuffer(Buffer* cpuBuffer, uint64_t count, uint64_t offset, EBufferUsage usage = EBufferUsage::STATIC) noexcept 
            : mCPUBuffer(cpuBuffer), mCount(count), mOffset(offset), mUsage(usage) {}
        virtual ~GPUBuffer() = default;
        VI_FORCE_INLINE const Buffer* GetCPUBuffer() const { return mCPUBuffer; }
        VI_FORCE_INLINE void SetCPUBuffer(Buffer* cpuBuffer) { mCPUBuffer = cpuBuffer; }
        VI_FORCE_INLINE EBufferUsage GetUsage() const { return mUsage; }
        VI_FORCE_INLINE void SetUsage(EBufferUsage usage) { mUsage = usage; }
        VI_FORCE_INLINE uint64_t GetCount() const { return mCount; }
        VI_FORCE_INLINE void SetCount(uint64_t count) { mCount = count; }
        VI_FORCE_INLINE uint64_t GetOffset() const { return mOffset; }
        VI_FORCE_INLINE void SetOffset(uint64_t offset) { mOffset = offset; }
    protected:
        GPUBuffer() = default;
    protected:
        Buffer* mCPUBuffer;
        EBufferUsage mUsage;
        uint64_t mCount;
        uint64_t mOffset;
    };
}