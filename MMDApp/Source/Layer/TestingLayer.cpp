#include"Layer/TestingLayer.h"
#include<Core/Input/Input.h>
#include<Core/Logger/Logger.h>

namespace MMDApp {
    TestingLayer::TestingLayer() : VIEngine::Layer() {

    }

    TestingLayer::~TestingLayer() {

    }

    void TestingLayer::OnAttach() {
        
    }

    void TestingLayer::OnUpdate(float deltaTime) {
        TestKeyboard();
        TestMouse();
        TestGamepad();
    }

    void TestingLayer::OnDetach() {

    }

    void TestingLayer::TestKeyboard() {
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
        LOG_DEBUG("B key: (State: {0}, Value: {1})", (int)Input::GetState(EKeyCode::B), Input::GetValue(EKeyCode::B));
    }

    void TestingLayer::TestMouse() {
        using namespace VIEngine;

        LOG_DEBUG("Left mouse: (State: {0}, Value: {1})", (int)VIEngine::Input::GetState(VIEngine::EMouseButton::BUTTON_LEFT), VIEngine::Input::GetValue(VIEngine::EMouseButton::BUTTON_LEFT));

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

    void TestingLayer::TestGamepad() {
        using namespace VIEngine;
        // float leftThumbsX = Input::GetLeftThumbStickXValue();
        // float leftThumbsY = Input::GetLeftThumbStickYValue();
        // float rightThumbsX = Input::GetRightThumbStickXValue();
        // float rightThumbsY = Input::GetRightThumbStickYValue();
        // LOG_DEBUG("Left thumbstick: (x: {0}, y: {1})", leftThumbsX, leftThumbsY);
        // LOG_DEBUG("Right thumbstick: (x: {0}, y: {1})", rightThumbsX, rightThumbsY);

        // float leftTrigger = Input::GetLeftTriggerValue();
        // float rightTrigger = Input::GetRightTriggerValue();
        // LOG_DEBUG("Trigger: (Left: {0}, Right: {1})", leftTrigger, rightTrigger);

        // LOG_DEBUG("B button: (State: {0}, Value: {1})", (int)Input::GetState(EGamepad::BUTTON_B), Input::GetValue(EGamepad::BUTTON_B));

        if (Input::IsPressed(EGamepad::BUTTON_A)) {
            LOG_DEBUG("A is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_A)) {
            LOG_DEBUG("A is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_A)) {
            LOG_DEBUG("A is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_B)) {
            LOG_DEBUG("B is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_B)) {
            LOG_DEBUG("B is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_B)) {
            LOG_DEBUG("B is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_X)) {
            LOG_DEBUG("X is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_X)) {
            LOG_DEBUG("X is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_X)) {
            LOG_DEBUG("X is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_Y)) {
            LOG_DEBUG("Y is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_Y)) {
            LOG_DEBUG("Y is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_Y)) {
            LOG_DEBUG("Y is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_LB)) {
            LOG_DEBUG("LB is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_LB)) {
            LOG_DEBUG("LB is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_LB)) {
            LOG_DEBUG("LB is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_RB)) {
            LOG_DEBUG("RB is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_RB)) {
            LOG_DEBUG("RB is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_RB)) {
            LOG_DEBUG("RB is released");
        }
        if (Input::IsPressed(EGamepad::LEFT_THUMBSTICK)) {
            LOG_DEBUG("L3 is pressed");
        }
        if (Input::IsHeld(EGamepad::LEFT_THUMBSTICK)) {
            LOG_DEBUG("L3 is held");
        }
        if (Input::IsReleased(EGamepad::LEFT_THUMBSTICK)) {
            LOG_DEBUG("L3 is released");
        }
        if (Input::IsPressed(EGamepad::RIGHT_THUMBSTICK)) {
            LOG_DEBUG("R3 is pressed");
        }
        if (Input::IsHeld(EGamepad::RIGHT_THUMBSTICK)) {
            LOG_DEBUG("R3 is held");
        }
        if (Input::IsReleased(EGamepad::RIGHT_THUMBSTICK)) {
            LOG_DEBUG("R3 is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_LEFT)) {
            LOG_DEBUG("Left is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_LEFT)) {
            LOG_DEBUG("Left is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_LEFT)) {
            LOG_DEBUG("Left is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_RIGHT)) {
            LOG_DEBUG("Right is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_RIGHT)) {
            LOG_DEBUG("Right is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_RIGHT)) {
            LOG_DEBUG("Right is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_UP)) {
            LOG_DEBUG("Up is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_UP)) {
            LOG_DEBUG("Up is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_UP)) {
            LOG_DEBUG("Up is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_DOWN)) {
            LOG_DEBUG("Down is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_DOWN)) {
            LOG_DEBUG("Down is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_DOWN)) {
            LOG_DEBUG("Down is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_MENU)) {
            LOG_DEBUG("Menu is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_MENU)) {
            LOG_DEBUG("Menu is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_MENU)) {
            LOG_DEBUG("Menu is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_VIEW)) {
            LOG_DEBUG("View is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_VIEW)) {
            LOG_DEBUG("View is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_VIEW)) {
            LOG_DEBUG("View is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_LT)) {
            LOG_DEBUG("LT is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_LT)) {
            LOG_DEBUG("LT is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_LT)) {
            LOG_DEBUG("LT is released");
        }
        if (Input::IsPressed(EGamepad::BUTTON_RT)) {
            LOG_DEBUG("RT is pressed");
        }
        if (Input::IsHeld(EGamepad::BUTTON_RT)) {
            LOG_DEBUG("RT is held");
        }
        if (Input::IsReleased(EGamepad::BUTTON_RT)) {
            LOG_DEBUG("RT is released");
        }
    }
}