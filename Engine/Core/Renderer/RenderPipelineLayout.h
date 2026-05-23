#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/CommonDefine.h"

namespace VIEngine {
    class DescriptorRangeLayout;
    class UniformBufferLayout;

    class VI_API RenderPipelineLayout {
        DECLARE_RTTI
    public:
        static RenderPipelineLayout* Create(const RenderPipelineLayoutAttribute& attribute);
    public:
        virtual ~RenderPipelineLayout() = default;
        uint32_t GetLayoutIndex(const void* layoutAddress) const;
    protected:
        RenderPipelineLayout() = default;
        RenderPipelineLayout(const RenderPipelineLayoutAttribute& attribute) noexcept : mAttribute(attribute) {}
    protected:
        std::vector<DescriptorRangeLayout*> mDescriptorRangeLayouts;
        std::vector<UniformBufferLayout*> mUniformBufferLayouts;
        std::unordered_map<const void*, uint32_t> mLayoutIndex;
        RenderPipelineLayoutAttribute mAttribute;
    };
}