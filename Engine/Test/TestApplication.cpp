#include"Core/Application.h"
#include <gtest/gtest.h>

#define TESTAPP

class TestApplication : public VIEngine::Application {
public:
    TestApplication(const VIEngine::ApplicationConfiguration& appConfig) : VIEngine::Application(appConfig) {}
    ~TestApplication() {}
    virtual bool Init() override { return true; }
    virtual void Run() override {}
    virtual void Shutdown() override {}
    virtual void OnInitClient() override {}
    virtual void OnShutdownClient() override {}
};

VIEngine::Application* VIEngine::CreateApplication() {
    VIEngine::ApplicationConfiguration appConfig = {};
    appConfig.WindowConfig.Width = 640;
    appConfig.WindowConfig.Height = 360;
    appConfig.WindowConfig.Title = _T("Test Application");
    return new TestApplication(appConfig);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}