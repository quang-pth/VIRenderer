#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    class VI_API Quaternion {
    public:
        static const Quaternion Identity;
    public:
        union {
            struct {
                float W;
                float X;
                float Y;
                float Z;
            };
            float Data[4];
        };
    public:
        Quaternion();

        Quaternion(const Quaternion&) = default;
        Quaternion& operator=(const Quaternion&) = default;

        Quaternion(Quaternion&&) = default;
        Quaternion& operator=(Quaternion&&) = default;
        
        constexpr explicit Quaternion(float w, float x, float y, float z) noexcept : W(w), X(x), Y(y), Z(z) {}
        explicit Quaternion(float angle, const class Vector3& axis);
        explicit Quaternion(IN_SIZE(4) const float* data) {
            memcpy(&Data[0], data, sizeof(float) * 4);
        }

        VI_FORCE_INLINE float operator[](uint8_t index) const { return Data[index]; }

        Quaternion operator+(const Quaternion& other) const;
        Quaternion& operator+=(const Quaternion& other);
        Quaternion operator-(const Quaternion& other) const;
        Quaternion& operator-=(const Quaternion& other);
        Quaternion operator*(const Quaternion& other) const;
        Quaternion& operator*=(const Quaternion& other);
        Quaternion operator*(float scalar) const;
        Quaternion& operator*=(float scalar);
    };

    Quaternion operator*(float scalar, const Quaternion& Quaternion);
}