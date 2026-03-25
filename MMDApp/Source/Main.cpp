#include<Core/Application.h>
#include<Core/Logger/Logger.h>

class MMDApp : public VIEngine::Application {
public:
    MMDApp(const VIEngine::ApplicationConfiguration& appConfig) : VIEngine::Application(appConfig) {
        
    }

    virtual void OnInitClient() override {
        LOG_TRACE("Init Client");
    }
    
    virtual void OnShutdownClient() override {
        LOG_TRACE("Shutdown Client");
    }
};

VIEngine::Application* VIEngine::CreateApplication() {
    VIEngine::ApplicationConfiguration appConfig = {};
    appConfig.Width = 1280;
    appConfig.Height = 720;
    appConfig.Title = "MMD Application";
    return new MMDApp(appConfig);
}