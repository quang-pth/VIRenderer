#pragma once

#include"Core/Resource/Buffer.h"

namespace VIEngine {
    class VI_API IndexBuffer : public Buffer {
        DECLARE_RTTI
    public:
        IndexBuffer() = default;
        explicit IndexBuffer(void* data, uint64_t sizeBytes, uint64_t count, uint64_t offset = 0) noexcept : Buffer(data, sizeBytes, count, offset) {}
        ~IndexBuffer() = default;
    };
}