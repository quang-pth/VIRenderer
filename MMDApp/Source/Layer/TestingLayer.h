#pragma once

#include<Core/Layer/Layer.h>

namespace MMDApp {
    class TestingLayer : public VIEngine::Layer {
    public:
        TestingLayer();
        ~TestingLayer();
        virtual void OnAttach() override;
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnDetach() override;
    private:
        void TestKeyboard();
        void TestMouse();
        void TestGamepad();
    };
}