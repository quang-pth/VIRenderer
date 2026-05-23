#include"Core/Renderer/UniformBuffer.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(UniformBuffer)

    void UniformBuffer::Push(void* data, uint64_t sizeInBytes) {
        VI_ASSERT(sizeInBytes > 0 && "Invalid data size");
        mConstantBuffers.emplace_back(data, sizeInBytes);
        mConstantBuffersSize += sizeInBytes;
    }
}