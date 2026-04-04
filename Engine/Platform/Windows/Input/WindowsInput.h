#pragma once

#include"Core/Input/Input.h"

namespace VIEngine {
    class VI_API WindowsInput : public Input {
    public:
        WindowsInput();
        ~WindowsInput();
        virtual void Update();
        virtual uint8_t GetValueImpl(EKeyCode keyCode) override;
        virtual bool IsPressedImpl(EKeyCode keyCode) override;
        virtual bool IsHeldImpl(EKeyCode keyCode) override;
        virtual bool IsReleasedImpl(EKeyCode keyCode) override;
        virtual EKeyState GetStateImpl(EKeyCode keyCode) override;
    };
}