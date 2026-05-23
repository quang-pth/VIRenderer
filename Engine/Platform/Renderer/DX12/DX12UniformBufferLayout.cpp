#include"Platform/Renderer/DX12/DX12UniformBufferLayout.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12UniformBufferLayout, UniformBufferLayout::RunTimeType)

    UniformBufferLayout* UniformBufferLayout::Create(const UniformBufferLayoutAttribute& attribute) {
        return new DX12UniformBufferLayout(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12UniformBufferLayout::DX12UniformBufferLayout(RendererContext* rendererContext, const UniformBufferLayoutAttribute& attribute) 
        : UniformBufferLayout(attribute)
    {
        VI_ASSERT(mAttribute.LayoutType != EDescriptorRangeLayoutType::DESCRIPTOR_TABLE && "Invalid descriptor range layout type");
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
    }

    DX12UniformBufferLayout::~DX12UniformBufferLayout() {
        
    }
}