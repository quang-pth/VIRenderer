#include"Core/Event/GameEventManager.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"

namespace VIEngine {
    GameEventManager::GameEventManager() : mEventQueue(), mActionMap(), mTotalListener(0) {

    }

    GameEventManager::~GameEventManager() {

    }

    void GameEventManager::ExecuteEvent(const EventContext& eventContext) {
        StringID eventNameID{eventContext.GetName().data()};
        if (mActionMap.count(eventNameID) > 0) {
            const EventActionList<EventContext>& actionList = mActionMap[eventNameID];
            for (const EventActionPair<EventContext>& eventActionPair : actionList) {
                const EventAction<EventContext>& eventAction = eventActionPair.second;
                if (!eventAction(eventContext)) {
                    break;
                }
            }
        }
        else {
            CORE_LOG_WARN("Event name not found: {0}", eventContext.GetName());
        }
    }

    void GameEventManager::DispatchEvent(const EventContext& eventContext) {
        mEventQueue.push(eventContext);
    }

    void GameEventManager::ProcessEvents() {
        while (!mEventQueue.empty()) {
            const EventContext& eventContext = mEventQueue.top();

            if (eventContext.GetFrameTime() < Application::Get().GetFrameCount()) break;

            ExecuteEvent(eventContext);
            mEventQueue.pop();
        }
    }

    EventActionHandle GameEventManager::RegisterEventListener(const std::string& eventName, const EventAction<EventContext>& eventAction) {
        StringID eventNameID{eventName.data()};
        mActionMap[eventNameID].emplace_back(std::make_pair(++mTotalListener, eventAction));
        return mTotalListener;
    }

    void GameEventManager::UnregisterEventListener(const std::string& eventName, EventActionHandle actionHandle) {
        StringID eventNameID{eventName.data()};
        if (mActionMap.count(eventNameID) > 0) {
            auto& actionList = mActionMap[eventNameID];
            auto iter = actionList.begin();
            for (; iter != actionList.end(); ++iter) {
                if ((*iter).first == actionHandle) break;
            }
            if (iter != actionList.end()) {
                actionList.erase(iter);
            }
        }
        else {
            CORE_LOG_WARN("Event name not found: {0}", eventName);
        }
    }
}