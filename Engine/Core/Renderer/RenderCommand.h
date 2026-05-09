#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class RendererContext;
    
    class VI_API RenderCommand {
        DECLARE_RTTI
    public:
        static RenderCommand* Create(ERenderCommandType type);
    public:
        virtual ~RenderCommand() = default;
        VI_FORCE_INLINE void BeginRecord() { BeginRecordImpl(); }
        VI_FORCE_INLINE void EndRecord() { EndRecordImpl(); }
        VI_FORCE_INLINE void Reset() { ResetImpl(); }
        VI_FORCE_INLINE void ClearColor(float r, float g, float b, float a = 1.0f) { ClearColorImpl(r, g, b, a); }
        VI_FORCE_INLINE void SetRenderTarget() { SetRenderTargetImpl(); }
        VI_FORCE_INLINE void SetBackBufferRender() { SetBackBufferRenderImpl(); }
        VI_FORCE_INLINE void SetBackBufferPresent() { SetBackBufferPresentImpl(); }
    protected:
        virtual void BeginRecordImpl() = 0;
        virtual void EndRecordImpl() = 0;
        virtual void ResetImpl() = 0;
        virtual void ClearColorImpl(float r, float g, float b, float a) = 0;
        virtual void SetRenderTargetImpl() = 0;
        virtual void SetBackBufferRenderImpl() = 0;
        virtual void SetBackBufferPresentImpl() = 0;
    protected:
        RenderCommand() = default;
        RenderCommand(ERenderCommandType type) noexcept : mType(type) {}
    protected:
        ERenderCommandType mType = ERenderCommandType::MAIN;
    };
}