#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    class VI_API Vector2 {
    public:
        static const Vector2 Zero;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 NegUnitX;
        static const Vector2 NegUnitY;
    public:
        union {
            struct {
                float X;
                float Y;
            };
            float Data[2];
        };
    public:
        Vector2() = default;

        Vector2(const Vector2&) = default;
        Vector2& operator=(const Vector2&) = default;

        Vector2(Vector2&&) = default;
        Vector2& operator=(Vector2&&) = default;
        
        constexpr Vector2(float x, float y) noexcept : X(x), Y(y) {}
        constexpr Vector2(float value) noexcept : X(value), Y(value) {}
        explicit Vector2(IN_SIZE(2) const float* values) noexcept {
            memcpy(&Data[0], values, sizeof(float) * 2);
        }
        
        ~Vector2() = default;

        VI_FORCE_INLINE float& operator[](uint8_t index) { return Data[index]; }
        VI_FORCE_INLINE float operator[](uint8_t index) const { return Data[index]; }

        bool operator==(const Vector2& other) const;
        bool operator!=(const Vector2& other) const;
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;
        Vector2& operator*=(float scalar);
        Vector2& operator/=(float scalar);
    };

    Vector2 operator*(float scalar, const Vector2& vector);
}