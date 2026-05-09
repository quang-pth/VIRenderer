#include"Core/Renderer/RendererContext.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(RendererContext)

    RendererContext::RendererContext(Application* app) : mApplication(app), mBackBufferCount(2) {

    }
}