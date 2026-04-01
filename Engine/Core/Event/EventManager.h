#pragma once

#include"Core/Event/EventContext.h"
#include"Core/Event/EventAction.h"
#include"Core/Type/String/StringID.h"

namespace VIEngine {
    class VI_API EventManager {
    public:
        EventManager();
        ~EventManager();
        void ExecuteEvent(const EventContext& eventContext);
        void DispatchEvent(const EventContext& eventContext);
        void ProcessEvents();

        EventActionHandle RegisterEventListener(const std::string& eventName, const EventAction& eventAction);
        void UnregisterEventListener(const std::string& eventName, EventActionHandle actionHandle);
    private:
        std::priority_queue<EventContext> mEventQueue;
        std::unordered_map<StringID, EventActionList> mActionMap;
        EventActionHandle mTotalListener;
    };
}