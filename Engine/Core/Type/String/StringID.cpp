#include"Core/Type/String/StringID.h"

namespace VIEngine {
    constexpr const unsigned long long HashConcatString(unsigned long long base, const char *str) {
        return (*str) ? HashConcatString(base ^ *str * FNV_PRIME, str + 1) : base;       
    }

    constexpr const unsigned long long HashString(const char *str) {
        return HashConcatString(FNV_OFFSET_BASIS, str);
    }

    StringID::StringID(uint64_t data) : mData(data) {

    }

    StringID::StringID(const char* data) : mData(HashString(data)) {

    }

    StringID::~StringID() {
        
    }
}

std::ostream& operator<<(std::ostream& out, VIEngine::StringID stringID) { return out << std::to_string(stringID.GetData()); }


