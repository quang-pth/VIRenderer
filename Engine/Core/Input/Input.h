#pragma once

#include"Core/pch.h"
#include"Core/Input/KeyCode.h"
#include<mutex>

namespace VIEngine {
    class VI_API Input {
    public:
        static void Init();
        static void Shutdown();
        static Input* Get();
        static uint8_t GetValue(EKeyCode keyCode) { return sInstance->GetValueImpl(keyCode); }
        static VI_FORCE_INLINE bool IsPressed(EKeyCode keyCode) { return sInstance->IsPressedImpl(keyCode); }
        static VI_FORCE_INLINE bool IsHeld(EKeyCode keyCode) { return sInstance->IsHeldImpl(keyCode); }
        static VI_FORCE_INLINE bool IsReleased(EKeyCode keyCode) { return sInstance->IsReleasedImpl(keyCode); }
        static VI_FORCE_INLINE EKeyState GetState(EKeyCode keyCode) { return sInstance->GetStateImpl(keyCode); }
    private:
        static Input* Create();
    private:
        static Input* sInstance;
        static std::mutex sMutex;
    public:
        virtual ~Input() = default;
        virtual void Update();
        virtual uint8_t GetValueImpl(EKeyCode keyCode) = 0;
        virtual bool IsPressedImpl(EKeyCode keyCode) = 0;
        virtual bool IsHeldImpl(EKeyCode keyCode) = 0;
        virtual bool IsReleasedImpl(EKeyCode keyCode) = 0;
        virtual EKeyState GetStateImpl(EKeyCode keyCode) = 0;
    protected:
        Input();
    protected:
        uint8_t mPreviousStates[256];
        uint8_t mCurrentStates[256];
    };
}