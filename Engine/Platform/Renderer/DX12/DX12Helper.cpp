#include"Platform/Renderer/DX12/DX12Helper.h"
#include<d3dcompiler.h>

namespace VIEngine {
    D3D12_HEAP_TYPE EngineToDX12HeapType(EBufferUsage usage) {
        switch (usage)
        {
            case EBufferUsage::STATIC:  return D3D12_HEAP_TYPE_DEFAULT;
            case EBufferUsage::DYNAMIC: return D3D12_HEAP_TYPE_UPLOAD;
            default:                    return D3D12_HEAP_TYPE_DEFAULT;
        }
    }

    D3D12_COMMAND_LIST_TYPE EngineToDX12RenderCommand(ERenderCommandType renderCommandType) {
        switch (renderCommandType)
        {
            case ERenderCommandType::MAIN:  return D3D12_COMMAND_LIST_TYPE_DIRECT;
            case ERenderCommandType::SUB:   return D3D12_COMMAND_LIST_TYPE_BUNDLE;
            default:                        return D3D12_COMMAND_LIST_TYPE_DIRECT;
        }
    }

    D3D12_COMMAND_QUEUE_PRIORITY EngineToDX12QueuePriority(EQueuePriority priority) {
        switch (priority)
        {
            case EQueuePriority::NORMAL:    return D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
            case EQueuePriority::HIGH:      return D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
            case EQueuePriority::REALTIME:  return D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME;
            default:                        return D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        }
    }

    DXGI_FORMAT EngineToDX12Format(EFormat format) {
        switch (format)
        {
            case EFormat::FLOAT:                return DXGI_FORMAT_R32_FLOAT;
            case EFormat::FLOAT2:               return DXGI_FORMAT_R32G32_FLOAT;
            case EFormat::FLOAT3:               return DXGI_FORMAT_R32G32B32_FLOAT;
            case EFormat::FLOAT4:               return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case EFormat::INT:                  return DXGI_FORMAT_R32_SINT;
            case EFormat::INT2:                 return DXGI_FORMAT_R32G32_SINT;
            case EFormat::INT3:                 return DXGI_FORMAT_R32G32B32_SINT;
            case EFormat::INT4:                 return DXGI_FORMAT_R32G32B32A32_SINT;
            case EFormat::UINT:                 return DXGI_FORMAT_R32_UINT;
            case EFormat::UINT2:                return DXGI_FORMAT_R32G32_UINT;
            case EFormat::UINT3:                return DXGI_FORMAT_R32G32B32_UINT;
            case EFormat::UINT4:                return DXGI_FORMAT_R32G32B32A32_UINT;
            case EFormat::RGBA8_UNORM:          return DXGI_FORMAT_R8G8B8A8_UNORM;
            case EFormat::NONE: default:        return DXGI_FORMAT_UNKNOWN;
        }
    }

    uint64_t EngineToDX12Usage(EUsage format) {
        switch (format)
        {
            case EUsage::SHADER_INPUT:                  return DXGI_USAGE_SHADER_INPUT;
            case EUsage::RENDER_TARGET_OUTPUT:          return DXGI_USAGE_RENDER_TARGET_OUTPUT;
            case EUsage::BACK_BUFFER:                   return DXGI_USAGE_BACK_BUFFER;
            case EUsage::SHARED:                        return DXGI_USAGE_SHARED;
            case EUsage::READ_ONLY:                     return DXGI_USAGE_READ_ONLY;
            case EUsage::DISCARD_ON_PRESENT:            return DXGI_USAGE_DISCARD_ON_PRESENT;
            case EUsage::UNORDERED_ACCESS:              return DXGI_USAGE_UNORDERED_ACCESS;
            default:                                    VI_ASSERT("Unknown usage");
        }
    }

