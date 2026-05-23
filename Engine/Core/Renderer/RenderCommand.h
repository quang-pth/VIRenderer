#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class RendererContext;
    class UniformBuffer;
    class RenderPipeline;

    class VI_API RenderCommand {
        DECLARE_RTTI
    public:
        static RenderCommand* Create(ERenderCommandType type);
    public:
        virtual ~RenderCommand() = default;
        VI_FORCE_INLINE void Submit() { SubmitImpl(); }
        VI_FORCE_INLINE void Reset() { ResetImpl(); }
        VI_FORCE_INLINE void SetRenderTarget() { SetRenderTargetImpl(); }
        VI_FORCE_INLINE void SetBackBufferRender() { SetBackBufferRenderImpl(); }
        VI_FORCE_INLINE void ClearColor(float r, float g, float b, float a = 1.0f) { ClearColorImpl(r, g, b, a); }
        VI_FORCE_INLINE void SetViewPort(float width, float height, float topLeftX, float topLeftY, float minDepth, float maxDepth) { SetViewPortImpl(width, height, topLeftX, topLeftY, minDepth, maxDepth); }
        VI_FORCE_INLINE void SetScissor(float top, float left, float right, float bottom) { SetScissorImpl(top, left, right, bottom); }
        VI_FORCE_INLINE void SetRenderPipeline(RenderPipeline* renderPipeline) { SetRenderPipelineImpl(renderPipeline); }
        VI_FORCE_INLINE void SetBackBufferPresent() { SetBackBufferPresentImpl(); }
        VI_FORCE_INLINE void Draw() { DrawImpl(); }
        VI_FORCE_INLINE void SetConstantsBuffer(UniformBuffer* buffer) { SetConstantsBufferImpl(buffer); }
    protected:
        virtual void SubmitImpl() = 0;
        virtual void ResetImpl() = 0;
        virtual void SetRenderTargetImpl() = 0;
        virtual void SetBackBufferRenderImpl() = 0;
        virtual void ClearColorImpl(float r, float g, float b, float a) = 0;
        virtual void SetViewPortImpl(float width, float height, float topLeftX, float topLeftY, float minDepth, float maxDepth) = 0;
        virtual void SetScissorImpl(float top, float left, float right, float bottom) = 0;
        virtual void SetRenderPipelineImpl(RenderPipeline* renderPipeline) = 0;
        virtual void SetBackBufferPresentImpl() = 0;
        virtual void DrawImpl() = 0;
        virtual void SetConstantsBufferImpl(UniformBuffer* buffer) = 0;
    protected:
        RenderCommand() = default;
        RenderCommand(ERenderCommandType type) noexcept : mType(type) {}
    protected:
        ERenderCommandType mType = ERenderCommandType::MAIN;
    };
}