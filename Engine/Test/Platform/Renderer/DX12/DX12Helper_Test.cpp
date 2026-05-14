#pragma once

#include<gtest/gtest.h>
#include<Platform/Renderer/DX12/DX12Helper.h>

namespace Test {
    using namespace VIEngine;

    TEST(DX12HelperTest, EngineToDX12HeapTypeStatic) {
        D3D12_HEAP_TYPE result = EngineToDX12HeapType(EBufferUsage::STATIC);
        EXPECT_EQ(result, D3D12_HEAP_TYPE_DEFAULT);
    }

    TEST(DX12HelperTest, EngineToDX12HeapTypeDynamic) {
        D3D12_HEAP_TYPE result = EngineToDX12HeapType(EBufferUsage::DYNAMIC);
        EXPECT_EQ(result, D3D12_HEAP_TYPE_UPLOAD);
    }

    TEST(DX12HelperTest, EngineToDX12RenderCommandMain) {
        D3D12_COMMAND_LIST_TYPE result = EngineToDX12RenderCommand(ERenderCommandType::MAIN);
        EXPECT_EQ(result, D3D12_COMMAND_LIST_TYPE_DIRECT);
    }

    TEST(DX12HelperTest, EngineToDX12RenderCommandSub) {
        D3D12_COMMAND_LIST_TYPE result = EngineToDX12RenderCommand(ERenderCommandType::SUB);
        EXPECT_EQ(result, D3D12_COMMAND_LIST_TYPE_BUNDLE);
    }

    TEST(DX12HelperTest, EngineToDX12QueuePriorityNormal) {
        D3D12_COMMAND_QUEUE_PRIORITY result = EngineToDX12QueuePriority(EQueuePriority::NORMAL);
        EXPECT_EQ(result, D3D12_COMMAND_QUEUE_PRIORITY_NORMAL);
    }

    TEST(DX12HelperTest, EngineToDX12QueuePriorityHigh) {
        D3D12_COMMAND_QUEUE_PRIORITY result = EngineToDX12QueuePriority(EQueuePriority::HIGH);
        EXPECT_EQ(result, D3D12_COMMAND_QUEUE_PRIORITY_HIGH);
    }

