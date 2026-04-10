#pragma once
#include"pch.h"
#include"Core/Window/Window.h"
#include"Core/Time/Timer.h"
#include"Core/Event/GameEventManager.h"
#include"Core/Layer/LayerStack.h"
#include"Core/Input/InputEvent.h"
#include"Core/Input/InputEventManager.h"

namespace VIEngine {
    struct VI_API ApplicationConfiguration {
		WindowConfiguration WindowConfig;
	};

    class VI_API Application {
    public:
		static Application& Get();
	private:
		static Application* sInstance;
	public:
		virtual ~Application() = default;
		virtual bool Init();
        void Run();
        virtual void Shutdown();

        VI_FORCE_INLINE const ApplicationConfiguration& GetConfig() const { return mAppConfig; }
        VI_FORCE_INLINE GameEventManager& GetGameEventManager() { return mGameEventManager; }
        VI_FORCE_INLINE InputEventManager& GetInputEventManager() { return mInputEventManager; }
        VI_FORCE_INLINE size_t GetFrameCount() const { return mFrameCount; }

        virtual void OnInitClient() = 0;
        virtual void OnShutdownClient() = 0;
    protected:
        Application() = default;
        Application(const ApplicationConfiguration&);
        void PushLayer(Layer* layer, bool overlay = false);
        void PopLayer(Layer* layer, bool overlay = false);
    private:
        bool OnKeyPressed(const KeyPressedEvent& keyEvent);
        bool OnKeyReleased(const KeyReleasedEvent& keyEvent);
        bool OnMouseButtonPressed(const MouseButtonPressedEvent& mouseEvent);
        bool OnMouseButtonReleased(const MouseButtonReleasedEvent& mouseEvent);
        bool OnMouseMoved(const MouseMovedEvent& mouseEvent);
        bool OnMouseScrolled(const MouseScrolledEvent& mouseEvent);
        bool OnWindowQuit(const EventContext& eventContext);
    private:
        ApplicationConfiguration mAppConfig;
        std::unique_ptr<Window> mWindow;
        bool mIsRunning = true;
        size_t mFrameCount;
        Timer mTimer;
        GameEventManager mGameEventManager;
        InputEventManager mInputEventManager;
        LayerStack mLayerStack;
    };

    extern Application* CreateApplication();
}