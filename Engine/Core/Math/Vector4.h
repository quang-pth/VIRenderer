#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    class Matrix4;
    class Vector3;

    class VI_API Vector4 {
    public:
        static const Vector4 Zero;
        static const Vector4 UnitX;
        static const Vector4 UnitY;
        static const Vector4 UnitZ;
        static const Vector4 NegUnitX;
        static const Vector4 NegUnitY;
        static const Vector4 NegUnitZ;
    public:
        union {
            struct {
                float X;
                float Y;
                float Z;
                float W;
            };
            struct {
                float R;
                float G;
                float B;
                float A;
            };
            float Data[4];
        };
    public:
        Vector4();

        Vector4(const Vector4&) = default;
        Vector4& operator=(const Vector4&) = default;

        Vector4(Vector4&&) = default;
        Vector4& operator=(Vector4&&) = default;
        
        Vector4(const Vector3& vector3, float w = 1.0f);
        constexpr Vector4(float x, float y, float z, float w = 1.0f) noexcept : X(x), Y(y), Z(z), W(w) {}
        constexpr Vector4(float xyz, float w = 1.0f) noexcept : X(xyz), Y(xyz), Z(xyz), W(w) {}
        explicit Vector4(IN_SIZE(4) const float* values) noexcept {
            memcpy(&Data[0], values, sizeof(float) * 4);
        }
        
        ~Vector4() = default;
        
        VI_FORCE_INLINE float& operator[](uint8_t index) { return Data[index]; }
        VI_FORCE_INLINE float operator[](uint8_t index) const { return Data[index]; }

        bool operator==(const Vector4& other) const;
        bool operator!=(const Vector4& other) const;
        Vector4 operator+(const Vector4& other) const;
        Vector4 operator-(const Vector4& other) const;
        Vector4& operator+=(const Vector4& other);
        Vector4& operator-=(const Vector4& other);
        Vector4 operator*(float scalar) const;
        Vector4 operator*(const Matrix4& matrix) const;
        Vector4 operator/(float scalar) const;
        Vector4& operator*=(float scalar);
        Vector4& operator/=(float scalar);
    };

    Vector4 operator*(float scalar, const Vector4& vector);
}