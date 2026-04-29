#include"Layer/GameplayLayer.h"
#include<Core/Input/InputEvent.h>
#include<Core/Logger/Logger.h>

namespace MMDApp {
    GameplayLayer::GameplayLayer() {
    }

    GameplayLayer::~GameplayLayer() {

    }

    void GameplayLayer::OnAttach() {
    }

    void GameplayLayer::OnUpdate(float deltaTime) {
    }

    void GameplayLayer::OnDetach() {

    }

    bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is pressed", (int)keyEvent.GetKey());
        return true;
    }
    
    bool GameplayLayer::OnKeyReleasedEvent(const VIEngine::KeyReleasedEvent& keyEvent) {
        CORE_LOG_DEBUG("Key {0} is released", (int)keyEvent.GetKey());
        return false;
    }
    
    bool GameplayLayer::OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is pressed: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        return false;
    }
    
    bool GameplayLayer::OnMouseButtonReleasedEvent(const VIEngine::MouseButtonReleasedEvent& mouseEvent) {
        CORE_LOG_DEBUG("Mouse {0} is released: (x: {1}, y: {2})", (int)mouseEvent.GetButton(), mouseEvent.GetPositionX(), mouseEvent.GetPositionY());
        return false;
    }

    bool GameplayLayer::OnMouseMovedEvent(const VIEngine::MouseMovedEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse position: (x: {0}, y: {1}), offset: (x: {2}, y: {3})", 
            mouseEvent.GetPositionX(), 
            mouseEvent.GetPositionY(), 
            mouseEvent.GetOffsetX(), 
            mouseEvent.GetOffsetY()
        );
        return false;
    }

    bool GameplayLayer::OnMouseScrolledEvent(const VIEngine::MouseScrolledEvent& mouseEvent) {
        CORE_LOG_TRACE("Mouse scrolled: (Delta: {0})", mouseEvent.GetDelta());
        return false;
    }
}