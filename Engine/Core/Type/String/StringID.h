#pragma once

#include"Core/pch.h"

namespace VIEngine {
    // FNV-1aハッシュ
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    //-----------------------------------------------------------------------------
    #pragma warning(disable : 4307)

    constexpr long long FNV_PRIME = 0x100000001b3;
    constexpr long long FNV_OFFSET_BASIS = 0xcbf29ce484222325;

    constexpr const unsigned long long HashConcatString(unsigned long long base, const char *str) {
        return (*str) ? HashConcatString(base ^ *str * FNV_PRIME, str + 1) : base;       
    }

    constexpr const unsigned long long HashString(const char *str) {
        return HashConcatString(FNV_OFFSET_BASIS, str);
    }

    class VI_API StringID {
    public:
        explicit StringID(uint64_t data);
        explicit StringID(const char* data);
        ~StringID();
        VI_FORCE_INLINE uint64_t GetData() const { return mData; }
        VI_FORCE_INLINE bool operator==(const StringID& other) const { return mData == other.GetData(); }
    private:
        uint64_t mData;
    };
}

std::ostream& operator<<(std::ostream& out, VIEngine::StringID stringID);

namespace std {
    template<>
    struct hash<VIEngine::StringID> {
        size_t operator()(const VIEngine::StringID& stringID) const {
            return std::hash<uint64_t>{}(stringID.GetData());
        }
    };
}