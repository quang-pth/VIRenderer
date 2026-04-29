#pragma once

#include"Core/pch.h"
#include"Core/Event/EventAction.h"
#include"Core/Input/InputEvent.h"
#include"Core/Input/InputEventAction.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
    using InputEventActionList = std::vector<std::pair<EventActionHandle, IInputEventAction*>>;

    class VI_API InputEventManager {
    public:
        InputEventManager();
        ~InputEventManager();
        
        template<typename T>
        void ExecuteEvent(const T& inputEvent) {
            VI_BASE_CLASS_ASSERT(InputEvent, T, "T must be an instance of InputEvent");
            const RTTI& rtti = T::RunTimeType;
            StringID eventNameID = rtti.GetTypeNameID();
            if (mActionMap.count(eventNameID) > 0) {
                const InputEventActionList& actionList = mActionMap[eventNameID];
                for (const auto& eventActionPair : actionList) {
                    IInputEventAction* eventAction = eventActionPair.second;
                    if (!eventAction->Execute(&inputEvent)) {
                        break;
                    }
                }
            }
            else {
                CORE_LOG_WARN("Event name not found: {0}", rtti.GetTypeName());
            }
        }

        template<typename T>
        EventActionHandle RegisterEventListener(const EventAction<T>& eventCallback) {
            VI_BASE_CLASS_ASSERT(InputEvent, T, "T must be an instance of InputEvent");
            const RTTI& rtti = T::RunTimeType;
            StringID eventNameID = rtti.GetTypeNameID();
            if (mActionMap.count(eventNameID) < 0) {
                mTotalListenerMap[eventNameID] = 0;
            }
            // TODO: Allocate with Memory Management System
            IInputEventAction* eventAction = new InputEventAction<T>(eventCallback);
            mActionMap[eventNameID].push_back(std::make_pair(
                ++mTotalListenerMap[eventNameID],
                eventAction
            ));
            return mTotalListenerMap[eventNameID];
        }

        template<typename T>
        void UnregisterEventListener(EventActionHandle actionHandle) {
            VI_BASE_CLASS_ASSERT(InputEvent, T, "T must be an instance of InputEvent");
            const RTTI& rtti = T::RunTimeType;
            StringID eventNameID = rtti.GetTypeNameID();
            if (mActionMap.count(eventNameID) > 0) {
                InputEventActionList& actionList = mActionMap[eventNameID];
                auto iter = actionList.begin();
                for (; iter != actionList.end(); ++iter) {
                    EventActionHandle handle = iter->first;
                    if (handle == actionHandle) break;
                }
                if (iter != actionList.end()) {
                    VI_FREE_MEMORY(iter->second);
                    actionList.erase(iter);
                }
            }
            else {
                CORE_LOG_WARN("Event name not found: {0}", rtti.GetTypeName());
            }
        }

        void ClearEventListeners();
    private:
        std::unordered_map<StringID, InputEventActionList> mActionMap;
        std::unordered_map<StringID, EventActionHandle> mTotalListenerMap;
    };
}