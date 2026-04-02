#pragma once

#include"Core/Window/Window.h"
#include"Core/Application.h"
#include<Windows.h>

namespace VIEngine {
    class VI_API WindowsWindow : public Window {
    public:
        WindowsWindow() = default;
        WindowsWindow(uint16_t width, uint16_t height, const std::string& title);
        WindowsWindow(const WindowConfiguration& windowConfig);
        virtual bool Init() override;
        virtual void Update() override;
        virtual void Close() override;
        virtual void Shutdown() override;
    private:
        HWND mHWND;
        MSG mMessage;
    };
}