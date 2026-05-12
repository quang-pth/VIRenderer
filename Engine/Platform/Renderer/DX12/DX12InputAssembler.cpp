#include"Platform/Renderer/DX12/DX12InputAssembler.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12VertexBufferAccessor.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12InputAssembler, InputAssembler::RunTimeType)

    InputAssembler* InputAssembler::Create(const InputAssemblerAttribute& attribute) {
        // TODO: Allocator from memory management system
        return new DX12InputAssembler(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12InputAssembler::DX12InputAssembler(RendererContext* rendererContext, const InputAssemblerAttribute& attribute)
        : InputAssembler(attribute)
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
        mVertexBufferLayouts.resize(attribute.VertexAttributes.size());
        mElementDesc.resize(attribute.VertexAttributes.size());

        for (auto& vertexAttribute : attribute.VertexAttributes) {
            uint64_t streamSlot = vertexAttribute.GetStreamSlot();
            VI_ASSERT((streamSlot >= 0 && streamSlot <= attribute.VertexAttributes.size()) && "Invalid vertex attribute index");
            mVertexBufferLayouts[vertexAttribute.GetStreamSlot()].AddAttribute(vertexAttribute);
        }

        DX12VertexBufferAccessor* bufferAccessor = static_cast<DX12VertexBufferAccessor*>(GPUVertexBufferAccessor::
            Create(attribute.VertexBuffers.data(), mVertexBufferLayouts.data(), attribute.VertexAttributes.size())
        );

        mIndexBufferAccessor = static_cast<DX12IndexBufferAccessor*>(GPUIndexBufferAccessor::Create(attribute.IndexBuffer));

        mElementDesc.resize(attribute.VertexAttributes.size());
        for (uint64_t i = 0; i < attribute.VertexAttributes.size(); ++i) {
            mElementDesc[i].SemanticName = attribute.VertexAttributes[i].GetName().c_str();
            mElementDesc[i].SemanticIndex = attribute.VertexAttributes[i].GetIndex();
            mElementDesc[i].Format = EngineToDX12Format(attribute.VertexAttributes[i].GetFormat());
            mElementDesc[i].InputSlot = attribute.VertexAttributes[i].GetStreamSlot();
            mElementDesc[i].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
            mElementDesc[i].InputSlotClass = EngineToDX12InputType(attribute.VertexAttributes[i].GetType());
            // TODO: インスタンシングをサポートする
            mElementDesc[i].InstanceDataStepRate = 0;
        }
    }

    DX12InputAssembler::~DX12InputAssembler() {
        VI_FREE_MEMORY(mVertexBufferAccessor);
        VI_FREE_MEMORY(mIndexBufferAccessor)
    }
}