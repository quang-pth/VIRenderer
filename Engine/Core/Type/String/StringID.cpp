#include"Core/Type/String/StringID.h"

namespace VIEngine {
    StringID::StringID(uint64_t data) : mData(data) {

    }

    StringID::StringID(const char* data) : mData(HashString(data)) {

    }

    StringID::~StringID() {
        
    }
}

std::ostream& operator<<(std::ostream& out, VIEngine::StringID stringID) { return out << std::to_string(stringID.GetData()); }


