#pragma once

#include"Core/Renderer/RendererContext.h"
#include"Platform/Renderer/DX12/DX12Helper.h"

namespace VIEngine {
    class DX12ShaderCompiler;

    class DX12RendererContext : public RendererContext {
        DECLARE_RTTI

        friend class DX12RenderCommand;
        friend class DX12RenderCommandQueue;
        friend class DX12Swapchain;
    public:
        DX12RendererContext(class Application* app);
        ~DX12RendererContext();
        virtual bool Init() override;
        virtual void Present() override;

        VI_FORCE_INLINE ID3D12Device* GetDevice() const { return mDevice.Get(); }
        VI_FORCE_INLINE const DX12ShaderCompiler* GetDefaultVertexShaderCompiler() const { return mDefaultVertexShaderCompiler; }
        VI_FORCE_INLINE const DX12ShaderCompiler* GetDefaultPixelShaderCompiler() const { return mDefaultPixelShaderCompiler; }
    protected:
        virtual RenderCommandQueue* GetRenderCommandQueueImpl() override { return reinterpret_cast<RenderCommandQueue*>(mRenderCommandQueue); }
    private:
        WRLComPtr<ID3D12Device> mDevice;
        WRLComPtr<IDXGIFactory6> mFactory;
        WRLComPtr<ID3D12CommandQueue> mCommandQueue;
        std::vector<WRLComPtr<IDXGIAdapter>> mAdapters;
        WRLComPtr<IDXGIAdapter> mActiveAdapter;
        WRLComPtr<ID3D12DescriptorHeap> mRTVDescriptorHeap;
        std::vector<WRLComPtr<ID3D12Resource>> mBackBuffers;
        D3D12_CPU_DESCRIPTOR_HANDLE mCurrentRTVDescHandle;
        #if _DEBUG
        WRLComPtr<ID3D12Debug> mDebug;
        #endif
        UINT mCBVDescriptorHeapSize;
        UINT mSamplerDescriptorHeapSize;
        UINT mRTVDescriptorHeapSize;
        UINT mDSVDescriptorHeapSize;
        DX12RenderCommandQueue* mRenderCommandQueue;
        DX12Swapchain* mSwapchain;
        HWND mHWND;
        DX12ShaderCompiler* mDefaultVertexShaderCompiler;
        DX12ShaderCompiler* mDefaultPixelShaderCompiler;
    };
}