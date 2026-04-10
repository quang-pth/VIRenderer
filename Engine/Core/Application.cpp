#include"Application.h"
#include"Core/Logger/Logger.h"
#include"Core/Input/Input.h"

namespace VIEngine {
    Application* Application::sInstance = nullptr;

    Application& Application::Get() {
        return *sInstance;
    }

    Application::Application(const ApplicationConfiguration& appConfig) : mAppConfig(appConfig), mIsRunning(true), 
        mFrameCount(0), mTimer(), mGameEventManager(), mInputEventManager(), mLayerStack()
    {
        sInstance = this;
    }

    bool Application::Init() {
        mInputEventManager.RegisterEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnKeyPressed));
        mInputEventManager.RegisterEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(OnKeyReleased));
        mInputEventManager.RegisterEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonPressed));
        mInputEventManager.RegisterEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonReleased));
        mInputEventManager.RegisterEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(OnMouseMoved));
        mInputEventManager.RegisterEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OnMouseScrolled));

        mGameEventManager.RegisterEventListener("ON_WINDOW_QUIT", BIND_EVENT_FUNCTION(OnWindowQuit));

        mWindow.reset(Window::Create(mAppConfig.WindowConfig));
        VI_ASSERT(mWindow != nullptr && "Failed to create application window");

        if (!mWindow->Init()) {
            CORE_LOG_CRITICAL("Failed to init application window");
            return false;
        }

        CORE_LOG_INFO("Init application");
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

            mGameEventManager.ProcessEvents();
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

    bool Application::OnKeyPressed(const KeyPressedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is pressed", (int)keyEvent.GetKey());
        if (keyEvent.GetKey() == EKeyCode::ESCAPE) {
            mIsRunning = false;
            mWindow->Close();
            return false;
        }
        return true;
    }
    
    bool Application::OnKeyReleased(const KeyReleasedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is released", (int)keyEvent.GetKey());
        return true;
    }
    
    bool Application::OnMouseButtonPressed(const MouseButtonPressedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is pressed: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        return false;
    }
    
    bool Application::OnMouseButtonReleased(const MouseButtonReleasedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is released: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        return false;
    }

    bool Application::OnMouseMoved(const MouseMovedEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse position: (x: {0}, y: {1}), offset: (x: {2}, y: {3})", 
            mouseEvent.GetPositionX(), 
            mouseEvent.GetPositionY(), 
            mouseEvent.GetOffsetX(), 
            mouseEvent.GetOffsetY()
        );
        return false;
    }

    bool Application::OnMouseScrolled(const MouseScrolledEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse scrolled: (Delta: {0})", mouseEvent.GetDelta());
        return false;
    }

    bool Application::OnWindowQuit(const EventContext& eventContext) {
        mIsRunning = false;
        return false;
    }
}