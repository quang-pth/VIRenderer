#pragma once

#include"Core/Input/KeyCode.h"
#include<Windows.h>

namespace VIEngine {
    EKeyCode WindowsToEngineKeyCode(WPARAM wparam);
    EMouseButton WindowsToEngineMouseButton(WPARAM wparam);
}