#include"Core/Layer/Layer.h"

namespace VIEngine {
    Layer::Layer() : mTimeScale(1.0f) {

    }

    void Layer::OnAttach() {

    }
    
    void Layer::OnUpdate(float deltaTime) {

    }

    void Layer::OnDetach() {

    }

    bool Layer::OnKeyPressedEvent(const KeyPressedEvent& keyEvent) {
        return true;
    }

    bool Layer::OnKeyReleasedEvent(const KeyReleasedEvent& keyEvent) {
        return true;
    }

    bool Layer::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& keyEvent) {
        return true;
    }

    bool Layer::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& keyEvent) {
        return true;
    }

    bool Layer::OnMouseMovedEvent(const MouseMovedEvent& keyEvent) {
        return true;
    }

    bool Layer::OnMouseScrolledEvent(const MouseScrolledEvent& keyEvent) {
        return true;
    }
}