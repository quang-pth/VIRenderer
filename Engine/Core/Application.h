#pragma once
#include"pch.h"
#include"Core/Window/Window.h"
#include"Core/Time/Timer.h"
#include"Core/Event/EventManager.h"
#include"Core/Layer/LayerStack.h"

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
        VI_FORCE_INLINE EventManager& GetEventManager() { return mEventManager; }
        VI_FORCE_INLINE size_t GetFrameCount() const { return mFrameCount; }

        virtual void OnInitClient() = 0;
        virtual void OnShutdownClient() = 0;
    protected:
        Application() = default;
        Application(const ApplicationConfiguration&);
        void PushLayer(Layer* layer, bool overlay = false);
        void PopLayer(Layer* layer, bool overlay = false);
    private:
        bool OnKeyPressed(const EventContext& eventContext);
        bool OnKeyReleased(const EventContext& eventContext);
        bool OnMousePressed(const EventContext& eventContext);
        bool OnMouseReleased(const EventContext& eventContext);
        bool OnMouseMoved(const EventContext& eventContext);
        bool OnMouseWheel(const EventContext& eventContext);
        bool OnWindowQuit(const EventContext& eventContext);
    private:
        ApplicationConfiguration mAppConfig;
        std::unique_ptr<Window> mWindow;
        bool mIsRunning = true;
        size_t mFrameCount;
        Timer mTimer;
        EventManager mEventManager;
        LayerStack mLayerStack;
    };

    extern Application* CreateApplication();
}