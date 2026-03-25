#include"Application.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    Application* Application::sInstance = nullptr;

    Application& Application::Get() {
        return *sInstance;
    }

    Application::Application(const ApplicationConfiguration& appConfig) : mAppConfig(appConfig) {
    }

    bool Application::Init() {
        Logger::Init();
        CORE_LOG_INFO("Init application");
        return true;
    }

    void Application::Run() {
        CORE_LOG_INFO("Run appplication");
    }
    
    void Application::Shutdown() {
        CORE_LOG_INFO("Shutdown appplication");
    }
}