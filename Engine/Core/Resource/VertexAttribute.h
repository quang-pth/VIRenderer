#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Resource/CommonDefine.h"

namespace VIEngine {
    class VI_API VertexAttribute {
        DECLARE_RTTI
    public:
        static uint64_t GetTypeSize(EFormat attributeType);
    public:
        VertexAttribute() = default;
        VertexAttribute(const std::string& name, EFormat type) noexcept : mName(name), mType(type) {}
        ~VertexAttribute() = default;
        VI_FORCE_INLINE const std::string& GetName() const { return mName; }
        VI_FORCE_INLINE void SetName(const std::string& name) { mName = name; }
        VI_FORCE_INLINE EFormat GetType() const { return mType; }
        VI_FORCE_INLINE void SetType(EFormat type) { mType = type; }
    private:
        std::string mName;
        EFormat mType;
    };
}