#include"Core/Resource/VertexLayout.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(VertexLayout)

    VertexLayout::VertexLayout(std::initializer_list<VertexAttribute> attributes) {
        AddAttributes(attributes);
    }

    void VertexLayout::AddAttribute(const VertexAttribute& attribute) {
        mAttributes.push_back(attribute);
    }

    void VertexLayout::AddAttributes(std::initializer_list<VertexAttribute> attributes) {
        for (auto attribute : attributes) {
            mAttributes.push_back(attribute);
        }
    }

    uint64_t VertexLayout::GetSize() const {
        uint16_t sizeInBytes = 0;
        for (const VertexAttribute& attribute : mAttributes) {
            sizeInBytes += VertexAttribute::GetTypeSize(attribute.GetType());
        }
        return sizeInBytes;
    }
}