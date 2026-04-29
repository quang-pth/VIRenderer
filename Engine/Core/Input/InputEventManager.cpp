#include"Core/Input/InputEventManager.h"

namespace VIEngine {
    InputEventManager::InputEventManager() : mActionMap(), mTotalListenerMap() {

    }

    InputEventManager::~InputEventManager() {
        ClearEventListeners();
    }

    void InputEventManager::ClearEventListeners() {
        for (auto& pair : mActionMap) {
            for (auto iter : pair.second) {
                VI_FREE_MEMORY(iter.second);
            }
            pair.second.clear();
        }
        mActionMap.clear();
        mTotalListenerMap.clear();
    }
}