#pragma once

#include"Core/pch.h"
#include"Core/Input/KeyCode.h"
#include"Core/Type/Object/RTTI.h"

#define DEFINE_KEYCODE_EVENT_BODY(eventName) \
	public: \
		eventName(EKeyCode keyCode) : mKeyCode(keyCode) {} \
		VI_FORCE_INLINE bool IsKey(EKeyCode keyCode) const { return mKeyCode == keyCode; } \
		VI_FORCE_INLINE EKeyCode GetKey() const { return mKeyCode; } \
	private: \
		EKeyCode mKeyCode;
	
#define DEFINE_MOUSE_BUTTON_EVENT_BODY(eventName) \
	public: \
		eventName(EMouseButton button, double x, double y) : mButton(button), mPositionX(x), mPositionY(y) {} \
		VI_FORCE_INLINE bool IsButton(EMouseButton button) const { return mButton == button; } \
		VI_FORCE_INLINE EMouseButton GetButton() const { return mButton; } \
		VI_FORCE_INLINE double GetPositionX() const { return mPositionX; } \
		VI_FORCE_INLINE double GetPositionY() const { return mPositionY; } \
	private: \
		EMouseButton mButton; \
		double mPositionX; \
		double mPositionY;

namespace VIEngine {
	class VI_API InputEvent {
	public:
		virtual ~InputEvent() = default;
	};

	class VI_API WindowResizedEvent : public InputEvent {
		DECLARE_RTTI
	public:
		WindowResizedEvent(uint32_t width, uint32_t height) : mWidth(width), mHeight(height) {}
		VI_FORCE_INLINE uint32_t GetWidth() const { return mWidth; }
		VI_FORCE_INLINE uint32_t GetHeight() const { return mHeight; }
	private:
		uint32_t mWidth;
        uint32_t mHeight;
	};

	class VI_API KeyPressedEvent : public InputEvent {
		DECLARE_RTTI
		DEFINE_KEYCODE_EVENT_BODY(KeyPressedEvent)
	};

	class VI_API KeyHeldEvent : public InputEvent {
		DECLARE_RTTI
		DEFINE_KEYCODE_EVENT_BODY(KeyHeldEvent)
	};

	class VI_API KeyReleasedEvent : public InputEvent {
		DECLARE_RTTI
		DEFINE_KEYCODE_EVENT_BODY(KeyReleasedEvent)
	};

	class VI_API MouseMovedEvent : public InputEvent {
		DECLARE_RTTI
	public:
		MouseMovedEvent(double x, double y, double offsetX, double offsetY) : 
			mPositionX(x), mPositionY(y),
			mOffsetX(offsetX), mOffsetY(offsetY) {}
		VI_FORCE_INLINE double GetPositionX() const { return mPositionX; }
		VI_FORCE_INLINE double GetPositionY() const { return mPositionY; }
		VI_FORCE_INLINE double GetOffsetX() const { return mOffsetX; }
		VI_FORCE_INLINE double GetOffsetY() const { return mOffsetY; }
	private:
		double mPositionX, mPositionY;
		double mOffsetX, mOffsetY;
	};

	class VI_API MouseScrolledEvent : public InputEvent {
		DECLARE_RTTI
	public:
		MouseScrolledEvent(double delta) : mDelta(delta) {}
		// [-1, 1]の範囲で正規化されてい値を返す。
		// 正の値は上方向のスクロール、負の値は下方向のスクロールを表す。
		VI_FORCE_INLINE double GetDelta() const { return mDelta; }
	private:
		double mDelta;
	};

	class VI_API MouseButtonPressedEvent : public InputEvent {
		DECLARE_RTTI
		DEFINE_MOUSE_BUTTON_EVENT_BODY(MouseButtonPressedEvent)
	};

	class VI_API MouseButtonHeldEvent : public InputEvent {
		DECLARE_RTTI
		DEFINE_MOUSE_BUTTON_EVENT_BODY(MouseButtonHeldEvent)
	};
	
	class VI_API MouseButtonReleasedEvent : public InputEvent {
		DECLARE_RTTI
		DEFINE_MOUSE_BUTTON_EVENT_BODY(MouseButtonReleasedEvent)
	};
}