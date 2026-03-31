#include"Core/Time/Timer.h"

namespace VIEngine {
    Timer::Timer() : mSecondsPerCount(0.0f), mDeltaTime(-1.0f), mBaseTime(0), mPausedTime(0), 
        mPreviousTime(0), mCurrentTime(0), mStopTime(0), mIsStopped(false)
    {
        int64_t countsPerSec;
        QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
        mSecondsPerCount = 1.0 / (double)countsPerSec;
    }

    Timer::~Timer() {
        
    }

    float Timer::GetTotalTimeSeconds() {
        // 停止中の場合、停止した瞬間から現在までの経過時間はカウントしません。
        // また、以前に一時停止があった場合、(mStopTime - mBaseTime) には
        // その停止時間が含まれてしまうため、これをカウントから除外する必要があります。
        // 正しい値を算出するために、mStopTime から累積停止時間を差し引きます。
        //                     |<-- 停止時間 (Paused Time) -->|
        // ----*---------------*-----------------------*------------*------> 時間 (Time)
        //  mBaseTime       mStopTime             startTime    mCurrentTime
        if (mIsStopped) {
            return (float)((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount;
        }

        // (mCurrTime - mBaseTime) には停止時間が含まれていますが、
        // これはカウントから除外したい時間です。
        // 正しい値を算出するために、mCurrentTimeから累積停止時間を差し引きます。
        //
        // 計算式: (mCurrentTime - mPausedTime) - mBaseTime
        //
        //                     |<-- 停止時間 (Paused Time) -->|
        // ----*---------------*-----------------*------------*------> 時間 (Time)
        //  mBaseTime       mStopTime       startTime     mCurrentTime
        return (float)((mCurrentTime - mPausedTime) - mBaseTime) * mSecondsPerCount;
    }

    void Timer::Reset() {
        int64_t currentTime;
        QueryPerformanceFrequency((LARGE_INTEGER*)&currentTime);

        mBaseTime = currentTime;
        mPreviousTime = currentTime;
        mStopTime = 0;
        mIsStopped = false;
    }

    void Timer::Start() {
        int64_t currentTime;
        QueryPerformanceFrequency((LARGE_INTEGER*)&currentTime);
        
        // 停止（Stop）と開始（Start）のペアの間に経過した時間を累積します。
        //
        //                     |<------- d (停止期間) ------->|
        // ----*---------------*-----------------------------*------------> 時間 (time)
        //  mBaseTime       mStopTime                     currentTime
        if (mIsStopped) {
            mPausedTime += currentTime - mStopTime;
            mPreviousTime = currentTime;
            mStopTime = 0;
            mIsStopped = false;
        }
    }

    void Timer::Stop() {
        if (mIsStopped) return;

        QueryPerformanceFrequency((LARGE_INTEGER*)&mStopTime);
        mIsStopped = true;
    }

    void Timer::Update() {
        if(mIsStopped)
        {
            mDeltaTime = 0.0;
            return;
        }

        int64_t currentTime;
        QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
        mCurrentTime = currentTime;

        mDeltaTime = (mCurrentTime - mPreviousTime) * mSecondsPerCount;
        mPreviousTime = mCurrentTime;

        // 非負（0以上）であることを保証します。DXSDKのCDXUTTimeの記述によると、
        // プロセッサが省電力モードに移行したり、別のプロセッサへスレッドが
        // スケジューリングされたりした場合、mDeltaTime が負の値になることがあります。
        if(mDeltaTime < 0.0)
        {
            mDeltaTime = 0.0;
        }
    }
}