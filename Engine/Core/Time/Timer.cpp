#include"Core/Time/Timer.h"

namespace VIEngine {
    Timer::Timer() : mDeltaTime(-1.0f), mBaseTime(), mPausedTime(), 
        mStopTime(), mCurrentTime(), mPreviousTime(), mIsStopped(false)
    {
    }

    Timer::~Timer() {
        
    }

    float Timer::GetTotalTime() {
        // 停止中の場合、停止した瞬間から現在までの経過時間はカウントしません。
        // また、以前に一時停止があった場合、(mStopTime - mBaseTime) には
        // その停止時間が含まれてしまうため、これをカウントから除外する必要があります。
        // 正しい値を算出するために、mStopTime から累積停止時間を差し引きます。
        //                     |<-- 停止時間 (Paused Time) -->|
        // ----*---------------*-----------------------*------------*------> 時間 (Time)
        //  mBaseTime       mStopTime             startTime    mCurrentTime
        if (mIsStopped) {
            return std::chrono::duration<float>((mStopTime.time_since_epoch() - mPausedTime.time_since_epoch()) - mBaseTime.time_since_epoch()).count();
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
        return std::chrono::duration<float>((mCurrentTime.time_since_epoch() - mPausedTime.time_since_epoch()) - mBaseTime.time_since_epoch()).count();
    }

    void Timer::Reset() {
        mBaseTime = Clock::now();
        mPreviousTime = Clock::now();
        mStopTime = {};
        mIsStopped = false;
    }

    void Timer::Start() {
        if (!mIsStopped) return;
        // 停止（Stop）と開始（Start）のペアの間に経過した時間を累積します。
        //
        //                     |<------- d (停止期間) ------->|
        // ----*---------------*-----------------------------*------------> 時間 (time)
        //  mBaseTime       mStopTime                     currentTime
        mCurrentTime = Clock::now();
        mPausedTime += mCurrentTime - mStopTime;
        mPreviousTime = mCurrentTime;
        mStopTime = {};
        mIsStopped = false;
    }

    void Timer::Stop() {
        if (mIsStopped) return;

        mStopTime = Clock::now();
        mIsStopped = true;
    }

    void Timer::Update() {
        if(mIsStopped) {
            mDeltaTime = 0.0;
            return;
        }

        mCurrentTime = Clock::now();

        mDeltaTime = (mCurrentTime - mPreviousTime).count();
        mPreviousTime = mCurrentTime;

        // 非負（0以上）であることを保証します。DXSDKのCDXUTTimeの記述によると、
        // プロセッサが省電力モードに移行したり、別のプロセッサへスレッドが
        // スケジューリングされたりした場合、mDeltaTime が負の値になることがあります。
        if(mDeltaTime < 0.0) {
            mDeltaTime = 0.0;
        }
    }
}