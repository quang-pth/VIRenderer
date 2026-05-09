#include<Core/Application.h>
#include<Core/Logger/Logger.h>
#include"Layer/GameplayLayer.h"
#include"Layer/TestingLayer.h"

namespace MMDApp {
    class MMDApp : public VIEngine::Application {
    public:
        MMDApp(const VIEngine::ApplicationConfiguration& appConfig) : VIEngine::Application(appConfig), mGameplayLayer(), mTestingLayer() {
        }

        virtual void OnInitClient() override {
            LOG_INFO("Init Client");
            PushLayer(&mGameplayLayer);
            // PushLayer(&mTestingLayer);
        }
        
        virtual void OnShutdownClient() override {
            LOG_INFO("Shutdown Client");
            PopLayer(&mGameplayLayer);
            // PopLayer(&mTestingLayer);
        }
    private:
        GameplayLayer mGameplayLayer;
        TestingLayer mTestingLayer;
    };
}

VIEngine::Application* VIEngine::CreateApplication() {
    VIEngine::ApplicationConfiguration appConfig = {};
    appConfig.WindowConfig.Width = 640;
    appConfig.WindowConfig.Height = 360;
    appConfig.WindowConfig.Title = _T("MMD Application");
    return new MMDApp::MMDApp(appConfig);
}