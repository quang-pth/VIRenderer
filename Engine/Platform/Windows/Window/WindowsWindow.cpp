#include"Platform/Windows/Window/WindowsWindow.h"
#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/Logger/Logger.h"
#include"Core/Input/InputEvent.h"
#include<windowsx.h>

namespace VIEngine {
    DEFINE_RTTI(WindowsWindow, Window::RunTimeType);

    Window* Window::Create(const WindowConfiguration& windowConfig) {
        return new WindowsWindow(windowConfig);
    }

    WindowsWindow::WindowsWindow(uint16_t width, uint16_t height, const std::string& title) : 
        Window(width, height, title), mHWND(), mMessage(), mMouseState(), mIsFirstMouse(true)
    {
    }

    WindowsWindow::WindowsWindow(const WindowConfiguration& windowConfig) : 
        Window(windowConfig), mHWND(), mMessage()  
    {
    }

    bool WindowsWindow::Init() {
        CORE_LOG_TRACE("Init WindowsWindow");

        WNDCLASSEX w = {};
        w.style = CS_HREDRAW | CS_VREDRAW;
        w.cbSize = sizeof(WNDCLASSEX);
        w.lpfnWndProc = (WNDPROC)WindowsWindow::WindowProcedure;
        w.lpszClassName = _T("WindowsWindow");
        w.hInstance = GetModuleHandleA(NULL);
        w.hCursor = LoadCursor(NULL, IDC_ARROW);

        if (!RegisterClassEx(&w)) {
            CORE_LOG_ERROR("Failed to register window class");
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
            this 
        );

        if (mHWND == NULL) {
            CORE_LOG_ERROR("Failed to create window");
            return false;
        }
	
    	ShowWindow(mHWND, SW_SHOW);
        
        return true;
    }

    void WindowsWindow::Update() {
        static Application& application = Application::Get();
        EventContext quitEventContext{"ON_WINDOW_QUIT", application.GetFrameCount(), EEventPriority::CRITICAL, {}};

        if (PeekMessage(&mMessage, nullptr, 0, 0, PM_REMOVE)) {
			if (mMessage.message == WM_QUIT) {
				application.GetGameEventManager().ExecuteEvent(quitEventContext);
			}
			TranslateMessage(&mMessage);
			DispatchMessage(&mMessage);
		}

		if (mMessage.message == WM_QUIT) {
			application.GetGameEventManager().ExecuteEvent(quitEventContext);
		}
    }

    void WindowsWindow::Close() {
        DestroyWindow(mHWND);
    }
    
    void WindowsWindow::Shutdown() {
        CORE_LOG_INFO("Shutdown WindowsWindow");
    }

