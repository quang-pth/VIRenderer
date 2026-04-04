#include"Core/Input/Input.h"

namespace VIEngine {
    Input* Input::sInstance = nullptr;
    std::mutex Input::sMutex{};

    void Input::Init() {
        std::lock_guard<std::mutex> lock(sMutex);
        if (sInstance != nullptr) return;
        sInstance = Input::Create();
    }
    
    void Input::Shutdown() {
        std::lock_guard<std::mutex> lock(sMutex);
        VI_FREE_MEMORY(sInstance);
    }

    Input* Input::Get() { return sInstance; }

    Input::Input() {
        memset(mPreviousStates, 0, sizeof(mPreviousStates));       
        memset(mCurrentStates, 0, sizeof(mCurrentStates));
    }

    void Input::Update() {
        memcpy(mPreviousStates, mCurrentStates, sizeof(mCurrentStates));
        memset(mCurrentStates, 0, sizeof(mCurrentStates));
        UpdateKeyboardStates();
        UpdateMouseStates();
    }
}