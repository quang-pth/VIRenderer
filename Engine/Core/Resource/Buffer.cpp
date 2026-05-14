#include"Core/Resource/Buffer.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(Buffer)

    Buffer* Buffer::Create(void* data, uint64_t sizeBytes) {
        // TODO: Allocate with memory mangement system
        return new Buffer(data, sizeBytes);
    }
}