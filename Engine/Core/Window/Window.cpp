#include"Window.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(Window)

    Window::Window(uint16_t width, uint16_t height, const std::string& title) {
        mConfiguration.Width = width;
        mConfiguration.Height = height;
        mConfiguration.Title = title;
    }

    Window::Window(const WindowConfiguration& windowConfig) : mConfiguration(windowConfig) {

    }
}