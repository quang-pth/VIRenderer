#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/RenderCommand.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class VI_API RenderCommandQueue {
        DECLARE_RTTI
    public:
        static RenderCommandQueue* Create(class RendererContext* rendererContext, const CommandQueueAttribute& attribute);
    public:
        virtual ~RenderCommandQueue() = default;
        void Submit(RenderCommand** renderCommand, uint64_t count) { SubmitImpl(renderCommand, count); }
        void Execute() { ExecuteImpl(); }
    protected:
        RenderCommandQueue() = default;
        RenderCommandQueue(const CommandQueueAttribute& attribute) noexcept : mAttribute(attribute) {}
        virtual void SubmitImpl(RenderCommand** renderCommand, uint64_t count) = 0;
        virtual void ExecuteImpl() = 0;
    protected:
        CommandQueueAttribute mAttribute;
    };
}