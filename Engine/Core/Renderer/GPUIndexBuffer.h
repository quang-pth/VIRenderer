#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/GPUBuffer.h"
#include"Core/Resource/IndexBuffer.h"

namespace VIEngine {
    class VI_API GPUIndexBuffer : public GPUBuffer {
        DECLARE_RTTI
    public:
        GPUIndexBuffer(IndexBuffer* cpuBuffer, EBufferUsage usage = EBufferUsage::STATIC) noexcept 
            :  GPUBuffer(usage), mCPUBuffer(cpuBuffer) {}
        virtual ~GPUIndexBuffer() = default;
        VI_FORCE_INLINE const IndexBuffer* GetCPUBuffer() const { return mCPUBuffer; }
        VI_FORCE_INLINE void SetCPUBuffer(IndexBuffer* cpuBuffer) { mCPUBuffer = cpuBuffer; }
    protected:
        GPUIndexBuffer() = default;
    protected:
        IndexBuffer* mCPUBuffer;
    };
}