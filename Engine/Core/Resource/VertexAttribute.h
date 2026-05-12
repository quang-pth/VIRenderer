#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Resource/CommonDefine.h"

namespace VIEngine {
    class VI_API VertexAttribute {
        DECLARE_RTTI
    public:
        static uint64_t GetFormatSize(EFormat attributeType);
    public:
        VertexAttribute() = default;
        VertexAttribute(const std::string& name, uint64_t index, EFormat format, uint64_t streamSlot, EInputType type) noexcept 
            : mName(name), mIndex(index), mFormat(format), mStreamSlot(streamSlot), mType(type) {}
        ~VertexAttribute() = default;
        VI_FORCE_INLINE const std::string& GetName() const { return mName; }
        VI_FORCE_INLINE void SetName(const std::string& name) { mName = name; }
        VI_FORCE_INLINE uint64_t GetStreamSlot() const { return mStreamSlot; }
        VI_FORCE_INLINE void SetStreamSlot(uint64_t streamSlot) { mStreamSlot = streamSlot; }
        VI_FORCE_INLINE uint64_t GetIndex() const { return mIndex; }
        VI_FORCE_INLINE void SetIndex(uint64_t index) { mIndex = index; }
        VI_FORCE_INLINE EFormat GetFormat() const { return mFormat; }
        VI_FORCE_INLINE void SetFormat(EFormat format) { mFormat = format; }
        VI_FORCE_INLINE EInputType GetType() const { return mType; }
        VI_FORCE_INLINE void SetType(EInputType type) { mType = type; }
    private:
        std::string mName;
        uint64_t mIndex;
        EFormat mFormat;
        uint64_t mStreamSlot;
        EInputType mType;
    };
}