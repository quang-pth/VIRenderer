#include"Core/Memory/CommonDefine.h"

namespace VIEngine {
    uint8_t GetAddressAdjustment(const void* address, uint8_t alignment) {
		VI_ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");

		/*
			0101 = 5 (address = 0x0101)
			&
			0011 = 3 (alignment = 4)
			0001 -> 1

			-> offset = alignment - 1 = 4 - 1 = 3 -> adjusted address = 0x1000
		*/

		uintptr_t remainder = reinterpret_cast<uintptr_t>(address) & (alignment - 1);
		if (remainder == 0) {
			return 0;
		}

		return alignment - remainder;
    }

    uint8_t GetAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory) {
		VI_ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");

		uint8_t padding = GetAddressAdjustment(address, alignment);
		if (padding < extraMemory) {
			uint8_t remainPadding = extraMemory - padding;

			if ((remainPadding & (alignment - 1)) != 0) {
				padding += alignment * (1 + (remainPadding / alignment));
			}
			else {
				padding += alignment * (remainPadding / alignment);
			}
		}

		return padding;
    }
    
    size_t AlignForward(size_t memorySize, size_t alignment) {
		VI_ASSERT(IsPowerOfTwo(alignment) && "Alignment is invalid");

		// 例：memorySize = 255, alignment = 256
		// 0x00000000000000ff (memorySize)
		// +
		// 0x00000000000000ff (alignment - 1)
		// =
		// 0x00000000000001fe
		// &
		// 0xffffffffffffff00 (~(alignment - 1))
		// =
		// 0x0000000000000100 (256)

		return (memorySize + (alignment - 1)) & ~(alignment - 1);
    }

    bool IsPowerOfTwo(uint64_t alignment) {
		/*
			0100 = 4
			&
			0011 = 3
			0000 -> true
			
			0101 = 5
			&
			0100 = 4
			0100 -> false
		*/
		return (alignment & (alignment - 1)) == 0;
    }
}