    DXGI_SCALING EngineToDX12ScaleMode(EScaleMode mode) {
        switch (mode)
        {
            case EScaleMode::STRETCH:                       return DXGI_SCALING_STRETCH;
            case EScaleMode::ASPECT_RATIO_STRETCH:          return DXGI_SCALING_ASPECT_RATIO_STRETCH;
            case EScaleMode::NONE: default:                 return DXGI_SCALING_NONE;
        }
    }
    
    DXGI_SWAP_EFFECT EngineToDX12SwapMode(ESwapMode mode) {
        switch (mode)
        {
            case ESwapMode::DISCARD:                  return DXGI_SWAP_EFFECT_DISCARD;
            case ESwapMode::SEQUENTIAL:               return DXGI_SWAP_EFFECT_SEQUENTIAL;
            case ESwapMode::FLIP_SEQUENTIAL:          return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
            case ESwapMode::FLIP_DISCARD:             return DXGI_SWAP_EFFECT_FLIP_DISCARD;
            default:                                  VI_ASSERT("Unknown swap mode");
        }
    }

    DXGI_ALPHA_MODE EngineToDX12AlphaMode(EAlphaMode mode) {
        switch (mode)
        {
            case EAlphaMode::PREMULTIPLIED:         return DXGI_ALPHA_MODE_PREMULTIPLIED;
            case EAlphaMode::STRAIGHT:              return DXGI_ALPHA_MODE_STRAIGHT;
            case EAlphaMode::IGNORED:               return DXGI_ALPHA_MODE_IGNORE;
            case EAlphaMode::FORCE:                 return DXGI_ALPHA_MODE_FORCE_DWORD;
            case EAlphaMode::NONE: default:         return DXGI_ALPHA_MODE_UNSPECIFIED;
        }
    }

    UINT EngineToDX12SwapchainFlags(ESwapchainFlag flags) {
        UINT result = 0;
        if (HasFlag(flags, ESwapchainFlag::NONPREROTATED)) {
            result |= DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;
        }
        if (HasFlag(flags, ESwapchainFlag::ALLOW_MODE_SWICH)) {
            result |= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        }
        if (HasFlag(flags, ESwapchainFlag::RESTRICTED_CONTENT)) {
            result |= DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT;
        }
        if (HasFlag(flags, ESwapchainFlag::RESTRICT_SHARED_RESOURCE_DRIVER)) {
            result |= DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER;
        }
        if (HasFlag(flags, ESwapchainFlag::DISPLAY_ONLY)) {
            result |= DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY;
        }
        if (HasFlag(flags, ESwapchainFlag::FRAME_LATENCY_WAITABLE_OBJECT)) {
            result |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        }
        if (HasFlag(flags, ESwapchainFlag::FOREGROUND_LAYER)) {
            result |= DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER;
        }
        if (HasFlag(flags, ESwapchainFlag::FULLSCREEN_VIDEO)) {
            result |= DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO;
        }
        if (HasFlag(flags, ESwapchainFlag::PROTECTED)) {
            result |= DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED;
        }
        if (HasFlag(flags, ESwapchainFlag::ALLOW_TEARING)) {
            result |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        }
        if (HasFlag(flags, ESwapchainFlag::RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS)) {
            result |= DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS;
        }
        return result;
    }

    D3D12_INPUT_CLASSIFICATION EngineToDX12InputType(EInputType type) {
        switch (type)
        {
            case EInputType::VERTEX:         return D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
            case EInputType::INSTANCE:       return D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
            default:                         VI_ASSERT("Unknown input type");
        }
    }

