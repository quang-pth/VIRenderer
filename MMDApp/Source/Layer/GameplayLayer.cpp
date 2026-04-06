#include"GameplayLayer.h"
#include"Core/Input/Input.h"
#include"Core/Logger/Logger.h"

GameplayLayer::GameplayLayer() {
}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
}

void GameplayLayer::OnUpdate() {
    // TestKeyboard();
    // TestMouse();
    TestGamepad();
}

void GameplayLayer::OnDetach() {

}

void GameplayLayer::TestKeyboard() {
    using namespace VIEngine;
    if (Input::IsPressed(EKeyCode::A)) {
        LOG_DEBUG("A is pressed");
    }
    
    if (Input::IsHeld(EKeyCode::A)) {
        LOG_DEBUG("A is held");
    }

    if (Input::IsReleased(EKeyCode::A)) {
        LOG_DEBUG("A is released");
    }
    LOG_DEBUG("B key value {0}", Input::GetValue(EKeyCode::B));
}

void GameplayLayer::TestMouse() {
    using namespace VIEngine;

    if (Input::IsPressed(EMouseButton::BUTTON_LEFT)) {
        LOG_DEBUG("Left mouse is pressed");
    }
    
    if (Input::IsHeld(EMouseButton::BUTTON_LEFT)) {
        LOG_DEBUG("Left mouse is held");
    }

    if (Input::IsReleased(EMouseButton::BUTTON_LEFT)) {
        LOG_DEBUG("Left mouse is released");
    }

    if (Input::IsPressed(EMouseButton::BUTTON_RIGHT)) {
        LOG_DEBUG("Right mouse is pressed");
    }
    
    if (Input::IsHeld(EMouseButton::BUTTON_RIGHT)) {
        LOG_DEBUG("Right mouse is held");
    }

    if (Input::IsReleased(EMouseButton::BUTTON_RIGHT)) {
        LOG_DEBUG("Right mouse is released");
    }

    if (Input::IsPressed(EMouseButton::BUTTON_MIDDLE)) {
        LOG_DEBUG("Middle mouse is pressed");
    }
    
    if (Input::IsHeld(EMouseButton::BUTTON_MIDDLE)) {
        LOG_DEBUG("Middle mouse is held");
    }

    if (Input::IsReleased(EMouseButton::BUTTON_MIDDLE)) {
        LOG_DEBUG("Middle mouse is released");
    }
    
    if (Input::IsPressed(EMouseButton::BUTTON_BACK)) {
        LOG_DEBUG("Back mouse is pressed");
    }
    
    if (Input::IsHeld(EMouseButton::BUTTON_BACK)) {
        LOG_DEBUG("Back mouse is held");
    }

    if (Input::IsReleased(EMouseButton::BUTTON_BACK)) {
        LOG_DEBUG("Back mouse is released");
    }

    if (Input::IsPressed(EMouseButton::BUTTON_FORWARD)) {
        LOG_DEBUG("Forward mouse is pressed");
    }
    
    if (Input::IsHeld(EMouseButton::BUTTON_FORWARD)) {
        LOG_DEBUG("Forward mouse is held");
    }

    if (Input::IsReleased(EMouseButton::BUTTON_FORWARD)) {
        LOG_DEBUG("Forward mouse is released");
    }

    LOG_DEBUG("Right mouse key value {0}", Input::GetValue(EMouseButton::BUTTON_RIGHT));
}

void GameplayLayer::TestGamepad() {
    using namespace VIEngine;
    float leftThumbsX = Input::GetLeftThumbStickXValue();
    float leftThumbsY = Input::GetLeftThumbStickYValue();
    float rightThumbsX = Input::GetRightThumbStickXValue();
    float rightThumbsY = Input::GetRightThumbStickYValue();
    // LOG_TRACE("Left thumbstick: (x: {0}, y: {1})", leftThumbsX, leftThumbsY);
    // LOG_TRACE("Right thumbstick: (x: {0}, y: {1})", rightThumbsX, rightThumbsY);
    float leftTrigger = Input::GetLeftTriggerValue();
    float rightTrigger = Input::GetRightTriggerValue();
    LOG_TRACE("Trigger: (Left: {0}, Right: {1})", leftTrigger, rightTrigger);
}

