#pragma once

#include"Core/Input/Input.h"

namespace VIEngine {
    class VI_API WindowsInput : public Input {
    public:
        WindowsInput();
        ~WindowsInput();
        virtual uint8_t GetValueImpl(EKeyCode keyCode) override;
        virtual bool IsPressedImpl(EKeyCode keyCode) override;
        virtual bool IsHeldImpl(EKeyCode keyCode) override;
        virtual bool IsReleasedImpl(EKeyCode keyCode) override;
        virtual EInputState GetStateImpl(EKeyCode keyCode) override;
        virtual uint8_t GetValueImpl(EMouseButton keyCode) override;
        virtual bool IsPressedImpl(EMouseButton keyCode) override;
        virtual bool IsHeldImpl(EMouseButton keyCode) override;
        virtual bool IsReleasedImpl(EMouseButton keyCode) override;
        virtual EInputState GetStateImpl(EMouseButton keyCode) override;
    protected:
        virtual void UpdateKeyboardStates() override;
        virtual void UpdateMouseStates() override;
    };
}