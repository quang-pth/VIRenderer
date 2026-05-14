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

    enum class ESwapchainFlag : uint16_t {
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

    enum class EShaderStageFlag : uint8_t {
        NONE = 0,
        VERTEX = 1 << 1,
        TESSELLATION_CONTROL = 1 << 2,
        TESSELLATION_EVALUATE = 1 << 3,
        GEOMETRY = 1 << 4,
        PIXEL = 1 << 5,
        COMPUTE = 1 << 6
    };
    ENABLE_BITMASK_OPERATORS(EShaderStageFlag)

    enum class EShaderCompileFlag : uint16_t {
        NONE = 0,
        DEBUG = 1 << 0,
        SKIP_VALIDATION = 1 << 1,
        SKIP_OPTIMIZATION = 1 << 2,
        OPTIMIZATION_LEVEL0 = 1 << 3,
        OPTIMIZATION_LEVEL1 = 1 << 4,
        OPTIMIZATION_LEVEL2 = 1 << 5,
        OPTIMIZATION_LEVEL3 = 1 << 6,
        PACK_ROW_MATRIX = 1 << 7,
        PACK_COLUMN_MATRIX = 1 << 8,
        WARNING_AS_ERRORS = 1 << 9
    };
    ENABLE_BITMASK_OPERATORS(EShaderCompileFlag)

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

    struct ShaderStage {
        EShaderStageFlag Flags{EShaderStageFlag::NONE};
        std::string SourceFile;
    };

    struct ShaderAttribute {
        std::vector<ShaderStage> Stages;
    };

    struct ShaderMacro {
        std::string Name;
        std::string Definition;
    };

    struct ShaderCompilerConfig {
        std::string EntryPoint;
        std::string Profile;
        EShaderCompileFlag Flags{EShaderCompileFlag::NONE};
        std::vector<ShaderMacro> Macros{};
    };
    
    VI_FORCE_INLINE bool HasFlag(ESwapchainFlag flags, ESwapchainFlag target) { return (flags & target) == target; }
    VI_FORCE_INLINE bool HasFlag(EShaderCompileFlag flags, EShaderCompileFlag target) { return (flags & target) == target; }
}