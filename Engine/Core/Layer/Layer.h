#pragma once

#include"Core/pch.h"
#include"Core/Input/InputEvent.h"

namespace VIEngine {
	class VI_API Layer {
	public:
		Layer() = default; 
        virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnUpdate() {}
		virtual void OnDetach() {}
		virtual bool OnKeyPressedEvent(const KeyPressedEvent& keyEvent) { return true; }
        virtual bool OnKeyReleasedEvent(const KeyReleasedEvent& keyEvent) { return true; }
        virtual bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent& mouseEvent) { return true; }
        virtual bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& mouseEvent) { return true; }
        virtual bool OnMouseMovedEvent(const MouseMovedEvent& mouseEvent) { return true; }
        virtual bool OnMouseScrolledEvent(const MouseScrolledEvent& mouseEvent) { return true; }
	};

}