#pragma once

#include"Core/Input/KeyCode.h"
#include<Windows.h>

namespace VIEngine {
    EKeyCode WindowsToEngineKeyCode(WPARAM wparam);
    WPARAM EngineToWindowsKeyCode(EKeyCode keyCode);
    EMouseButton WindowsToEngineMouseButton(WPARAM wparam);
    WPARAM EngineToWindowsMouseButton(EMouseButton mouseButton);
}