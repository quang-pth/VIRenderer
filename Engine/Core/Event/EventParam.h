#pragma once

#include"Core/pch.h"
#include"Core/Input/KeyCode.h"

namespace VIEngine {
    using EventParam = std::variant<int, double, EKeyCode, EMouseButton>;
    using EventParamList = std::vector<EventParam>;
}