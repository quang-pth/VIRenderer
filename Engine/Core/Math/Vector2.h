#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    struct VI_API Vector2 {
    public:
        static const Vector2 Zero;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 NegUnitX;
        static const Vector2 NegUnitY;
    public:
        float mX;
        float mY;
    public:
        Vector2() = default;

        Vector2(const Vector2&) = default;
        Vector2& operator=(const Vector2&) = default;

        Vector2(Vector2&&) = default;
        Vector2& operator=(Vector2&&) = default;
        
        constexpr Vector2(float x, float y) noexcept : mX(x), mY(y) {}
        constexpr Vector2(float value) noexcept : mX(value), mY(value) {}
        explicit Vector2(IN_SIZE(2) const float* values) noexcept : mX(values[0]), mY(values[1]) {}
        
        ~Vector2() = default;

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