#include"Platform/Windows/Input/WindowsInput.h"
#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    Input* Input::Create() { return new WindowsInput(); }

    WindowsInput::WindowsInput() : Input() {

    }

    WindowsInput::~WindowsInput() {

    }

    void WindowsInput::Update() {
        Input::Update();
        GetKeyboardState(mCurrentStates);
    }

    uint8_t WindowsInput::GetValueImpl(EKeyCode keyCode) {
        if (IsPressedImpl(keyCode) || IsHeldImpl(keyCode)) return 1;
        return 0;
    }

    bool WindowsInput::IsPressedImpl(EKeyCode keyCode) {
        WPARAM windowsKey = EngineToWindowsKeyCode(keyCode);
        return !(mPreviousStates[windowsKey] & 0x80) && (mCurrentStates[windowsKey] & 0x80);
    }

    bool WindowsInput::IsHeldImpl(EKeyCode keyCode) {
        WPARAM windowsKey = EngineToWindowsKeyCode(keyCode);
        return (mPreviousStates[windowsKey] & 0x80) && (mCurrentStates[windowsKey] & 0x80);
    }

    bool WindowsInput::IsReleasedImpl(EKeyCode keyCode) {
        WPARAM windowsKey = EngineToWindowsKeyCode(keyCode);
        return (mPreviousStates[windowsKey] & 0x80) && !(mCurrentStates[windowsKey] & 0x80);
    }

    EKeyState WindowsInput::GetStateImpl(EKeyCode keyCode) {
        if (IsPressedImpl(keyCode)) return EKeyState::Pressed;
        if (IsHeldImpl(keyCode)) return EKeyState::Held;
        if (IsHeldImpl(keyCode)) return EKeyState::Released;
        CORE_LOG_WARN("Invalid engine key {0}, return EKeyState::None", static_cast<uint16_t>(keyCode));
        return EKeyState::None;
    }
}