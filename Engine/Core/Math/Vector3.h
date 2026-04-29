#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    class Vector4;

    class VI_API Vector3 {
    public:
        static const Vector3 Zero;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;
        static const Vector3 NegUnitX;
        static const Vector3 NegUnitY;
        static const Vector3 NegUnitZ;
    public:
        union {
            struct {
                float X;
                float Y;
                float Z;
            };
            struct {
                float R;
                float G;
                float B;
            };
            float Data[3];
        };
    public:
        Vector3() = default;

        Vector3(const Vector3&) = default;
        Vector3& operator=(const Vector3&) = default;

        Vector3(Vector3&&) = default;
        Vector3& operator=(Vector3&&) = default;
        
        constexpr Vector3(float x, float y, float z = 0.0f) noexcept : X(x), Y(y), Z(z) {}
        constexpr Vector3(float value) noexcept : X(value), Y(value), Z(value) {}
        explicit Vector3(IN_SIZE(3) const float* values) noexcept {
            memcpy(&Data[0], values, sizeof(float) * 3);
        }
        ~Vector3() = default;

        VI_FORCE_INLINE float& operator[](uint8_t index) { return Data[index]; }
        VI_FORCE_INLINE float operator[](uint8_t index) const { return Data[index]; }

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