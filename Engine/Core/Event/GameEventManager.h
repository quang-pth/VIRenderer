#pragma once

#include"Core/Event/EventContext.h"
#include"Core/Event/EventAction.h"
#include"Core/Type/String/StringID.h"

namespace VIEngine {
    class VI_API GameEventManager {
    public:
        GameEventManager();
        ~GameEventManager();
        void ExecuteEvent(const EventContext& eventContext);
        void DispatchEvent(const EventContext& eventContext);
        void ProcessEvents();

        EventActionHandle RegisterEventListener(const std::string& eventName, const EventAction<EventContext>& eventAction);
        void UnregisterEventListener(const std::string& eventName, EventActionHandle actionHandle);
        void ClearEventListeners();
    private:
        std::priority_queue<EventContext> mEventQueue;
        std::unordered_map<StringID, EventActionList<EventContext>> mActionMap;
        EventActionHandle mTotalListener;
    };
}