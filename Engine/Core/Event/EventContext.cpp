#include"Core/Event/EventContext.h"

namespace VIEngine {
    EventContext::EventContext(const std::string& name, uint64_t frameTime, EEventPriority priority, const EventParamList& params)
        : mName(name), mFrameTime(frameTime), mParams(params), mPriority(priority) 
    {

    }

    bool EventContext::operator==(const EventContext& other) const {
        if (mParams.size() != other.mParams.size()) return false;

        size_t numsParam = mParams.size();
        for (size_t i = 0; i < numsParam; ++i) {
            const auto& lhs = mParams[i];
            const auto& rhs = other.mParams[i];

            if (lhs.index() != rhs.index()) return false;

            bool isSameValue = std::visit([](auto&& arg1, auto&& arg2) -> bool {
                // 正規化された型を取得
                using T = std::decay_t<decltype(arg1)>;
                using U = std::decay_t<decltype(arg2)>; 

                if constexpr (std::is_same_v<T, U>) {
                    return arg1 == arg2;
                }
                return false;
            }, lhs, rhs);

            if (!isSameValue) return false;
        }

        return mName == other.mName && mFrameTime == other.mFrameTime && mPriority == other.mPriority;
    }

    bool EventContext::operator!=(const EventContext& other) const { 
        return !(*this == other);
    }

    bool EventContext::operator<(const EventContext& other) const {
        return (mFrameTime < other.mFrameTime) || (mFrameTime == other.mFrameTime && mPriority < other.mPriority);
    }

    bool EventContext::operator>(const EventContext& other) const {
        return (mFrameTime > other.mFrameTime) || (mFrameTime == other.mFrameTime && mPriority > other.mPriority);
    }
}