#pragma once

#include"Core/pch.h"

namespace VIEngine {
    /*
    * イベントの優先度を表す列挙型
    * 数値が大きいほど優先度が高い
    */
    enum class VI_API EEventPriority {
        LOW = 100,          // ログ出力、リソースロード完了通知
        MEDIUM = 200,       // ゲームロジック、物理演算、アニメーション
        HIGH = 300,         // マウス操作、キー入力、UI反応
        CRITICAL = 400      // システム終了、リサイズ、デバイスロスト
    };
}