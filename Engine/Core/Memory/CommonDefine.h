#pragma once

#include"Core/pch.h"

namespace VIEngine {
    uint8_t GetAddressAdjustment(const void* address, uint8_t alignment);
    uint8_t GetAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory);
    size_t AlignForward(size_t memorySize, size_t alignment);
    bool IsPowerOfTwo(uint64_t alignment);
}