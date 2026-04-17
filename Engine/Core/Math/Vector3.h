#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    struct VI_API Vector3 {
    public:
        static const Vector3 Zero;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;
        static const Vector3 NegUnitX;
        static const Vector3 NegUnitY;
        static const Vector3 NegUnitZ;
    public:
        float X;
        float Y;
        float Z;
    public:
        Vector3() = default;

        Vector3(const Vector3&) = default;
        Vector3& operator=(const Vector3&) = default;

        Vector3(Vector3&&) = default;
        Vector3& operator=(Vector3&&) = default;
        
        constexpr Vector3(float x, float y, float z = 0.0f) noexcept : X(x), Y(y), Z(z) {}
        constexpr Vector3(float value) noexcept : X(value), Y(value), Z(value) {}
        explicit Vector3(IN_SIZE(3) const float* values) noexcept : X(values[0]), Y(values[1]), Z(values[2]) {}
        
        ~Vector3() = default;

        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;
        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3 operator*(float scalar) const;
        Vector3 operator/(float scalar) const;
        Vector3& operator*=(float scalar);
        Vector3& operator/=(float scalar);
    };

    Vector3 operator*(float scalar, const Vector3& vector);
}