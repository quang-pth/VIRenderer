#pragma once

// 参照: https://github.com/d3dcoder/d3d12book/blob/master/Common/GameTimer.h

#include"Core/pch.h"

namespace VIEngine {
    class VI_API Timer {
    public:
        Timer();
        ~Timer();
        
        // Reset() が呼ばれてからの経過時間の合計を返します。停止中の時間は含まれません。
        float GetTotalTimeSeconds();
        
        VI_FORCE_INLINE float GetDeltaTimeSeconds() { return mDeltaTime; }

        void Reset();
        void Start();
        void Stop();
        void Update();
    private:
        double mSecondsPerCount;
        double mDeltaTime;
        int64_t mBaseTime;
        int64_t mPausedTime;
        int64_t mStopTime;
        int64_t mPreviousTime;
        int64_t mCurrentTime;
        bool mIsStopped;
    };
}