#pragma once

#include<Core/Layer/Layer.h>

namespace MMDApp {
	class GameplayLayer : public VIEngine::Layer {
	public:
		GameplayLayer();
		~GameplayLayer();

		virtual void OnAttach() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnDetach() override;
		virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& keyEvent) override;
		virtual bool OnKeyReleasedEvent(const VIEngine::KeyReleasedEvent& keyEvent) override;
		virtual bool OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& mouseEvent) override;
		virtual bool OnMouseButtonReleasedEvent(const VIEngine::MouseButtonReleasedEvent& mouseEvent) override;
		virtual bool OnMouseMovedEvent(const VIEngine::MouseMovedEvent& mouseEvent) override;
		virtual bool OnMouseScrolledEvent(const VIEngine::MouseScrolledEvent& mouseEvent) override;
	};
}