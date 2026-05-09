#pragma once

#include"Core/Renderer/Swapchain.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    class DX12RendererContext;

    class VI_API DX12Swapchain : public Swapchain {
    public:
        DX12Swapchain() = default;
        DX12Swapchain(RendererContext* rendererContext, const SwapchainAttribute& attribute);
        ~DX12Swapchain() = default;
        VI_FORCE_INLINE IDXGISwapChain4* GetNative() { return mSwapchain.Get(); }
    protected:
        virtual void PresentImpl(uint64_t syncInterval, uint64_t flags) override;
    private:
        DXGI_SWAP_CHAIN_DESC1 ToSwapChainDesc(const SwapchainAttribute& attribute);
    private:
        WRLComPtr<IDXGISwapChain4> mSwapchain;
        DX12RendererContext* mRendererContext;
        SwapchainAttribute mAttribute;
    };
}