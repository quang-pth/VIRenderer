#pragma once
#include"pch.h"

namespace VIEngine {
    struct VI_API ApplicationConfiguration {
		uint16_t Width, Height;
		const char* Title;
	};

    class VI_API Application {
    public:
		static Application& Get();
	private:
		static Application* sInstance;
	public:
		virtual ~Application() = default;
		bool Init();
        void Run();
        void Shutdown();
        VI_FORCE_INLINE const ApplicationConfiguration& GetConfig() const { mAppConfig; }

        virtual void OnInitClient() = 0;
        virtual void OnShutdownClient() = 0;
    protected:
        Application() = default;
        Application(const ApplicationConfiguration&);
    private:
        ApplicationConfiguration mAppConfig;
    };

    extern Application* CreateApplication();
}