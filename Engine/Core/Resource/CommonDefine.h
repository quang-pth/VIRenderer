#pragma once

#include"Core/pch.h"

namespace VIEngine {
    enum class EFormat : uint8_t {
        NONE,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        INT,
        INT2,
        INT3,
        INT4,
        UINT,
        UINT2,
        UINT3,
        UINT4,
        RGBA8_UNORM
    };

    enum class EInputType : uint8_t {
        VERTEX,
        INSTANCE
    };
}