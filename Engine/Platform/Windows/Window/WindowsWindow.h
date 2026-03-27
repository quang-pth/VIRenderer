#pragma once

#include"Core/Window/Window.h"

namespace VIEngine {
    class VI_API WindowsWindow : public Window {
    public:
        WindowsWindow() = default;
        WindowsWindow(uint16_t width, uint16_t height, const std::string& title);
        WindowsWindow(const WindowConfiguration& windowConfig);
        virtual bool Init() override;
        virtual void Shutdown() override;
    };
}