#include"Core/Resource/VertexAttribute.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(VertexAttribute)

    uint64_t VertexAttribute::GetTypeSize(EFormat attributeType) {
        switch (attributeType)
        {
            case EFormat::FLOAT:       return sizeof(float);
            case EFormat::FLOAT2:      return sizeof(float) * 2;
            case EFormat::FLOAT3:      return sizeof(float) * 3;
            case EFormat::FLOAT4:      return sizeof(float) * 4;
            case EFormat::INT:         return sizeof(int32_t);
            case EFormat::INT2:        return sizeof(int32_t) * 2;
            case EFormat::INT3:        return sizeof(int32_t) * 3;
            case EFormat::INT4:        return sizeof(int32_t) * 4;
            case EFormat::UINT:        return sizeof(uint32_t);
            case EFormat::UINT2:       return sizeof(uint32_t) * 2;
            case EFormat::UINT3:       return sizeof(uint32_t) * 3;
            case EFormat::UINT4:       return sizeof(uint32_t) * 4;
        }
    }
}