    TEST(DX12HelperTest, EngineToDX12QueuePriorityRealtime) {
        D3D12_COMMAND_QUEUE_PRIORITY result = EngineToDX12QueuePriority(EQueuePriority::REALTIME);
        EXPECT_EQ(result, D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME);
    
    }
    TEST(DX12HelperTest, EngineToDX12FormatFloat) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::FLOAT);
        EXPECT_EQ(result, DXGI_FORMAT_R32_FLOAT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatFloat2) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::FLOAT2);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32_FLOAT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatFloat3) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::FLOAT3);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32B32_FLOAT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatFloat4) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::FLOAT4);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32B32A32_FLOAT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatInt) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::INT);
        EXPECT_EQ(result, DXGI_FORMAT_R32_SINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatInt2) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::INT2);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32_SINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatInt3) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::INT3);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32B32_SINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatInt4) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::INT4);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32B32A32_SINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatUint) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::UINT);
        EXPECT_EQ(result, DXGI_FORMAT_R32_UINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatUint2) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::UINT2);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32_UINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatUint3) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::UINT3);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32B32_UINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatUint4) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::UINT4);
        EXPECT_EQ(result, DXGI_FORMAT_R32G32B32A32_UINT);
    }

    TEST(DX12HelperTest, EngineToDX12FormatRGBA8Unorm) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::RGBA8_UNORM);
        EXPECT_EQ(result, DXGI_FORMAT_R8G8B8A8_UNORM);
    }

    TEST(DX12HelperTest, EngineToDX12FormatNone) {
        DXGI_FORMAT result = EngineToDX12Format(EFormat::NONE);
        EXPECT_EQ(result, DXGI_FORMAT_UNKNOWN);
    }

    TEST(DX12HelperTest, EngineToDX12UsageShaderInput) {
        uint64_t result = EngineToDX12Usage(EUsage::SHADER_INPUT);
        EXPECT_EQ(result, DXGI_USAGE_SHADER_INPUT);
    }

    TEST(DX12HelperTest, EngineToDX12UsageRenderTargetOutput) {
        uint64_t result = EngineToDX12Usage(EUsage::RENDER_TARGET_OUTPUT);
        EXPECT_EQ(result, DXGI_USAGE_RENDER_TARGET_OUTPUT);
    }

    TEST(DX12HelperTest, EngineToDX12UsageBackBuffer) {
        uint64_t result = EngineToDX12Usage(EUsage::BACK_BUFFER);
        EXPECT_EQ(result, DXGI_USAGE_BACK_BUFFER);
    }

    TEST(DX12HelperTest, EngineToDX12UsageShared) {
        uint64_t result = EngineToDX12Usage(EUsage::SHARED);
        EXPECT_EQ(result, DXGI_USAGE_SHARED);
    }

    TEST(DX12HelperTest, EngineToDX12UsageReadOnly) {
        uint64_t result = EngineToDX12Usage(EUsage::READ_ONLY);
        EXPECT_EQ(result, DXGI_USAGE_READ_ONLY);
    }

    TEST(DX12HelperTest, EngineToDX12UsageDiscardOnPresent) {
        uint64_t result = EngineToDX12Usage(EUsage::DISCARD_ON_PRESENT);
        EXPECT_EQ(result, DXGI_USAGE_DISCARD_ON_PRESENT);
    }

    TEST(DX12HelperTest, EngineToDX12UsageUnorderedAccess) {
        uint64_t result = EngineToDX12Usage(EUsage::UNORDERED_ACCESS);
        EXPECT_EQ(result, DXGI_USAGE_UNORDERED_ACCESS);
    }
    
    // TEST(DX12HelperTest, EngineToDX12UsageUnknown) {
    //     EXPECT_DEATH(EngineToDX12Usage(static_cast<EUsage>(-1)), "Unknown usage");
    // }

    TEST(DX12HelperTest, EngineToDX12ScaleModeStretch) {
        DXGI_SCALING result = EngineToDX12ScaleMode(EScaleMode::STRETCH);
        EXPECT_EQ(result, DXGI_SCALING_STRETCH);
    }

    TEST(DX12HelperTest, EngineToDX12ScaleModeAspectRatioStretch) {
        DXGI_SCALING result = EngineToDX12ScaleMode(EScaleMode::ASPECT_RATIO_STRETCH);
        EXPECT_EQ(result, DXGI_SCALING_ASPECT_RATIO_STRETCH);
    }

    TEST(DX12HelperTest, EngineToDX12ScaleModeNone) {
        DXGI_SCALING result = EngineToDX12ScaleMode(EScaleMode::NONE);
        EXPECT_EQ(result, DXGI_SCALING_NONE);
    }

    TEST(DX12HelperTest, EngineToDX12SwapMode) {
        DXGI_SWAP_EFFECT result = EngineToDX12SwapMode(ESwapMode::DISCARD);
        EXPECT_EQ(result, DXGI_SWAP_EFFECT_DISCARD);
    }

    TEST(DX12HelperTest, EngineToDX12SwapModeSequential) {
        DXGI_SWAP_EFFECT result = EngineToDX12SwapMode(ESwapMode::SEQUENTIAL);
        EXPECT_EQ(result, DXGI_SWAP_EFFECT_SEQUENTIAL);
    }

    TEST(DX12HelperTest, EngineToDX12SwapModeFlipSequential) {
        DXGI_SWAP_EFFECT result = EngineToDX12SwapMode(ESwapMode::FLIP_SEQUENTIAL);
        EXPECT_EQ(result, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL);
    }

    TEST(DX12HelperTest, EngineToDX12SwapModeFlipDiscard) {
        DXGI_SWAP_EFFECT result = EngineToDX12SwapMode(ESwapMode::FLIP_DISCARD);
        EXPECT_EQ(result, DXGI_SWAP_EFFECT_FLIP_DISCARD);
    }

    // TEST(DX12HelperTest, EngineToDX12SwapModeUnknown) {
    //     EXPECT_DEATH(EngineToDX12SwapMode(static_cast<ESwapMode>(-1)), "Unknown swap mode");
    // }

    TEST(DX12HelperTest, EngineToDX12AlphaModePremultiplied) {
        DXGI_ALPHA_MODE result = EngineToDX12AlphaMode(EAlphaMode::PREMULTIPLIED);
        EXPECT_EQ(result, DXGI_ALPHA_MODE_PREMULTIPLIED);
    }

    TEST(DX12HelperTest, EngineToDX12AlphaModeStraight) {
        DXGI_ALPHA_MODE result = EngineToDX12AlphaMode(EAlphaMode::STRAIGHT);
        EXPECT_EQ(result, DXGI_ALPHA_MODE_STRAIGHT);
    }

    TEST(DX12HelperTest, EngineToDX12AlphaModeIgnored) {
        DXGI_ALPHA_MODE result = EngineToDX12AlphaMode(EAlphaMode::IGNORED);
        EXPECT_EQ(result, DXGI_ALPHA_MODE_IGNORE);
    }

    TEST(DX12HelperTest, EngineToDX12AlphaModeForce) {
        DXGI_ALPHA_MODE result = EngineToDX12AlphaMode(EAlphaMode::FORCE);
        EXPECT_EQ(result, DXGI_ALPHA_MODE_FORCE_DWORD);
    }

    TEST(DX12HelperTest, EngineToDX12AlphaModeNone) {
        DXGI_ALPHA_MODE result = EngineToDX12AlphaMode(EAlphaMode::NONE);
        EXPECT_EQ(result, DXGI_ALPHA_MODE_UNSPECIFIED);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsNonPrerotated) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::NONPREROTATED);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_NONPREROTATED);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsAllowModeSwitch) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::ALLOW_MODE_SWICH);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsRestrictedContent) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::RESTRICTED_CONTENT);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsRestrictedSharedResourceDriver) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::RESTRICT_SHARED_RESOURCE_DRIVER);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsDisplayOnly) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::DISPLAY_ONLY);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsFrameLatencyWaitableObject) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::FRAME_LATENCY_WAITABLE_OBJECT);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsForegroundLayer) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::FOREGROUND_LAYER);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsFullscreenVideo) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::FULLSCREEN_VIDEO);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsProtected) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::PROTECTED);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsAllowTearing) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::ALLOW_TEARING);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsRestrictedToAllHolographicDisplays) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsBitwiseOr) {
        UINT result = EngineToDX12SwapchainFlags(ESwapchainFlag::NONPREROTATED | ESwapchainFlag::ALLOW_MODE_SWICH);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_NONPREROTATED | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsBitwiseOrEqual) {
        ESwapchainFlag flags = ESwapchainFlag::NONPREROTATED;
        flags |= ESwapchainFlag::ALLOW_MODE_SWICH;
        UINT result = EngineToDX12SwapchainFlags(flags);
        EXPECT_EQ(result, DXGI_SWAP_CHAIN_FLAG_NONPREROTATED | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    }

    TEST(DX12HelperTest, EngineToDX12SwapchainFlagsBitwiseAnd) {
        ESwapchainFlag flags = ESwapchainFlag::NONPREROTATED & ESwapchainFlag::ALLOW_MODE_SWICH;
        UINT result = EngineToDX12SwapchainFlags(flags);
        EXPECT_EQ(result, 0);
    }

    TEST(DX12HelperTest, HasFlag) {
        ESwapchainFlag flags = ESwapchainFlag::NONPREROTATED | ESwapchainFlag::ALLOW_MODE_SWICH;
        EXPECT_TRUE(HasFlag(flags, ESwapchainFlag::NONPREROTATED));
        EXPECT_TRUE(HasFlag(flags, ESwapchainFlag::ALLOW_MODE_SWICH));
        EXPECT_FALSE(HasFlag(flags, ESwapchainFlag::RESTRICTED_CONTENT));
    }
}