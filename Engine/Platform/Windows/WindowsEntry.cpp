#include"Core/Application.h"
#include"Core/Logger/Logger.h"
#include"Core/Input/Input.h"

#ifndef TEST_APP
#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    #endif
    VIEngine::Logger::Init();
    VIEngine::Input::Init();

    VIEngine::Application* application = VIEngine::CreateApplication();
    
    if (application->Init()) {
        application->Run();
    }
    application->Shutdown();

    VIEngine::Input::Shutdown();

    VI_FREE_MEMORY(application);

    return 0;
}
#endif