#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    constexpr float PI = 3.1415926535f;
	constexpr float TWO_Pi = PI * 2.0f;
	constexpr float PI_OVER_2 = PI / 2.0f;
	constexpr float MAX_NUMBER = std::numeric_limits<float>::infinity();
	constexpr float MIN_NUMBER = -std::numeric_limits<float>::infinity();

    VI_FORCE_INLINE float ToRadians(float degrees) { return degrees * PI / 180.0f; }
    VI_FORCE_INLINE float ToDegrees(float radians) { return radians * 180.0f / PI; }
    VI_FORCE_INLINE bool IsNearZero(float value, float epsilon = 0.001f) { return fabs(value) <= epsilon; }
}