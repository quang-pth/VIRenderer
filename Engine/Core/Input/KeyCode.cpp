#include"Core/Input/KeyCode.h"

#include"Core/pch.h"

VIEngine::EKeyModifier operator|(VIEngine::EKeyModifier lhs, VIEngine::EKeyModifier rhs) {
    return static_cast<VIEngine::EKeyModifier>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}