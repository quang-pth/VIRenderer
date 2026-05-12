#include"Platform/Renderer/DX12/DX12Swapchain.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12RenderCommandQueue.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12Swapchain, Swapchain::RunTimeType)

    Swapchain* Swapchain::Create(RendererContext* rendererContext, const SwapchainAttribute& attribute) {
        // TODO: Allocate from memory management
        return new DX12Swapchain(rendererContext, attribute);
    } 

    DX12Swapchain::DX12Swapchain(RendererContext* rendererContext, const SwapchainAttribute& attribute) 
        : mAttribute(attribute)
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = ToSwapChainDesc(mAttribute);
        DX12CheckException(mRendererContext->mFactory->CreateSwapChainForHwnd(
            mRendererContext->mRenderCommandQueue->GetNative(), mRendererContext->mHWND,
            &swapChainDesc, nullptr, nullptr,
            (IDXGISwapChain1**)mSwapchain.GetAddressOf()
        ));
    }

    DXGI_SWAP_CHAIN_DESC1 DX12Swapchain::ToSwapChainDesc(const SwapchainAttribute& attribute) {
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = mAttribute.Width;
        swapChainDesc.Height = mAttribute.Height;
        swapChainDesc.Format = EngineToDX12Format(mAttribute.Format);
        swapChainDesc.Stereo = mAttribute.Stereo;
        swapChainDesc.SampleDesc.Count = mAttribute.Sample.Count;
        swapChainDesc.SampleDesc.Quality = mAttribute.Sample.Quantity;
        swapChainDesc.BufferUsage = EngineToDX12Usage(mAttribute.Usage);
        swapChainDesc.BufferCount = mRendererContext->mBackBufferCount;
        swapChainDesc.Scaling = EngineToDX12ScaleMode(mAttribute.ScaleMode);
        swapChainDesc.SwapEffect = EngineToDX12SwapMode(mAttribute.SwapMode);
        swapChainDesc.AlphaMode = EngineToDX12AlphaMode(mAttribute.AlphaMode);
        swapChainDesc.Flags = EngineToDX12SwapchainFlags(mAttribute.Flags);
        return swapChainDesc;
    }

    void DX12Swapchain::PresentImpl(uint64_t syncInterval, uint64_t flags) {
        mSwapchain->Present(syncInterval, flags);
    }
}