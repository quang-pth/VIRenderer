#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/GPUBuffer.h"
#include"Core/Resource/VertexBuffer.h"

namespace VIEngine {
    class VI_API GPUVertexBuffer : public GPUBuffer {
        DECLARE_RTTI
    public:
        GPUVertexBuffer(VertexBuffer* cpuBuffer, EBufferUsage usage = EBufferUsage::DYNAMIC) noexcept 
            : GPUBuffer(usage), mCPUBuffer(cpuBuffer) {}
        virtual ~GPUVertexBuffer() = default;
        VI_FORCE_INLINE const VertexBuffer* GetCPUBuffer() const { return mCPUBuffer; }
        VI_FORCE_INLINE void SetCPUBuffer(VertexBuffer* cpuBuffer) { mCPUBuffer = cpuBuffer; }
    protected:
        GPUVertexBuffer() = default;
    protected:
        VertexBuffer* mCPUBuffer;
    };
}