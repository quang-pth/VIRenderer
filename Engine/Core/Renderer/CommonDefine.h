#pragma once

#include"Core/pch.h"
#include"Core/Resource/CommonDefine.h"

#define ENABLE_BITMASK_OPERATORS(Type) \
    VI_FORCE_INLINE Type operator | (Type a, Type b) { return static_cast<Type>(static_cast<std::underlying_type_t<Type>>(a) | static_cast<std::underlying_type_t<Type>>(b)); } \
    VI_FORCE_INLINE Type operator & (Type a, Type b) { return static_cast<Type>(static_cast<std::underlying_type_t<Type>>(a) & static_cast<std::underlying_type_t<Type>>(b)); } \
    VI_FORCE_INLINE Type& operator |= (Type& a, Type b) { a = static_cast<Type>(static_cast<std::underlying_type_t<Type>>(a) | static_cast<std::underlying_type_t<Type>>(b)); return a; } \
    VI_FORCE_INLINE bool HasFlag(Type flags, Type target) { return (static_cast<std::underlying_type_t<Type>>(flags) & static_cast<std::underlying_type_t<Type>>(target)) == static_cast<std::underlying_type_t<Type>>(target); }

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

    enum class EShaderStageFlag : uint16_t {
        ALL = 0,
        VERTEX = 1 << 1,
        TESSELLATION_CONTROL = 1 << 2,
        TESSELLATION_EVALUATE = 1 << 3,
        GEOMETRY = 1 << 4,
        PIXEL = 1 << 5,
        COMPUTE = 1 << 6,
        AMPLIFICATION = 1 << 7,
        MESH = 1 << 8
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

    enum class EDescriptorRangeType : uint8_t {
        SHADER_RESOURCE,
        UNORDERED_ACCESS,
        CONSTANT_BUFFER,
        SAMPLER
    };

    enum class EDescriptorRangeLayoutType : uint8_t {
        DESCRIPTOR_TABLE,
        CONSTANTS_32BIT,
        CONSTANT_BUFFER_VIEW,
        SHADER_RESOURCE_VIEW,
        UNORDERED_ACCESS_VIEW,
    };

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
        EShaderStageFlag Flags;
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
        EShaderCompileFlag Flags;
        std::vector<ShaderMacro> Macros{};
    };

    class DescriptorRangeLayout;
    struct DescriptorRangeAttribute {
        const DescriptorRangeLayout* Layout;
    };

    struct DescriptorRangeLayoutBinding {
        EDescriptorRangeType RangeType;
        uint64_t Count;
        uint64_t BaseRegister;
        uint64_t RegisterSpace;
        uint64_t Offset{0xffffffff};
    };
    using DescriptorRangeLayoutBindingList = std::vector<DescriptorRangeLayoutBinding>;

    struct DescriptorRangeLayoutAttribute {
        DescriptorRangeLayoutBindingList BindingList;
        EShaderStageFlag ShaderVisibilityFlag;
    };

    struct UniformBufferLayoutAttribute {
        EDescriptorRangeLayoutType LayoutType;
        EShaderStageFlag ShaderVisibilityFlag;
        uint32_t BaseRegister;
        uint32_t RegisterSpace;
        uint32_t Count;
    };

    class UniformBufferLayout;
    struct UniformBufferAttribute {
        const UniformBufferLayout* Layout;
    };

    struct RenderPipelineLayoutAttribute {
        std::vector<UniformBufferLayout*> UniformBufferLayouts;
    };

    class InputAssembler;
    class RenderPipelineLayout;
    class Shader;
    struct RenderPipelineAttribute {
        InputAssembler* pInputAssembler;
        RenderPipelineLayout* pPipelineLayout;
        Shader* pShader;
    };

    class GPUBuffer;
    class VertexLayout;
    struct GPUVertexBufferAccessorAttribute {
        GPUBuffer *const* VertexBuffer;
        const VertexLayout* Layout; 
        uint64_t Count;
    };
}