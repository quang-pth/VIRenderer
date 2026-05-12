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
        GPUBuffer(Buffer* cpuBuffer, EBufferUsage usage = EBufferUsage::STATIC) noexcept : mCPUBuffer(cpuBuffer), mUsage(usage) {}
        virtual ~GPUBuffer() = default;
        VI_FORCE_INLINE const Buffer* GetCPUBuffer() const { return mCPUBuffer; }
        VI_FORCE_INLINE void SetCPUBuffer(Buffer* cpuBuffer) { mCPUBuffer = cpuBuffer; }
        VI_FORCE_INLINE EBufferUsage GetUsage() const { return mUsage; }
        VI_FORCE_INLINE void SetUsage(EBufferUsage usage) { mUsage = usage; }
    protected:
        GPUBuffer() = default;
    protected:
        Buffer* mCPUBuffer;
        EBufferUsage mUsage;
    };
}