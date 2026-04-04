#include"Platform/Windows/Input/WindowsInput.h"
#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    Input* Input::Create() { return new WindowsInput(); }

    WindowsInput::WindowsInput() : Input() {

    }

    WindowsInput::~WindowsInput() {

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

    EInputState WindowsInput::GetStateImpl(EKeyCode keyCode) {
        if (IsPressedImpl(keyCode)) return EInputState::Pressed;
        if (IsHeldImpl(keyCode)) return EInputState::Held;
        if (IsHeldImpl(keyCode)) return EInputState::Released;
        CORE_LOG_WARN("Invalid engine key {0}, return EKeyState::None", static_cast<uint16_t>(keyCode));
        return EInputState::None;
    }

    uint8_t WindowsInput::GetValueImpl(EMouseButton mouseButton) {
        if (IsPressedImpl(mouseButton) || IsHeldImpl(mouseButton)) return 1;
        return 0;
    }

    bool WindowsInput::IsPressedImpl(EMouseButton mouseButton) {
        uint8_t mouseKey = EngineToWindowsMouseButton(mouseButton);
        return !(mPreviousStates[mouseKey] & 0x80) && (mCurrentStates[mouseKey] & 0x80);
    }

    bool WindowsInput::IsHeldImpl(EMouseButton mouseButton) {
        uint8_t mouseKey = EngineToWindowsMouseButton(mouseButton);
        return (mPreviousStates[mouseKey] & 0x80) && (mCurrentStates[mouseKey] & 0x80);
    }

    bool WindowsInput::IsReleasedImpl(EMouseButton mouseButton) {
        uint8_t mouseKey = EngineToWindowsMouseButton(mouseButton);
        return (mPreviousStates[mouseKey] & 0x80) && !(mCurrentStates[mouseKey] & 0x80);
    }

    EInputState WindowsInput::GetStateImpl(EMouseButton mouseButton) {
        if (IsPressedImpl(mouseButton)) return EInputState::Pressed;
        if (IsHeldImpl(mouseButton)) return EInputState::Held;
        if (IsHeldImpl(mouseButton)) return EInputState::Released;
        CORE_LOG_WARN("Invalid mouse button {0}, return EKeyState::None", static_cast<uint16_t>(mouseButton));
        return EInputState::None;
    }

    void WindowsInput::UpdateKeyboardStates() {
        GetKeyboardState(mCurrentStates);
    }

    void WindowsInput::UpdateMouseStates() {
        uint8_t leftButton = EngineToWindowsMouseButton(EMouseButton::BUTTON_LEFT);
        uint8_t rightButton = EngineToWindowsMouseButton(EMouseButton::BUTTON_RIGHT);
        uint8_t middleButton = EngineToWindowsMouseButton(EMouseButton::BUTTON_MIDDLE);
        uint8_t backButton = EngineToWindowsMouseButton(EMouseButton::BUTTON_BACK);
        uint8_t forwardButton = EngineToWindowsMouseButton(EMouseButton::BUTTON_FORWARD);
        /* 
        GetKeyStateはスレッド固有のメッセージキューの状態を参照するため、カーネルモードへの遷移が発生せず、非常に高速です。
        しかし、データの正確性はPeekMessageの呼び出し頻度に依存するため、アクションゲームの移動処理にはGetAsyncKeyStateの方が適しています。
        */
        mCurrentStates[leftButton] = GetKeyState(leftButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[rightButton] = GetKeyState(rightButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[middleButton] = GetKeyState(middleButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[backButton] = GetKeyState(backButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[forwardButton] = GetKeyState(forwardButton) & 0x800 ? 0x80 : 0;
    }
}