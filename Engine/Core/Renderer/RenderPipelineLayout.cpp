#include"Core/Renderer/RenderPipelineLayout.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(RenderPipelineLayout)

    uint32_t RenderPipelineLayout::GetLayoutIndex(const void* layoutAddress) const { 
        VI_ASSERT(mLayoutIndex.count(layoutAddress) > 0 && "Invalid layout address");
        return mLayoutIndex.at(layoutAddress);
    }
}