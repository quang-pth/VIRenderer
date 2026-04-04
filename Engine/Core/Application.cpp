#include"Application.h"
#include"Core/Logger/Logger.h"
#include"Core/Input/Input.h"

namespace VIEngine {
    Application* Application::sInstance = nullptr;

    Application& Application::Get() {
        return *sInstance;
    }

    Application::Application(const ApplicationConfiguration& appConfig) : mAppConfig(appConfig), mIsRunning(true), 
        mFrameCount(0), mTimer(), mEventManager(), mLayerStack()
    {
        sInstance = this;
    }

    bool Application::Init() {
        CORE_LOG_INFO("Init application");

        mEventManager.RegisterEventListener("ON_WINDOW_QUIT", BIND_EVENT_FUNCTION(OnWindowQuit));
        mEventManager.RegisterEventListener("ON_KEY_PRESSED", BIND_EVENT_FUNCTION(OnKeyPressed));
        mEventManager.RegisterEventListener("ON_KEY_RELEASED", BIND_EVENT_FUNCTION(OnKeyReleased));
        mEventManager.RegisterEventListener("ON_MOUSE_PRESSED", BIND_EVENT_FUNCTION(OnMousePressed));
        mEventManager.RegisterEventListener("ON_MOUSE_RELEASED", BIND_EVENT_FUNCTION(OnMouseReleased));
        mEventManager.RegisterEventListener("ON_MOUSE_MOVED", BIND_EVENT_FUNCTION(OnMouseMoved));
        mEventManager.RegisterEventListener("ON_MOUSE_WHEEL", BIND_EVENT_FUNCTION(OnMouseWheel));

        mWindow.reset(Window::Create(mAppConfig.WindowConfig));
        VI_ASSERT(mWindow != nullptr && "Failed to create application window");

        if (!mWindow->Init()) {
            CORE_LOG_CRITICAL("Failed to init application window");
            return false;
        }

        return true;
    }

    void Application::Run() {
        CORE_LOG_INFO("Run appplication");

        OnInitClient();

        Input* input = Input::Get();
        while(mIsRunning) {
            ++mFrameCount;
            mWindow->Update();
            input->Update();

            for (auto iter = mLayerStack.begin(); iter != mLayerStack.end(); ++iter) {
                (*iter)->OnUpdate();
            }

            mEventManager.ProcessEvents();
        }

        OnShutdownClient();
    }
    
    void Application::Shutdown() {
        mWindow->Shutdown();
        CORE_LOG_INFO("Shutdown appplication");
    }

    void Application::PushLayer(Layer* layer, bool overlay) {
        layer->OnAttach();
        if (overlay) {
            mLayerStack.PushOverlay(layer);
        }
        else {
            mLayerStack.Push(layer);
        }
    }

    void Application::PopLayer(Layer* layer, bool overlay) {
        layer->OnDetach();
        if (overlay) {
            mLayerStack.PopOverlay(layer);
        }
        else {
            mLayerStack.Pop(layer);
        }
    }

    bool Application::OnKeyPressed(const EventContext& eventContext) {
        EKeyCode keyCode = std::get<EKeyCode>(eventContext.GetParamList()[0]);
        // CORE_LOG_TRACE("Key {0} is pressed at frame {1}", (int)keyCode, eventContext.GetFrameTime());
        if (keyCode == EKeyCode::ESCAPE) {
            mIsRunning = false;
            mWindow->Close();
            return false;
        }
        return true;
    }

    bool Application::OnKeyReleased(const EventContext& eventContext) {
        EKeyCode keyCode = std::get<EKeyCode>(eventContext.GetParamList()[0]);
        // CORE_LOG_TRACE("Key {0} is released at frame {1}", (int)keyCode, eventContext.GetFrameTime());
        return true;
    }

    bool Application::OnMousePressed(const EventContext& eventContext) {
        EMouseButton mouseButton = std::get<EMouseButton>(eventContext.GetParamList()[0]);
        // CORE_LOG_TRACE("Mouse {0} is pressed at frame {1}", (int)mouseButton, eventContext.GetFrameTime());
        return false;
    }

    bool Application::OnMouseReleased(const EventContext& eventContext) {
        EMouseButton mouseButton = std::get<EMouseButton>(eventContext.GetParamList()[0]);
        // CORE_LOG_TRACE("Mouse {0} is released at frame {1}", (int)mouseButton, eventContext.GetFrameTime());
        return false;
    }

    bool Application::OnMouseMoved(const EventContext& eventContext) {
        int16_t xPos = std::get<int>(eventContext.GetParamList()[0]);
        int16_t yPos = std::get<int>(eventContext.GetParamList()[1]);
        // CORE_LOG_TRACE("Mouse position: (x: {0}, y: {1})", xPos, yPos);
        return false;
    }

    bool Application::OnMouseWheel(const EventContext& eventContext) {
        int direction = std::get<int>(eventContext.GetParamList()[0]);
        // CORE_LOG_TRACE("Mouse wheel: {0}", direction);
        return false;
    }

    bool Application::OnWindowQuit(const EventContext& eventContext) {
        mIsRunning = false;
        return false;
    }
}