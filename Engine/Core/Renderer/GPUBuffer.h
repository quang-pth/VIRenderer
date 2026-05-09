#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/RendererContext.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API GPUBuffer {
        DECLARE_RTTI
    public:
        GPUBuffer(EBufferUsage usage = EBufferUsage::STATIC) noexcept : mUsage(usage) {}
        virtual ~GPUBuffer() = default;
        VI_FORCE_INLINE EBufferUsage GetUsage() const { return mUsage; }
        VI_FORCE_INLINE void SetUsage(EBufferUsage usage) { mUsage = usage; }
    protected:
        GPUBuffer() = default;
    protected:
        EBufferUsage mUsage;
    };
}