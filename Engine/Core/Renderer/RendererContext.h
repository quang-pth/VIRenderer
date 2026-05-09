#pragma once

#include"Core/Type/Object/RTTI.h"

namespace VIEngine {
    class RenderCommandQueue;

    class VI_API RendererContext {
        DECLARE_RTTI
    public:
        static RendererContext* Create(class Application* app);
    public:
        virtual ~RendererContext() = default;
        virtual bool Init() = 0;
        virtual void Present() = 0;
        VI_FORCE_INLINE RenderCommandQueue* GetRenderCommandQueue() { return GetRenderCommandQueueImpl(); }
    protected:
        virtual RenderCommandQueue* GetRenderCommandQueueImpl() = 0;
    protected:
        RendererContext(class Application*);
        RendererContext() = default;
    protected:
        class Application* mApplication;
        uint8_t mBackBufferCount;
    };
}