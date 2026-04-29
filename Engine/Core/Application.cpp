#include"Application.h"
#include"Core/Logger/Logger.h"
#include"Core/Input/Input.h"

#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter = mLayerStack.rbegin(); iter != mLayerStack.rend(); ++iter) {\
	if (!(*iter)->On##eventType(eventContext)) {\
		break;\
	}\
}

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
        mTimer.Reset();
        mTimer.Start();

        mInputEventManager.RegisterEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnKeyPressedEvent));
        mInputEventManager.RegisterEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(OnKeyReleasedEvent));
        mInputEventManager.RegisterEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonPressedEvent));
        mInputEventManager.RegisterEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonReleasedEvent));
        mInputEventManager.RegisterEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(OnMouseMovedEvent));
        mInputEventManager.RegisterEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OnMouseScrolledEvent));

        mGameEventManager.RegisterEventListener("ON_WINDOW_QUIT", BIND_EVENT_FUNCTION(OnWindowQuitEvent));

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
            mTimer.Update();

            float maxFPS = mWindow->GetMaxFPS();
            float deltaTime = 1.0f / maxFPS;
            // 最大FPSを超えるフレームレートにならないように、前回のフレームからの経過時間がdeltaTimeに達するまで待機する
            while(mTimer.GetDeltaTime() < deltaTime) {
                mTimer.UpdateCurrentTime();
            }

            mWindow->Update();
            input->Update();

            float currentDeltaTime = mTimer.GetDeltaTime();
            // フレームレートが極端に低い場合の対策として、前回のフレームからの経過時間がウィンドウの最大許容デルタタイムを超える場合は、複数回に分けて更新処理を行う
            while (currentDeltaTime > mWindow->GetMaxAllowedDeltaTime()) {
                for (auto iter = mLayerStack.begin(); iter != mLayerStack.end(); ++iter) {
                    Layer* layer = *iter;
                    layer->OnUpdate(mWindow->GetMaxAllowedDeltaTime() * layer->GetTimeScale());
                }
                currentDeltaTime -= mWindow->GetMaxAllowedDeltaTime();
            }
            // 通常の更新処理
            for (auto iter = mLayerStack.begin(); iter != mLayerStack.end(); ++iter) {
                Layer* layer = *iter;
                layer->OnUpdate(currentDeltaTime * layer->GetTimeScale());
            }

            mGameEventManager.ProcessEvents();

            // CORE_LOG_DEBUG("Frame {0}: {1}, FPS: {2}", mFrameCount, mTimer.GetDeltaTime(), 1.0f / mTimer.GetDeltaTime());

            ++mFrameCount;
        }

        OnShutdownClient();
    }
    
    void Application::Shutdown() {
        mWindow->Shutdown();
        mInputEventManager.ClearEventListeners();
        mGameEventManager.ClearEventListeners();
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

    bool Application::OnKeyPressedEvent(const KeyPressedEvent& keyEvent) {
        if (keyEvent.GetKey() == EKeyCode::ESCAPE) {
            mIsRunning = false;
            mWindow->Close();
            return false;
        }

        DISPATCH_LAYER_EVENT(KeyPressedEvent, keyEvent);
        
        return false;
    }
    
    bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is released", (int)keyEvent.GetKey());
        DISPATCH_LAYER_EVENT(KeyReleasedEvent, keyEvent);
        return false;
    }
    
    bool Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is pressed: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        DISPATCH_LAYER_EVENT(MouseButtonPressedEvent, mouseEvent);        
        return false;
    }
    
    bool Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is released: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        DISPATCH_LAYER_EVENT(MouseButtonReleasedEvent, mouseEvent);        
        return false;
    }

    bool Application::OnMouseMovedEvent(const MouseMovedEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse position: (x: {0}, y: {1}), offset: (x: {2}, y: {3})", 
            mouseEvent.GetPositionX(), 
            mouseEvent.GetPositionY(), 
            mouseEvent.GetOffsetX(), 
            mouseEvent.GetOffsetY()
        );
        DISPATCH_LAYER_EVENT(MouseMovedEvent, mouseEvent);        
        return false;
    }

    bool Application::OnMouseScrolledEvent(const MouseScrolledEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse scrolled: (Delta: {0})", mouseEvent.GetDelta());
        DISPATCH_LAYER_EVENT(MouseScrolledEvent, mouseEvent);
        return false;
    }

    bool Application::OnWindowQuitEvent(const EventContext& eventContext) {
        mIsRunning = false;
        return false;
    }
}