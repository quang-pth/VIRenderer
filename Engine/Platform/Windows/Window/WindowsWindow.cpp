#include"Platform/Windows/Window/WindowsWindow.h"
#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/Logger/Logger.h"
#include<windowsx.h>

namespace VIEngine {
    uint8_t mPreviousPressedState[256];
    uint8_t mCurrentPressedState[256];

    Window* Window::Create(uint16_t width, uint16_t height, const std::string& title) {
        return new WindowsWindow(width, height, title);
    }

    Window* Window::Create(const WindowConfiguration& windowConfig) {
        return new WindowsWindow(windowConfig);
    }

    LRESULT WindowProcedure(HWND wind, UINT msg, WPARAM wparam, LPARAM lparam) {
        Application& application = Application::Get();
        
        int16_t mouseX = GET_X_LPARAM(wparam);
        int16_t mouseY = GET_Y_LPARAM(wparam);
        switch (msg)
        {
            case WM_KEYDOWN:
                application.GetEventManager().ExecuteEvent({
                    "ON_KEY_PRESSED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineKeyCode(wparam)
                    }
                });
                break;
            case WM_KEYUP:
                application.GetEventManager().ExecuteEvent({
                    "ON_KEY_RELEASED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineKeyCode(wparam)
                    }
                });
                break;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_XBUTTONDOWN:
                application.GetEventManager().ExecuteEvent({
                    "ON_MOUSE_PRESSED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineMouseButton(wparam),
                        mouseX,
                        mouseY
                    }
                });
                break;
            case WM_LBUTTONUP:
                application.GetEventManager().ExecuteEvent({
                    "ON_MOUSE_RELEASED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineMouseButton(MK_LBUTTON),
                        mouseX,
                        mouseY
                    }
                });
                break;
            case WM_RBUTTONUP:
                application.GetEventManager().ExecuteEvent({
                    "ON_MOUSE_RELEASED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineMouseButton(MK_RBUTTON),
                        mouseX,
                        mouseY
                    }
                });
                break;
            case WM_MBUTTONUP:
                application.GetEventManager().ExecuteEvent({
                    "ON_MOUSE_RELEASED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineMouseButton(MK_MBUTTON),
                        mouseX,
                        mouseY
                    }
                });
                break;
            case WM_XBUTTONUP:
                application.GetEventManager().ExecuteEvent({
                    "ON_MOUSE_RELEASED",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        WindowsToEngineMouseButton(wparam),
                        mouseX,
                        mouseY
                    }
                });
                break;
            case WM_MOUSEMOVE:
                // application.GetEventManager().ExecuteEvent({
                //     "ON_MOUSE_MOVED",
                //     application.GetFrameCount(),
                //     EEventPriority::HIGH,
                //     {
                //         mouseX,
                //         mouseY
                //     }
                // });
                break;
            case WM_MOUSEWHEEL:
                application.GetEventManager().ExecuteEvent({
                    "ON_MOUSE_WHEEL",
                    application.GetFrameCount(),
                    EEventPriority::HIGH,
                    {
                        GET_WHEEL_DELTA_WPARAM(wparam)
                    }
                });
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

    WindowsWindow::WindowsWindow(uint16_t width, uint16_t height, const std::string& title) : 
        Window(width, height, title), mHWND(), mMessage() 
    {
        
    }

    WindowsWindow::WindowsWindow(const WindowConfiguration& windowConfig) : 
        Window(windowConfig), mHWND(), mMessage()  
    {
        memset(mPreviousPressedState, 0, sizeof(mPreviousPressedState));
        memset(mCurrentPressedState, 0, sizeof(mCurrentPressedState));
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
        
        mHWND = CreateWindow(
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

        if (mHWND == NULL) {
            std::string error = GetErrorString();
            MessageBoxA(NULL, error.c_str(), "Create Window Error", MB_ICONERROR);
            return false;
        }
	
    	ShowWindow(mHWND, SW_SHOW);
        
        return true;
    }

    void WindowsWindow::Update() {
        Application& application = Application::Get();
        EventContext quitEventContext{"ON_WINDOW_QUIT", application.GetFrameCount(), EEventPriority::CRITICAL, {}};

        if (PeekMessage(&mMessage, nullptr, 0, 0, PM_REMOVE)) {
			if (mMessage.message == WM_QUIT) {
				application.GetEventManager().ExecuteEvent(quitEventContext);
			}
			TranslateMessage(&mMessage);
			DispatchMessage(&mMessage);
		}

		if (mMessage.message == WM_QUIT) {
			application.GetEventManager().ExecuteEvent(quitEventContext);
		}
    }

    void WindowsWindow::Close() {
        DestroyWindow(mHWND);
    }
    
    void WindowsWindow::Shutdown() {
        CORE_LOG_INFO("Shutdown WindowsWindow");
    }
}