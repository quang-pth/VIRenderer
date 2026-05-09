#pragma once

#include"Core/Resource/VertexAttribute.h"

namespace VIEngine {
    class VI_API VertexLayout {
        DECLARE_RTTI
    public:
        VertexLayout() = default;
        VertexLayout(std::initializer_list<VertexAttribute> attributes);
        ~VertexLayout() = default;
        void AddAttribute(const VertexAttribute& attribute);
        void AddAttributes(std::initializer_list<VertexAttribute> attributes);
        VI_FORCE_INLINE const std::vector<VertexAttribute>& GetAttributes() const { return mAttributes; }
        uint64_t GetSize() const;
    private:
        std::vector<VertexAttribute> mAttributes;
    };
}