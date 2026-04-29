#pragma once

#include"Core/pch.h"
#include"Core/Input/InputEvent.h"

namespace VIEngine {
	class VI_API Layer {
	public:
		Layer(); 
        virtual ~Layer() = default;
		virtual void OnAttach();
		virtual void OnUpdate(float deltaTime);
		virtual void OnDetach();
		virtual bool OnKeyPressedEvent(const KeyPressedEvent& keyEvent);
        virtual bool OnKeyReleasedEvent(const KeyReleasedEvent& keyEvent);
        virtual bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent& mouseEvent);
        virtual bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& mouseEvent);
        virtual bool OnMouseMovedEvent(const MouseMovedEvent& mouseEvent);
        virtual bool OnMouseScrolledEvent(const MouseScrolledEvent& mouseEvent);

		VI_FORCE_INLINE float GetTimeScale() const { return mTimeScale; }
		VI_FORCE_INLINE void SetTimeScale(float value) { mTimeScale = value; }
	private:
		float mTimeScale;
	};

}