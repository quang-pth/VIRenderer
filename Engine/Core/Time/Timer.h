#pragma once

#include"Core/pch.h"
#include<chrono>

namespace VIEngine {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    class VI_API Timer {
    public:
        Timer();
        ~Timer();
        
        // Reset() が呼ばれてからの秒単位の経過時間の合計を返します。停止中の時間は含まれません。
        double GetTotalTime();
        
        // 前回のフレームからの秒単位の経過時間を返します。
        VI_FORCE_INLINE double GetDeltaTime() { return mDeltaTime; }

        void Reset();
        void Start();
        void Stop();
        void Update();
        void UpdateCurrentTime();
    private:
        double mDeltaTime;
        TimePoint mBaseTime;
        TimePoint mPausedTime;
        TimePoint mStopTime;
        TimePoint mCurrentTime;
        TimePoint mPreviousTime;
        bool mIsStopped;
    };
}