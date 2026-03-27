#include"Platform/Windows/Window/WindowsWindow.h"
#include"Core/Logger/Logger.h"
#include<Windows.h>

namespace VIEngine {
    Window* Window::Create(uint16_t width, uint16_t height, const std::string& title) {
        return new WindowsWindow(width, height, title);
    }

    Window* Window::Create(const WindowConfiguration& windowConfig) {
        return new WindowsWindow(windowConfig);
    }

    LRESULT WindowProcedure(HWND wind, UINT msg, WPARAM wparam, LPARAM lparam) {
        switch (msg)
        {
            case WM_KEYDOWN:
                if (wparam == VK_ESCAPE) {
                    // TODO: Dispatch event to application
                    DestroyWindow(wind);
                }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        } 
        return DefWindowProcW(wind, msg, wparam, lparam);
    }  

    std::string GetErrorString() {
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0) {
            return std::string();
        }

        LPSTR messageBuffer = nullptr;

        size_t size = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, 
            errorMessageID, 
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
            (LPSTR)&messageBuffer, 
            0, 
            NULL
        );

        std::string message(messageBuffer, size);

        LocalFree(messageBuffer);

        return message;
    }

    WindowsWindow::WindowsWindow(uint16_t width, uint16_t height, const std::string& title) : Window(width, height, title) 
    {
        
    }

    WindowsWindow::WindowsWindow(const WindowConfiguration& windowConfig) : Window(windowConfig) {

    }

    bool WindowsWindow::Init() {
        CORE_LOG_TRACE("Init WindowsWindow");

        WNDCLASSEX w = {};
        w.style = CS_HREDRAW | CS_VREDRAW;
        w.cbSize = sizeof(WNDCLASSEX);
        w.lpfnWndProc = (WNDPROC)WindowProcedure;
        w.lpszClassName = _T("WindowsWindow");
        w.hInstance = GetModuleHandleA(NULL);
        w.hCursor = LoadCursor(NULL, IDC_ARROW);

        if (!RegisterClassEx(&w)) {
            std::string error = GetErrorString();
            MessageBoxA(NULL, error.c_str(), "Window Class Registration Error", MB_ICONERROR);
            return false;
        }

        RECT wrc = { 0, 0, mConfiguration.Width, mConfiguration.Height };
        AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, FALSE);
        
        HWND hwnd = CreateWindow(
            w.lpszClassName, 
            (mConfiguration.Title.c_str()),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            wrc.right - wrc.left,
            wrc.bottom - wrc.top,
            NULL,
            NULL,
            w.hInstance,
            NULL 
        );

        if (hwnd == NULL) {
            std::string error = GetErrorString();
            MessageBoxA(NULL, error.c_str(), "Create Window Error", MB_ICONERROR);
            return false;
        }
	
    	ShowWindow(hwnd, SW_SHOW);

        return true;
    }
    
    void WindowsWindow::Shutdown() {
        CORE_LOG_TRACE("Shutdown WindowsWindow");
    }
}