#include"Core/Application.h"
#include <gtest/gtest.h>

class TestApplication : public VIEngine::Application {
public:
    TestApplication() : VIEngine::Application() {}
    ~TestApplication() {}
    virtual bool Init() override { return true; }
    virtual void Run() override {
        // ::testing::InitGoogleTest();
        // RUN_ALL_TESTS();
    }
    virtual void Shutdown() override {}
    virtual void OnInitClient() override {}
    virtual void OnShutdownClient() override {}
};

VIEngine::Application* VIEngine::CreateApplication() {
    return new TestApplication();
}