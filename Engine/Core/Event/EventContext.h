#pragma once

#include"Core/Event/EventPriority.h"
#include"Core/Event/EventParam.h"

namespace VIEngine {
    class VI_API EventContext {
    public:
        EventContext() = default;
        EventContext(const EventContext&) = default;
        EventContext(const std::string& name, uint64_t frameTime, EEventPriority priority, const EventParamList& params);
        ~EventContext() = default;
        bool operator==(const EventContext& other) const;
        bool operator!=(const EventContext& other) const;
        bool operator<(const EventContext& other) const;
        bool operator>(const EventContext& other) const;
        VI_FORCE_INLINE const std::string& GetName() const { return mName; }
        VI_FORCE_INLINE uint64_t GetFrameTime() const { return mFrameTime; }
        VI_FORCE_INLINE EEventPriority GetPriority() const { return mPriority; }
        VI_FORCE_INLINE const EventParamList& GetParamList() const { return mParams; }
    private:
        std::string mName;
        uint64_t mFrameTime;
        EEventPriority mPriority;
        EventParamList mParams;
    };
}