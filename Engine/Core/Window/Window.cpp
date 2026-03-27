#include"Window.h"

namespace VIEngine {
    Window::Window(uint16_t width, uint16_t height, const std::string& title) {
        mConfiguration.Width = width;
        mConfiguration.Height = height;
        mConfiguration.Title = title;
    }

    Window::Window(const WindowConfiguration& windowConfig) : mConfiguration(windowConfig) {

    }
}