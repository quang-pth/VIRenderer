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
        float X;
        float Y;
    public:
        Vector2() = default;

        Vector2(const Vector2&) = default;
        Vector2& operator=(const Vector2&) = default;

        Vector2(Vector2&&) = default;
        Vector2& operator=(Vector2&&) = default;
        
        constexpr Vector2(float x, float y) noexcept : X(x), Y(y) {}
        constexpr Vector2(float value) noexcept : X(value), Y(value) {}
        explicit Vector2(IN_SIZE(2) const float* values) noexcept : X(values[0]), Y(values[1]) {}
        
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