#pragma once

#include"Core/pch.h"
#include"Core/Resource/CommonDefine.h"

#define ENABLE_BITMASK_OPERATORS(Type) \
    inline Type operator | (Type a, Type b) { return static_cast<Type>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); } \
    inline Type operator & (Type a, Type b) { return static_cast<Type>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); } \
    inline Type& operator |= (Type& a, Type b) { a = a | b; return a; }

namespace VIEngine {
    enum class EBufferUsage : uint8_t {
        STATIC,
        DYNAMIC
    };

    enum class ERenderCommandType : uint8_t {
        MAIN,
        SUB
    };

    enum class EQueuePriority : uint8_t{
        NORMAL,
        HIGH,
        REALTIME
    };

    enum class EUsage : uint8_t {
        SHADER_INPUT,
        RENDER_TARGET_OUTPUT,
        BACK_BUFFER,
        SHARED,
        READ_ONLY,
        DISCARD_ON_PRESENT,
        UNORDERED_ACCESS
    };

    enum class EScaleMode : uint8_t {
        NONE,
        STRETCH,
        ASPECT_RATIO_STRETCH
    };

    enum class ESwapMode : uint8_t {
        DISCARD,
        SEQUENTIAL,
        FLIP_SEQUENTIAL,
        FLIP_DISCARD
    };

    enum class EAlphaMode : uint8_t {
        NONE,
        PREMULTIPLIED,
        STRAIGHT,
        IGNORED ,
        FORCE
    };

    enum class ESwapchainFlag {
        NONPREROTATED = 1,
        ALLOW_MODE_SWICH = 1 << 1,
        RESTRICTED_CONTENT = 1 << 2,
        RESTRICT_SHARED_RESOURCE_DRIVER = 1 << 3,
        DISPLAY_ONLY = 1 << 4,
        FRAME_LATENCY_WAITABLE_OBJECT = 1 << 5,
        FOREGROUND_LAYER = 1 << 6,
        FULLSCREEN_VIDEO = 1 << 7,
        PROTECTED = 1 << 9,
        ALLOW_TEARING = 1 << 10,
        RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS = 1 << 11
    };
    ENABLE_BITMASK_OPERATORS(ESwapchainFlag)

    struct CommandQueueAttribute {
        ERenderCommandType Type;
        EQueuePriority Priority;
    };

    struct SampleAttribute {
        uint64_t Count;
        uint64_t Quantity;
    };

    struct SwapchainAttribute {
        uint64_t Width;
        uint64_t Height;
        EFormat Format;
        bool Stereo;
        SampleAttribute Sample;
        EUsage Usage;
        uint64_t BufferCount;
        EScaleMode ScaleMode;
        ESwapMode SwapMode;
        EAlphaMode AlphaMode;
        ESwapchainFlag Flags;
    };
}