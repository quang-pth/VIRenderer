#include"Platform/Windows/Input/WindowsInput.h"
#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    Input* Input::Create() { return new WindowsInput(); }

    WindowsInput::WindowsInput() : Input(), mMouseButtonMap(), mPreviousGamepadStates(), mCurrentGamepadStates() {
        mMouseButtonMap[EMouseButton::BUTTON_LEFT] = EngineToWindowsMouseButton(EMouseButton::BUTTON_LEFT); 
        mMouseButtonMap[EMouseButton::BUTTON_RIGHT] = EngineToWindowsMouseButton(EMouseButton::BUTTON_RIGHT);
        mMouseButtonMap[EMouseButton::BUTTON_MIDDLE] = EngineToWindowsMouseButton(EMouseButton::BUTTON_MIDDLE);
        mMouseButtonMap[EMouseButton::BUTTON_BACK] = EngineToWindowsMouseButton(EMouseButton::BUTTON_BACK);
        mMouseButtonMap[EMouseButton::BUTTON_FORWARD] = EngineToWindowsMouseButton(EMouseButton::BUTTON_FORWARD);
        for (uint8_t index = 0; index < XUSER_MAX_COUNT; ++index) {
            memset(&mPreviousGamepadStates[index], 0, sizeof(XINPUT_STATE));
            memset(&mCurrentGamepadStates[index], 0, sizeof(XINPUT_STATE));
        }
    }

    WindowsInput::~WindowsInput() {
    }

    uint8_t WindowsInput::GetValueImpl(EKeyCode keyCode) {
        return IsPressed(keyCode) || IsHeld(keyCode);
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
        if (IsPressed(keyCode))         return EInputState::PRESSED;
        if (IsHeld(keyCode))            return EInputState::HELD;
        if (IsReleased(keyCode))        return EInputState::RELEASED;
        return EInputState::NONE;
    }

    uint8_t WindowsInput::GetValueImpl(EMouseButton mouseButton) {
        return IsPressed(mouseButton) || IsHeld(mouseButton);
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
        if (IsPressed(mouseButton))         return EInputState::PRESSED;
        if (IsHeld(mouseButton))            return EInputState::HELD;
        if (IsReleased(mouseButton))        return EInputState::RELEASED;
        return EInputState::NONE;
    }

    uint8_t WindowsInput::GetValueImpl(EGamepad gamepad, uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        if 
        (
            gamepad == EGamepad::BUTTON_LT || gamepad == EGamepad::BUTTON_RT || 
            gamepad == EGamepad::LEFT_THUMBSTICK || gamepad == EGamepad::RIGHT_THUMBSTICK
        )
        {
            return 0;
        }

        return IsPressed(gamepad, index) || IsHeld(gamepad, index);
    }

    float WindowsInput::GetLeftTriggerValueImpl(uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        
        if (GetState(EGamepad::BUTTON_LT) == EInputState::NONE) return 0.0f;

        XINPUT_STATE* inputState = &mCurrentGamepadStates[index];
        return Normalize(inputState->Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD, TRIGGER_THRESHOLD_MAX - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
    }
    
    float WindowsInput::GetRightTriggerValueImpl(uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");

        if (GetState(EGamepad::BUTTON_RT) == EInputState::NONE) return 0.0f;

        XINPUT_STATE* inputState = &mCurrentGamepadStates[index];
        return Normalize(inputState->Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD, TRIGGER_THRESHOLD_MAX - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
    }
    
    float WindowsInput::GetLeftThumbStickXValueImpl(uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* inputState = &mCurrentGamepadStates[index];

        if (std::abs(inputState->Gamepad.sThumbLX) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) return 0.0f;

        if (inputState->Gamepad.sThumbLX < 0) {
            return Normalize(
                inputState->Gamepad.sThumbLX + XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, 
                THUMBSTICK_THRESHOLD_MIN * -1.0f - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
            );
        }

        return Normalize(
            inputState->Gamepad.sThumbLX - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, 
            THUMBSTICK_THRESHOLD_MAX * 1.0f - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
        );
    }

    float WindowsInput::GetRightThumbStickXValueImpl(uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* inputState = &mCurrentGamepadStates[index];

        if (std::abs(inputState->Gamepad.sThumbRX) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) return 0.0f;

        if (inputState->Gamepad.sThumbRX < 0) {
            return Normalize(
                inputState->Gamepad.sThumbRX + XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE,
                THUMBSTICK_THRESHOLD_MIN * -1.0f - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
            );
        }

        return Normalize(
            inputState->Gamepad.sThumbRX - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, 
            THUMBSTICK_THRESHOLD_MAX * 1.0f - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
        );
    }

    float WindowsInput::GetLeftThumbStickYValueImpl(uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* inputState = &mCurrentGamepadStates[index];

        if (std::abs(inputState->Gamepad.sThumbLY) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) return 0.0f;

        if (inputState->Gamepad.sThumbLY < 0) {
            return Normalize(inputState->Gamepad.sThumbLY, THUMBSTICK_THRESHOLD_MIN * -1.0f);
        }

        return Normalize(inputState->Gamepad.sThumbLY, THUMBSTICK_THRESHOLD_MAX * 1.0f);
    }

    float WindowsInput::GetRightThumbStickYValueImpl(uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* inputState = &mCurrentGamepadStates[index];

        if (std::abs(inputState->Gamepad.sThumbRY) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) return 0.0f;

        if (inputState->Gamepad.sThumbRY < 0) {
            return Normalize(inputState->Gamepad.sThumbRY, THUMBSTICK_THRESHOLD_MIN * -1.0f);
        }

        return Normalize(inputState->Gamepad.sThumbRY, THUMBSTICK_THRESHOLD_MAX * 1.0f);
    }

    bool WindowsInput::IsPressedImpl(EGamepad gamepad, uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* previousState = &mPreviousGamepadStates[index];
        XINPUT_STATE* currentState = &mCurrentGamepadStates[index];
        
        if (gamepad == EGamepad::BUTTON_LT) {
            bool isPressedPrevious = previousState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            bool isPressedCurrent = currentState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            return !isPressedPrevious && isPressedCurrent;
        }

        if (gamepad == EGamepad::BUTTON_RT) {
            bool isPressedPrevious = previousState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            bool isPressedCurrent = currentState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            return !isPressedPrevious && isPressedCurrent;
        }

        uint16_t windowsGamepad = EngineToWindowsGamepad(gamepad);
        bool isPressedPrevious = previousState->Gamepad.wButtons & windowsGamepad; 
        bool isPressedCurrent = currentState->Gamepad.wButtons & windowsGamepad; 
        return !isPressedPrevious && isPressedCurrent;
    }

    bool WindowsInput::IsHeldImpl(EGamepad gamepad, uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* previousState = &mPreviousGamepadStates[index];
        XINPUT_STATE* currentState = &mCurrentGamepadStates[index];
        
        if (gamepad == EGamepad::BUTTON_LT) {
            bool isPressedPrevious = previousState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            bool isPressedCurrent = currentState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            return isPressedPrevious && isPressedCurrent;
        }

        if (gamepad == EGamepad::BUTTON_RT) {
            bool isPressedPrevious = previousState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            bool isPressedCurrent = currentState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            return isPressedPrevious && isPressedCurrent;
        }

        uint16_t windowsGamepad = EngineToWindowsGamepad(gamepad);
        bool isPressedPrevious = previousState->Gamepad.wButtons & windowsGamepad; 
        bool isPressedCurrent = currentState->Gamepad.wButtons & windowsGamepad; 
        return isPressedPrevious && isPressedCurrent;
    }

    bool WindowsInput::IsReleasedImpl(EGamepad gamepad, uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        XINPUT_STATE* previousState = &mPreviousGamepadStates[index];
        XINPUT_STATE* currentState = &mCurrentGamepadStates[index];
        
        if (gamepad == EGamepad::BUTTON_LT) {
            bool isPressedPrevious = previousState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            bool isPressedCurrent = currentState->Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            return isPressedPrevious && !isPressedCurrent;
        }

        if (gamepad == EGamepad::BUTTON_RT) {
            bool isPressedPrevious = previousState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            bool isPressedCurrent = currentState->Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; 
            return isPressedPrevious && !isPressedCurrent;
        }

        uint16_t windowsGamepad = EngineToWindowsGamepad(gamepad);
        bool isPressedPrevious = previousState->Gamepad.wButtons & windowsGamepad; 
        bool isPressedCurrent = currentState->Gamepad.wButtons & windowsGamepad; 
        return isPressedPrevious && !isPressedCurrent;
    }

    EInputState WindowsInput::GetStateImpl(EGamepad gamepad, uint8_t index) {
        VI_ASSERT(index < XUSER_MAX_COUNT && "Invalid gamepad index, max index is 3");
        if (IsPressed(gamepad, index))      return EInputState::PRESSED;
        if (IsHeld(gamepad, index))         return EInputState::HELD;
        if (IsReleased(gamepad, index))     return EInputState::RELEASED;
        return EInputState::NONE;
    }

    void WindowsInput::UpdateKeyboardStates() {
        GetKeyboardState(mCurrentStates);
    }

    void WindowsInput::UpdateMouseStates() {
        uint8_t leftButton = mMouseButtonMap[EMouseButton::BUTTON_LEFT];
        uint8_t rightButton = mMouseButtonMap[EMouseButton::BUTTON_RIGHT];
        uint8_t middleButton = mMouseButtonMap[EMouseButton::BUTTON_MIDDLE];
        uint8_t backButton = mMouseButtonMap[EMouseButton::BUTTON_BACK];
        uint8_t forwardButton = mMouseButtonMap[EMouseButton::BUTTON_FORWARD];
        mCurrentStates[leftButton] = GetKeyState(leftButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[rightButton] = GetKeyState(rightButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[middleButton] = GetKeyState(middleButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[backButton] = GetKeyState(backButton) & 0x800 ? 0x80 : 0;
        mCurrentStates[forwardButton] = GetKeyState(forwardButton) & 0x800 ? 0x80 : 0;
    }

    void WindowsInput::UpdateGamepadStates() {
        for (uint8_t index = 0; index < XUSER_MAX_COUNT; ++index) {
            memcpy(&mPreviousGamepadStates[index], &mCurrentGamepadStates[index], sizeof(XINPUT_STATE));
            memset(&mCurrentGamepadStates[index], 0, sizeof(XINPUT_STATE));
            XInputGetState(index, &mCurrentGamepadStates[index]);
        }
    }
}