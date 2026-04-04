#pragma once

#include"Core/Input/KeyCode.h"
#include<Windows.h>

namespace VIEngine {
    EKeyCode WindowsToEngineKeyCode(WPARAM wparam);
    uint8_t EngineToWindowsKeyCode(EKeyCode keyCode);
    EMouseButton WindowsToEngineMouseButton(WPARAM wparam);
    uint8_t EngineToWindowsMouseButton(EMouseButton mouseButton);
}