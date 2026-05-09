#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/RendererContext.h"

namespace VIEngine {
    class VI_API Renderer {
        DECLARE_RTTI
    public:
        Renderer();
        ~Renderer();
        bool Init(class Application*);
        bool BeginScene();
        void WaitAndProcess();
        void Present();
        void EndScene();
        VI_FORCE_INLINE RendererContext* GetContext() { return mContext; }
    protected:
        RendererContext* mContext;
        class Application* mApplication;
    };
}