    LRESULT WindowsWindow::WindowProcedure(HWND wind, UINT msg, WPARAM wparam, LPARAM lparam) {
        static Application& application = Application::Get();
        
        double mouseX = static_cast<double>(GET_X_LPARAM(lparam));
        double mouseY = static_cast<double>(GET_Y_LPARAM(lparam));
        switch (msg)
        {
            case WM_NCCREATE:
                {
                    CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lparam);
                    WindowsWindow* appWindow = reinterpret_cast<WindowsWindow*>(createStruct->lpCreateParams);
                    VI_ASSERT(appWindow != nullptr && "Failed to pass WindowsWindow pointer to HWND");
                    SetWindowLongPtr(wind, GWLP_USERDATA, (LONG_PTR)appWindow);
                }
                break;
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                {
                    uint8_t isRepeated = GetPreviousState(lparam);
                    if (!isRepeated) {
                        WPARAM mapKey = MapSystemKey(wparam, lparam);
                        application.GetInputEventManager().ExecuteEvent<KeyPressedEvent>({WindowsToEngineKeyCode(mapKey)});
                    }
                }
                break;
            case WM_KEYUP:
            case WM_SYSKEYUP:
                {
                    WPARAM mapKey = MapSystemKey(wparam, lparam);
                    application.GetInputEventManager().ExecuteEvent<KeyReleasedEvent>({WindowsToEngineKeyCode(mapKey)});
                }
                break;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_XBUTTONDOWN:
                SetCapture(wind);
                application.GetInputEventManager().ExecuteEvent<MouseButtonPressedEvent>({
                    WindowsToEngineMouseButton(wparam),
                    mouseX,
                    mouseY
                });
                break;
            case WM_LBUTTONUP:
                ReleaseCapture();
                application.GetInputEventManager().ExecuteEvent<MouseButtonReleasedEvent>({
                    WindowsToEngineMouseButton(MK_LBUTTON),
                    mouseX,
                    mouseY
                });
                break;
            case WM_RBUTTONUP:
                ReleaseCapture();
                application.GetInputEventManager().ExecuteEvent<MouseButtonReleasedEvent>({
                    WindowsToEngineMouseButton(MK_RBUTTON),
                    mouseX,
                    mouseY
                });
                break;
            case WM_MBUTTONUP:
                ReleaseCapture();
                application.GetInputEventManager().ExecuteEvent<MouseButtonReleasedEvent>({
                    WindowsToEngineMouseButton(MK_MBUTTON),
                    mouseX,
                    mouseY
                });
                break;
            case WM_XBUTTONUP:
                ReleaseCapture();
                application.GetInputEventManager().ExecuteEvent<MouseButtonReleasedEvent>({
                    WindowsToEngineMouseButton(wparam),
                    mouseX,
                    mouseY
                });
                break;
            case WM_MOUSEMOVE:
                {
                    WindowsWindow* appWindow = (WindowsWindow*)GetWindowLongPtr(wind, GWLP_USERDATA);
                    WindowsMouseState& mouseState = appWindow->GetMouseState();
                    // マウスが最初に動いたときは、移動量の計算のためにマウスの位置を初期化
                    if (appWindow->GetIsFirstMouse()) {
                        mouseState.PositionX = mouseX;
                        mouseState.PositionY = mouseY;
                        appWindow->SetIsFirstMouse(false);
                    }
                    // マウスの移動量を計算
                    mouseState.OffsetX = mouseX - mouseState.PositionX;
                    mouseState.OffsetY = mouseY - mouseState.PositionY;
                    application.GetInputEventManager().ExecuteEvent<MouseMovedEvent>({
                        mouseX,
                        mouseY,
                        mouseState.OffsetX,
                        mouseState.OffsetY
                    });
                    // マウスの位置を現行の位置に更新
                    mouseState.PositionX = mouseX;
                    mouseState.PositionY = mouseY;
                }
                break;
            case WM_MOUSEWHEEL:
                {
                    short delta = GET_WHEEL_DELTA_WPARAM(wparam);
                    application.GetInputEventManager().ExecuteEvent<MouseScrolledEvent>(static_cast<double>(delta) / WHEEL_DELTA);
                }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        }
        return DefWindowProcW(wind, msg, wparam, lparam);
    }

    WPARAM WindowsWindow::MapSystemKey(WPARAM wparam, LPARAM lparam) {
        bool isExtended = IsExtendedKey(lparam);

        if (wparam == VK_MENU) {
            if (isExtended) return VK_RMENU;
            return VK_LMENU;
            
        }
        if (wparam == VK_CONTROL) {
            if (isExtended) return VK_RCONTROL;
            return VK_LCONTROL;
        }
        
        if (wparam == VK_SHIFT) {
            uint32_t scancode = GetScanCode(lparam);
            return MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
        }

        return wparam;
    }

    LPARAM WindowsWindow::GetRepeatCount(LPARAM lparam) {
        return lparam & 0xffff;
    }

    uint32_t WindowsWindow::GetScanCode(LPARAM lparam) {
        return (lparam >> 16) & 0xff; 
    }

    bool WindowsWindow::IsExtendedKey(LPARAM lparam) {
        return (lparam >> 24) & 1;
    }

    uint8_t WindowsWindow::GetPreviousState(LPARAM lparam) {
        return (lparam >> 30) & 1;
    }

    uint8_t WindowsWindow::GetTransistionState(LPARAM lparam) {
        return (lparam >> 31) & 1;
    }
}