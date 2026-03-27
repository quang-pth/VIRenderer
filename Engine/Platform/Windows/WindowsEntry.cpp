#include"Core/Application.h"
#include"Core/Logger/Logger.h"

#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
    VIEngine::Application* application = VIEngine::CreateApplication();

    VIEngine::Logger::Init();
    
    if (application->Init()) {
        application->Run();
    }
    application->Shutdown();
    VI_FREE_MEMORY(application);

    return 0;
}