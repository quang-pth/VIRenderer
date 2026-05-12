#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class RendererContext;

    class VI_API Swapchain {
        DECLARE_RTTI
    public:
        static Swapchain* Create(RendererContext* rendererContext, const SwapchainAttribute& attribute);
    public:
        virtual ~Swapchain() = default;
        void Present(uint64_t syncInterval, uint64_t flags) { PresentImpl(syncInterval, flags); }
    protected:
        virtual void PresentImpl(uint64_t syncInterval, uint64_t flags) = 0;
        Swapchain() = default;
    };
}