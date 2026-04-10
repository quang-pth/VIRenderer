#pragma once

#include"Core/pch.h"
#include"Core/Input/InputEvent.h"
#include"Core/Event/EventAction.h"

namespace VIEngine {
    class VI_API IInputEventAction {
        public:
            virtual ~IInputEventAction() = default;
            virtual bool Execute(const InputEvent*) = 0;
    };

    template<typename T>
    class VI_API InputEventAction : public IInputEventAction {
            VI_BASE_CLASS_ASSERT(InputEvent, T, "T must be an instance of InputEvent");
        public:
            InputEventAction() = default;
            InputEventAction(const EventAction<T>& eventAction) : mCallback(eventAction) {}
            ~InputEventAction() = default;

            VI_FORCE_INLINE virtual bool Execute(const InputEvent* inputEvent) override {
                return mCallback(*(T*)(inputEvent));
            }
        private:
            EventAction<T> mCallback;
    };
}