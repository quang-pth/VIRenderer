#pragma once

#include"Core/Window/Window.h"
#include"Core/Application.h"
#include"Core/Type/Object/RTTI.h"
#include<Windows.h>

namespace VIEngine {
    struct WindowsMouseState {
        double PositionX;
        double PositionY;
        double OffsetX;
        double OffsetY;
    };

    class VI_API WindowsWindow : public Window {
        DECLARE_RTTI
    private:
        static LRESULT WindowProcedure(HWND wind, UINT msg, WPARAM wparam, LPARAM lparam);

        /*
        Windowsのキーコードを拡張キーを変換、さらに左右のキーを区別する。拡張キーでないキーは、左右の区別がないため、そのまま返す
        例えば、Shiftキーは左と右で同じVK_SHIFTが送られてくるが、lparamの情報をもとに左右を区別している
        */
        static WPARAM MapSystemKey(WPARAM wparam, LPARAM lparam);

        // lparamからリピート回数を取得
        static LPARAM GetRepeatCount(LPARAM lparam);

        // lparamからスキャンコードを取得
        static uint32_t GetScanCode(LPARAM lparam);

        /*
        lparamから拡張キーかどうかを取得。
        1が返る場合は、拡張キーである。0が返る場合は、拡張キーでない。
        */
        static bool IsExtendedKey(LPARAM lparam);

        /*
        lparamからキーの前回の状態を取得。
        1が返る場合は、キーが押されている状態から離された状態に変化したことを表す。
        0が返る場合は、キーが離された状態から押されている状態に変化したことを表す。
        */
        static uint8_t GetPreviousState(LPARAM lparam);

        /*
        lparamからキーの遷移状態を取得。
        1が返る場合は、キーが離れた状態から押された状態に変化したことを表す。
        0が返る場合は、キーが押された状態から離された状態に変化したことを表す。
        */
        static uint8_t GetTransistionState(LPARAM lparam);
    public:
        WindowsWindow() = default;
        WindowsWindow(uint16_t width, uint16_t height, const std::string& title);
        WindowsWindow(const WindowConfiguration& windowConfig);
        virtual bool Init() override;
        virtual void Update() override;
        virtual void Close() override;
        virtual void Shutdown() override;
        VI_FORCE_INLINE WindowsMouseState& GetMouseState() { return mMouseState; }
        VI_FORCE_INLINE bool GetIsFirstMouse() const { return mIsFirstMouse; }
        VI_FORCE_INLINE void SetIsFirstMouse(bool value) { mIsFirstMouse = value; }
    private:
        HWND mHWND;
        MSG mMessage;
        WindowsMouseState mMouseState;
        bool mIsFirstMouse;
    };
}