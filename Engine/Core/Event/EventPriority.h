#pragma once

#include"Core/pch.h"

namespace VIEngine {
    /*
    * イベントの優先度を表す列挙型
    * 数値が大きいほど優先度が高い
    */
    enum class VI_API EEventPriority {
        LOW = 100,
        MEDIUM = 200,
        HIGH = 300,
        CRITICAL = 400
    };
}