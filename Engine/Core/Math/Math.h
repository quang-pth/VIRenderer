#pragma once

#include"Core/pch.h"
#include"Core/Math/Vector2.h"
#include"Core/Math/Vector3.h"

namespace VIEngine::Math {
    constexpr float PI = 3.1415926535f;
	constexpr float TWO_Pi = PI * 2.0f;
	constexpr float PI_OVER_2 = PI / 2.0f;
	constexpr float MAX_NUMBER = std::numeric_limits<float>::infinity();
	constexpr float MIN_NUMBER = -std::numeric_limits<float>::infinity();
    constexpr float BASE_EPSILON = 0.001f;

    // 角度をラジアンに変換する
    VI_FORCE_INLINE float ToRadians(float degrees) { return degrees * PI / 180.0f; }
    // ラジアンを角度に変換する
    VI_FORCE_INLINE float ToDegrees(float radians) { return radians * 180.0f / PI; }
    // 値が0に近いかどうかを判断する
    VI_FORCE_INLINE bool IsNearZero(float value, float epsilon = BASE_EPSILON) { return fabs(value) <= epsilon; }

    // aとbの小さい方の値を返す
    template<typename T>
    VI_FORCE_INLINE T Min(T a, T b) { return a > b ? b : a; }
    
    // aとbの大きい方の値を返す
    template<typename T>
    VI_FORCE_INLINE T Max(T a, T b) { return a > b ? a : b; }

    // aをminとmaxの範囲内にクランプする
    template<typename T>
    VI_FORCE_INLINE T Clamp(T a, T min, T max) { return Min(max, Max(a, min)); }
    
    // ベクトルの各要素をminとmaxの範囲内にクランプする
    template<typename T>
    VI_FORCE_INLINE Vector2 Clamp(const Vector2& vector, T min, T max) { 
        return { 
            Clamp(vector.X, min, max), 
            Clamp(vector.Y, min, max) 
        }; 
    }

    // ベクトルの各要素をminVectorとmaxVectorの該当する要素の範囲内にクランプする
    VI_FORCE_INLINE Vector2 Clamp(const Vector2& vector, const Vector2& minVector, const Vector2& maxVector) { 
        return { 
            Clamp(vector.X, minVector.X, maxVector.X), 
            Clamp(vector.Y, minVector.Y, maxVector.Y) 
        }; 
    }

    // ベクトルの各要素をminとmaxの範囲内にクランプする
    template<typename T>
    VI_FORCE_INLINE Vector3 Clamp(const Vector3& vector, T a, T min, T max) { 
        return { 
            Clamp(vector.X, min, max), 
            Clamp(vector.Y, min, max), 
            Clamp(vector.Z, min, max)
        }; 
    }

    // ベクトルの各要素をminVectorとmaxVectorの該当する要素の範囲内にクランプする
    VI_FORCE_INLINE Vector3 Clamp(const Vector3& vector, const Vector3& minVector, const Vector3& maxVector) { 
        return { 
            Clamp(vector.X, minVector.X, maxVector.X), 
            Clamp(vector.Y, minVector.Y, maxVector.Y), 
            Clamp(vector.Z, minVector.Z, maxVector.Z)
        }; 
    }
}