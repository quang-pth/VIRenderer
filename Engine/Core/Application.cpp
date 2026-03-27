#include"Application.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    Application* Application::sInstance = nullptr;

    const Application& Application::Get() {
        return *sInstance;
    }

    Application::Application(const ApplicationConfiguration& appConfig) : mAppConfig(appConfig) {
    }

    bool Application::Init() {
        CORE_LOG_INFO("Init application");
        sInstance = this;
        
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
    }
    
    void Application::Shutdown() {
        mWindow->Shutdown();
        CORE_LOG_INFO("Shutdown appplication");
    }
}