    UINT EngineToDX12ShaderCompileFlag(EShaderCompileFlag flags) {
        UINT result;
        if (HasFlag(flags, EShaderCompileFlag::DEBUG)) {
            result |= D3DCOMPILE_DEBUG;
        }
        if (HasFlag(flags, EShaderCompileFlag::SKIP_VALIDATION)) {
            result |= D3DCOMPILE_SKIP_VALIDATION;
        }
        if (HasFlag(flags, EShaderCompileFlag::SKIP_OPTIMIZATION)) {
            result |= D3DCOMPILE_SKIP_OPTIMIZATION;
        }
        if (HasFlag(flags, EShaderCompileFlag::OPTIMIZATION_LEVEL0)) {
            result |= D3DCOMPILE_OPTIMIZATION_LEVEL0;
        }
        if (HasFlag(flags, EShaderCompileFlag::OPTIMIZATION_LEVEL1)) {
            result |= D3DCOMPILE_OPTIMIZATION_LEVEL1;
        }
        if (HasFlag(flags, EShaderCompileFlag::OPTIMIZATION_LEVEL2)) {
            result |= D3DCOMPILE_OPTIMIZATION_LEVEL2;
        }
        if (HasFlag(flags, EShaderCompileFlag::OPTIMIZATION_LEVEL3)) {
            result |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
        }
        if (HasFlag(flags, EShaderCompileFlag::PACK_ROW_MATRIX)) {
            result |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
        }
        if (HasFlag(flags, EShaderCompileFlag::PACK_COLUMN_MATRIX)) {
            result |= D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;
        }
        if (HasFlag(flags, EShaderCompileFlag::WARNING_AS_ERRORS)) {
            result |= D3DCOMPILE_WARNINGS_ARE_ERRORS;
        }
        return result;
    }

    D3D12_DESCRIPTOR_RANGE_TYPE EngineToDX12DescriptorRangeType(EDescriptorRangeType type) {
        switch (type)
        {
            case EDescriptorRangeType::SHADER_RESOURCE:         return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
            case EDescriptorRangeType::UNORDERED_ACCESS:        return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
            case EDescriptorRangeType::CONSTANT_BUFFER:         return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
            case EDescriptorRangeType::SAMPLER:                 return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
            default:                                            VI_ASSERT("Unknown descriptor range type");
        }
    }

    D3D12_ROOT_PARAMETER_TYPE EngineToDX12RootParameterType(EDescriptorRangeLayoutType type) {
        switch (type)
        {
            case EDescriptorRangeLayoutType::DESCRIPTOR_TABLE:          return D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
            case EDescriptorRangeLayoutType::CONSTANTS_32BIT:           return D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
            case EDescriptorRangeLayoutType::CONSTANT_BUFFER_VIEW:      return D3D12_ROOT_PARAMETER_TYPE_CBV;
            case EDescriptorRangeLayoutType::SHADER_RESOURCE_VIEW:      return D3D12_ROOT_PARAMETER_TYPE_SRV;
            case EDescriptorRangeLayoutType::UNORDERED_ACCESS_VIEW:     return D3D12_ROOT_PARAMETER_TYPE_UAV;
            default:                                                    VI_ASSERT("Unknown root parameter type");
        }
    }

    D3D12_SHADER_VISIBILITY EngineToDX12ShaderVisbility(EShaderStageFlag flag) {
        switch (flag)
        {
            case EShaderStageFlag::ALL:                             return D3D12_SHADER_VISIBILITY_ALL;
            case EShaderStageFlag::VERTEX:                          return D3D12_SHADER_VISIBILITY_VERTEX;
            case EShaderStageFlag::TESSELLATION_CONTROL:            return D3D12_SHADER_VISIBILITY_HULL;
            case EShaderStageFlag::TESSELLATION_EVALUATE:           return D3D12_SHADER_VISIBILITY_DOMAIN;
            case EShaderStageFlag::GEOMETRY:                        return D3D12_SHADER_VISIBILITY_GEOMETRY;
            case EShaderStageFlag::PIXEL:                           return D3D12_SHADER_VISIBILITY_PIXEL;
            case EShaderStageFlag::AMPLIFICATION:                   return D3D12_SHADER_VISIBILITY_AMPLIFICATION;
            case EShaderStageFlag::MESH:                            return D3D12_SHADER_VISIBILITY_MESH;
            default:                                                VI_ASSERT("Unknown root parameter type");
        }
    }
}