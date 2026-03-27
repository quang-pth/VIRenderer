#pragma once
#include"pch.h"
#include"Core/Window/Window.h"

namespace VIEngine {
    struct VI_API ApplicationConfiguration {
		WindowConfiguration WindowConfig;
	};

    class VI_API Application {
    public:
		static const Application& Get();
	private:
		static Application* sInstance;
	public:
		virtual ~Application() = default;
		virtual bool Init();
        void Run();
        virtual void Shutdown();
        VI_FORCE_INLINE const ApplicationConfiguration& GetConfig() const { mAppConfig; }

        virtual void OnInitClient() = 0;
        virtual void OnShutdownClient() = 0;
    protected:
        Application() = default;
        Application(const ApplicationConfiguration&);
    private:
        ApplicationConfiguration mAppConfig;
        std::unique_ptr<Window> mWindow;
    };

    extern Application* CreateApplication();
}