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
        mVertexBufferLayouts.resize(mAttribute.VertexBuffers.size());
        mVertexBufferAccessors.reserve(mAttribute.VertexBuffers.size());

        for (auto& vertexAttribute : attribute.VertexAttributes) {
            uint64_t streamSlot = vertexAttribute.GetStreamSlot();
            VI_ASSERT((streamSlot >= 0 && streamSlot <= attribute.VertexAttributes.size()) && "Invalid vertex attribute index");
            mVertexBufferLayouts[vertexAttribute.GetStreamSlot()].AddAttribute(vertexAttribute);
        }

        for (uint32_t streamSlot = 0; streamSlot < mAttribute.VertexBuffers.size(); ++streamSlot) {
            DX12VertexBufferAccessor* bufferAccessor = static_cast<DX12VertexBufferAccessor*>(
                GPUVertexBufferAccessor::Create({
                    &mAttribute.VertexBuffers[0], 
                    &mVertexBufferLayouts[streamSlot], 
                    1, // 固定：1スロットあたり一つの頂点バッファにする
                    streamSlot
                })
            );
            mVertexBufferAccessors.push_back(bufferAccessor);
        }

        mIndexBufferAccessor = static_cast<DX12IndexBufferAccessor*>(GPUIndexBufferAccessor::Create(mAttribute.IndexBuffer));

        mElementDesc.resize(mAttribute.VertexAttributes.size());
        for (uint64_t i = 0; i < attribute.VertexAttributes.size(); ++i) {
            mElementDesc[i].SemanticName = mAttribute.VertexAttributes[i].GetName().c_str();
            mElementDesc[i].SemanticIndex = mAttribute.VertexAttributes[i].GetIndex();
            mElementDesc[i].Format = EngineToDX12Format(mAttribute.VertexAttributes[i].GetFormat());
            mElementDesc[i].InputSlot = mAttribute.VertexAttributes[i].GetStreamSlot();
            mElementDesc[i].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
            mElementDesc[i].InputSlotClass = EngineToDX12InputType(mAttribute.VertexAttributes[i].GetType());
            // TODO: インスタンシングをサポートする
            mElementDesc[i].InstanceDataStepRate = 0;
        }
    }

    DX12InputAssembler::~DX12InputAssembler() {
        for (auto& vertexBufferAccessor : mVertexBufferAccessors) {
            VI_FREE_MEMORY(vertexBufferAccessor)
        }
        mVertexBufferAccessors.clear();
        VI_FREE_MEMORY(mIndexBufferAccessor)
    }
}