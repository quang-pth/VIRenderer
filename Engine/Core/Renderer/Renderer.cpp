#include"Core/Renderer/Renderer.h"
#include"Core/Renderer/RenderCommandQueue.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(Renderer)

    Renderer::Renderer() {
    }

    Renderer::~Renderer() {

    }

    bool Renderer::Init(Application* application) {
        mApplication = application;
        mContext = RendererContext::Create(application);
        if (!mContext->Init()) {
            return false;
        }

        return true;
    }

    bool Renderer::BeginScene() {
        return true;
    }

    void Renderer::WaitAndProcess() {
        //  ClearRenderCommands()
        //  renderPasses = SortRenderPass()
        //  rootSignature = GetBaseRootSignature()
        //  for pass : renderPasses
        //    shader = pass->GetShader()
        //    renderPipeline = mContext.Get(pass.GetRenderPipeline())    
        //    mContext.SetRenderPipeline(rootSignature, renderPipeline)
        //    for instance : GetVisibleInstances(pass)
        //      mContext.SetVertexBuffer(instance.GetVertexBuffer())
        //      mContext.SetIndexBuffer(instance.GetIndexBuffer())
        //      mContext.SetPrimitive(TRIANGLE)
        //      mContext.DrawInstanced(indexBuffer.GetCount(), instanceCount, indexLocation, vertexLocation, instanceLocation)
        //    mContext.SubmitRenderCommand()
        //  ExecuteRenderCommands(commands, count)
        mContext->GetRenderCommandQueue()->Execute();
    }

    void Renderer::Present() {
        mContext->Present();
    }

    void Renderer::EndScene() {

    }
}