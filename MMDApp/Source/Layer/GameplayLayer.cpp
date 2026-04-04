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

void GameplayLayer::OnDetach() {

}

