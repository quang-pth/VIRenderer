#pragma once

#include"Core/Input/Input.h"
#include<Xinput.h>

namespace VIEngine {
    const uint8_t TRIGGER_THRESHOLD_MAX = 0xff;
    const short THUMBSTICK_THRESHOLD_MAX = 0x7fff;
    const short THUMBSTICK_THRESHOLD_MIN = 0x8000;

    class VI_API WindowsInput : public Input {
    public:
        WindowsInput();
        ~WindowsInput();
    protected:
        // キーボードステート取得用メソッド
        virtual uint8_t GetValueImpl(EKeyCode keyCode) override;
        virtual bool IsPressedImpl(EKeyCode keyCode) override;
        virtual bool IsHeldImpl(EKeyCode keyCode) override;
        virtual bool IsReleasedImpl(EKeyCode keyCode) override;
        virtual EInputState GetStateImpl(EKeyCode keyCode) override;
        // マウス取得用メソッド
        virtual uint8_t GetValueImpl(EMouseButton keyCode) override;
        virtual bool IsPressedImpl(EMouseButton keyCode) override;
        virtual bool IsHeldImpl(EMouseButton keyCode) override;
        virtual bool IsReleasedImpl(EMouseButton keyCode) override;
        virtual EInputState GetStateImpl(EMouseButton keyCode) override;
        // コントローラー取得用メソッド
        virtual uint8_t GetValueImpl(EGamepad gamepad, uint8_t index) override;
        virtual float GetLeftTriggerValueImpl(uint8_t index) override;
        virtual float GetRightTriggerValueImpl(uint8_t index) override;
        virtual float GetLeftThumbStickXValueImpl(uint8_t index) override;
        virtual float GetRightThumbStickXValueImpl(uint8_t index) override;
        virtual float GetLeftThumbStickYValueImpl(uint8_t index) override;
        virtual float GetRightThumbStickYValueImpl(uint8_t index) override;
        virtual bool IsPressedImpl(EGamepad gamepad, uint8_t index) override;
        virtual bool IsHeldImpl(EGamepad gamepad, uint8_t index) override;
        virtual bool IsReleasedImpl(EGamepad gamepad, uint8_t index) override;
        virtual EInputState GetStateImpl(EGamepad gamepad, uint8_t index) override;
    protected:
        virtual void UpdateKeyboardStates() override;
        virtual void UpdateMouseStates() override;
        virtual void UpdateGamepadStates() override;
        template<typename T, typename R>
        VI_FORCE_INLINE float Normalize(T value, R range) { return value / static_cast<float>(range); }
    private:
        std::unordered_map<EMouseButton, uint8_t> mMouseButtonMap;
        XINPUT_STATE mPreviousGamepadStates[XUSER_MAX_COUNT];
        XINPUT_STATE mCurrentGamepadStates[XUSER_MAX_COUNT];
    };
}