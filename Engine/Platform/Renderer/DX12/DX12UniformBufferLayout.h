#pragma once

#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Core/Renderer/UniformBufferLayout.h"

namespace VIEngine {
    class RendererContext;
    class DX12RendererContext;

    class VI_API DX12UniformBufferLayout final : public UniformBufferLayout {
        DECLARE_RTTI
    public:
        DX12UniformBufferLayout(class RendererContext* rendererContext, const UniformBufferLayoutAttribute& attribute);
        ~DX12UniformBufferLayout();
    private:
        DX12RendererContext* mRendererContext;
    };
}