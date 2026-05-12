#pragma once

#include"Core/Type/Object/RTTI.h"
#include"Core/Renderer/GPUBuffer.h"
#include"Core/Resource/VertexAttribute.h"
#include"Core/Resource/VertexLayout.h"

namespace VIEngine {
    struct InputAssemblerAttribute {
        std::vector<GPUBuffer*> VertexBuffers;
        GPUBuffer* IndexBuffer;
        std::vector<VertexAttribute> VertexAttributes;
    };

    class VI_API InputAssembler {
        DECLARE_RTTI
    public:
        static InputAssembler* Create(const InputAssemblerAttribute& attribute);
    public:
        virtual ~InputAssembler() = default;
    protected:
        InputAssembler() = default;
        InputAssembler(const InputAssemblerAttribute& attribute) noexcept : mAttribute(attribute), mVertexBufferLayouts() {}
    protected:
        InputAssemblerAttribute mAttribute;
        std::vector<VertexLayout> mVertexBufferLayouts;
    };
}