#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12Helper.h"
#include"Platform/Renderer/DX12/DX12RenderCommandQueue.h"
#include"Platform/Renderer/DX12/DX12Swapchain.h"
#include"Platform/Windows/Window/WindowsWindow.h"
#include"Core/Renderer/Renderer.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"
#include<d3dcommon.h>

namespace VIEngine {
    DEFINE_RTTI(DX12RendererContext, RendererContext::RunTimeType)

    RendererContext* RendererContext::Create(Application* application) {
        // TODO: Allocate with memory management system
        return new DX12RendererContext(application);
    }

    DX12RendererContext::DX12RendererContext(Application* app) 
        : RendererContext(app), mBackBuffers(mBackBufferCount)
    {

    }

    DX12RendererContext::~DX12RendererContext() {
        VI_FREE_MEMORY(mRenderCommandQueue);
        VI_FREE_MEMORY(mSwapchain);
    }

    bool DX12RendererContext::Init() {
    #if _DEBUG
        DX12CheckException(D3D12GetDebugInterface(IID_PPV_ARGS(&mDebug)));
        DX12CheckException(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&mFactory)));
        mDebug->EnableDebugLayer();
    #else
        DX12CheckException(CreateDXGIFactory1(IID_PPV_ARGS(&mFactory)));
    #endif
        for(UINT i = 0; mFactory->EnumAdapters(i, &mActiveAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
            mAdapters.push_back(mActiveAdapter);
        }
        for (auto adapter : mAdapters) {
            DXGI_ADAPTER_DESC desc;
            adapter->GetDesc(&desc);
            std::wstring wdesc(desc.Description);

            if (wdesc.find(L"NVIDIA") != std::wstring::npos) {
                mActiveAdapter = adapter;
                CORE_LOG_INFO("Using NVIDIA as adapter");
                break; 
            }
        }

        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_12_1,
            D3D_FEATURE_LEVEL_12_0,
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };
        for (auto featureLevel : featureLevels) {
            DX12CheckException(D3D12CreateDevice(mActiveAdapter.Get(), featureLevel, IID_PPV_ARGS(&mDevice)));
        }
        mCBVDescriptorHeapSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        mSamplerDescriptorHeapSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
        mRTVDescriptorHeapSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        mDSVDescriptorHeapSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

        mRenderCommandQueue = static_cast<DX12RenderCommandQueue*>(RenderCommandQueue::Create(this, {ERenderCommandType::MAIN, EQueuePriority::NORMAL}));
        
        mHWND = mApplication->GetPlatformWindow<WindowsWindow>()->GetHWND();
        SwapchainAttribute swapchainAttribute = {};
        swapchainAttribute.Width = mApplication->GetConfig().WindowConfig.Width; 
        swapchainAttribute.Height = mApplication->GetConfig().WindowConfig.Height;
        swapchainAttribute.Format = EFormat::RGBA8_UNORM; 
        swapchainAttribute.Stereo = false; 
        swapchainAttribute.Sample.Count = 1; 
        swapchainAttribute.Sample.Quantity = 0; 
        swapchainAttribute.BufferCount = mBackBufferCount; 
        swapchainAttribute.ScaleMode = EScaleMode::STRETCH; 
        swapchainAttribute.SwapMode = ESwapMode::FLIP_DISCARD; 
        swapchainAttribute.AlphaMode = EAlphaMode::NONE; 
        swapchainAttribute.Flags = ESwapchainFlag::ALLOW_MODE_SWICH;
        mSwapchain = static_cast<DX12Swapchain*>(Swapchain::Create(this, swapchainAttribute));

        D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeap = {};
        rtvDescriptorHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvDescriptorHeap.NodeMask = 0;
        rtvDescriptorHeap.NumDescriptors = 2;
        rtvDescriptorHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        DX12CheckException(mDevice->CreateDescriptorHeap(&rtvDescriptorHeap, IID_PPV_ARGS(&mRTVDescriptorHeap)));

        D3D12_RENDER_TARGET_VIEW_DESC rtvDescription = {};
        rtvDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        rtvDescription.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = mRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
        for (uint8_t i = 0; i < mBackBufferCount; ++i) {
            rtvHandle.ptr += i * mRTVDescriptorHeapSize;
            mSwapchain->GetNative()->GetBuffer(i, IID_PPV_ARGS(&mBackBuffers[i]));
            mDevice->CreateRenderTargetView(mBackBuffers[i].Get(), &rtvDescription, rtvHandle);
        }

        return true;
    }

    void DX12RendererContext::Present() {
        mSwapchain->Present(1, 0);
    }
}