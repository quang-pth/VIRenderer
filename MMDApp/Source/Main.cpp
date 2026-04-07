#include<Core/Application.h>
#include<Core/Logger/Logger.h>
#include"Layer/GameplayLayer.h"

class MMDApp : public VIEngine::Application {
public:
    MMDApp(const VIEngine::ApplicationConfiguration& appConfig) : VIEngine::Application(appConfig) {
        // TODO: Use a manager to create a layer
        mGameplayLayer = new GameplayLayer();
    }

    virtual void OnInitClient() override {
        LOG_INFO("Init Client");
        PushLayer(mGameplayLayer);
    }
    
    virtual void OnShutdownClient() override {
        LOG_INFO("Shutdown Client");
        PopLayer(mGameplayLayer);
        VI_FREE_MEMORY(mGameplayLayer);
    }
private:
    GameplayLayer* mGameplayLayer;
};

VIEngine::Application* VIEngine::CreateApplication() {
    VIEngine::ApplicationConfiguration appConfig = {};
    appConfig.WindowConfig.Width = 640;
    appConfig.WindowConfig.Height = 360;
    appConfig.WindowConfig.Title = "MMD Application";
    return new MMDApp(appConfig);
}