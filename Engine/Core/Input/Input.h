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
        // キーボードステート取得用メソッド
        static uint8_t GetValue(EKeyCode keyCode) { return sInstance->GetValueImpl(keyCode); }
        static VI_FORCE_INLINE bool IsPressed(EKeyCode keyCode) { return sInstance->IsPressedImpl(keyCode); }
        static VI_FORCE_INLINE bool IsHeld(EKeyCode keyCode) { return sInstance->IsHeldImpl(keyCode); }
        static VI_FORCE_INLINE bool IsReleased(EKeyCode keyCode) { return sInstance->IsReleasedImpl(keyCode); }
        static VI_FORCE_INLINE EInputState GetState(EKeyCode keyCode) { return sInstance->GetStateImpl(keyCode); }
        // マウス取得用メソッド
        static uint8_t GetValue(EMouseButton mouseButton) { return sInstance->GetValueImpl(mouseButton); }
        static VI_FORCE_INLINE bool IsPressed(EMouseButton mouseButton) { return sInstance->IsPressedImpl(mouseButton); }
        static VI_FORCE_INLINE bool IsHeld(EMouseButton mouseButton) { return sInstance->IsHeldImpl(mouseButton); }
        static VI_FORCE_INLINE bool IsReleased(EMouseButton mouseButton) { return sInstance->IsReleasedImpl(mouseButton); }
        static VI_FORCE_INLINE EInputState GetState(EMouseButton mouseButton) { return sInstance->GetStateImpl(mouseButton); }
        /*
            コントローラーのボタンの値を取得するメソッド。値は0か1で、0は非押下、1は押下を表す。
            LT、RT、スティックのボタンは常に0を返す。
            これらの入力はGetLeftTriggerValueやGetRightTriggerValueやGetHorizontalAxisValueやGetVerticalAxisValueで取得する必要がある。
        */
        static uint8_t GetValue(uint8_t index, EGamepad gamepad) { return sInstance->GetValueImpl(index, gamepad); }
        // コントローラーの左トリガーの値を取得するメソッド。値は0.0fから1.0fの範囲で、0.0fは非押下、1.0fは完全に押下を表す。
        static float GetLeftTriggerValue(uint8_t index = 0) { return sInstance->GetLeftTriggerValueImpl(index); }
        // コントローラーの右トリガーの値を取得するメソッド。値は0.0fから1.0fの範囲で、0.0fは非押下、1.0fは完全に押下を表す。
        static float GetRightTriggerValue(uint8_t index = 0) { return sInstance->GetRightTriggerValueImpl(index); }
        // コントローラーの左スティックの横軸の値を取得するメソッド。値は-1.0fから1.0fの範囲で、-1.0fは完全に左、1.0fは完全に右を表す。
        static float GetLeftThumbStickXValue(uint8_t index = 0) { return sInstance->GetLeftThumbStickXValueImpl(index); }
        // コントローラーの右スティックの横軸の値を取得するメソッド。値は-1.0fから1.0fの範囲で、-1.0fは完全に左、1.0fは完全に右を表す。
        static float GetRightThumbStickXValue(uint8_t index = 0) { return sInstance->GetRightThumbStickXValueImpl(index); }
        // コントローラーの左スティックの縦軸の値を取得するメソッド。値は-1.0fから1.0fの範囲で、-1.0fは完全に下、1.0fは完全に上を表す。
        static float GetLeftThumbStickYValue(uint8_t index = 0) { return sInstance->GetLeftThumbStickYValueImpl(index); }
        // コントローラーの右スティックの縦軸の値を取得するメソッド。値は-1.0fから1.0fの範囲で、-1.0fは完全に下、1.0fは完全に上を表す。
        static float GetRightThumbStickYValue(uint8_t index = 0) { return sInstance->GetRightThumbStickYValueImpl(index); }
        static VI_FORCE_INLINE bool IsPressed(uint8_t index, EGamepad gamepad) { return sInstance->IsPressedImpl(index, gamepad); }
        static VI_FORCE_INLINE bool IsHeld(uint8_t index, EGamepad gamepad) { return sInstance->IsHeldImpl(index, gamepad); }
        static VI_FORCE_INLINE bool IsReleased(uint8_t index, EGamepad gamepad) { return sInstance->IsReleasedImpl(index, gamepad); }
        static VI_FORCE_INLINE EInputState GetState(uint8_t index, EGamepad gamepad) { return sInstance->GetStateImpl(index, gamepad); }
    private:
        static Input* Create();
    private:
        static Input* sInstance;
        static std::mutex sMutex;
    public:
        virtual ~Input() = default;
        void Update();
    protected:
        // キーボードステート取得用メソッド
        virtual uint8_t GetValueImpl(EKeyCode keyCode) = 0;
        virtual bool IsPressedImpl(EKeyCode keyCode) = 0;
        virtual bool IsHeldImpl(EKeyCode keyCode) = 0;
        virtual bool IsReleasedImpl(EKeyCode keyCode) = 0;
        virtual EInputState GetStateImpl(EKeyCode keyCode) = 0;
        // マウス取得用メソッド
        virtual uint8_t GetValueImpl(EMouseButton keyCode) = 0;
        virtual bool IsPressedImpl(EMouseButton keyCode) = 0;
        virtual bool IsHeldImpl(EMouseButton keyCode) = 0;
        virtual bool IsReleasedImpl(EMouseButton keyCode) = 0;
        virtual EInputState GetStateImpl(EMouseButton keyCode) = 0;
        // コントローラー取得用メソッド
        virtual uint8_t GetValueImpl(uint8_t index, EGamepad gamepad) = 0;
        virtual float GetLeftTriggerValueImpl(uint8_t index) = 0;
        virtual float GetRightTriggerValueImpl(uint8_t index) = 0;
        virtual float GetLeftThumbStickXValueImpl(uint8_t index) = 0;
        virtual float GetRightThumbStickXValueImpl(uint8_t index) = 0;
        virtual float GetLeftThumbStickYValueImpl(uint8_t index) = 0;
        virtual float GetRightThumbStickYValueImpl(uint8_t index) = 0;
        virtual bool IsPressedImpl(uint8_t index, EGamepad gamepad) = 0;
        virtual bool IsHeldImpl(uint8_t index, EGamepad gamepad) = 0;
        virtual bool IsReleasedImpl(uint8_t index, EGamepad gamepad) = 0;
        virtual EInputState GetStateImpl(uint8_t index, EGamepad gamepad) = 0;
    protected:
        Input();
        virtual void UpdateKeyboardStates() = 0;
        virtual void UpdateMouseStates() = 0;
        virtual void UpdateGamepadStates() = 0;
    protected:
        uint8_t mPreviousStates[256];
        uint8_t mCurrentStates[256];
    };
}