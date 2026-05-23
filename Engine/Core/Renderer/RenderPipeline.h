#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class RenderPipelineLayout;

    class VI_API RenderPipeline {
        DECLARE_RTTI
    public:
        static RenderPipeline* Create(const RenderPipelineAttribute& attribute);
    public:
        virtual ~RenderPipeline() = default;
        VI_FORCE_INLINE InputAssembler* GetInputAssembler() const { return mAttribute.pInputAssembler; }
        VI_FORCE_INLINE RenderPipelineLayout* GetPipelineLayout() const { return mAttribute.pPipelineLayout; }
        VI_FORCE_INLINE Shader* GetShader() const { return mAttribute.pShader; }
    protected:
        RenderPipeline() = default;
        RenderPipeline(const RenderPipelineAttribute& attribute) noexcept : mAttribute(attribute) {}
    protected:
        RenderPipelineAttribute mAttribute;
    };
}