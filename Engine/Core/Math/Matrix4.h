#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    class VI_API Matrix4 {
    public:
        static const Matrix4 Identity;
        static const Matrix4 Zero;
    public:
        Matrix4();
        
        Matrix4(const Matrix4&) = default;
        Matrix4& operator=(const Matrix4&) = default;

        Matrix4(Matrix4&&) = default;
        Matrix4& operator=(Matrix4&&) = default;
        
        explicit Matrix4(float values[4][4]) noexcept {
            std::memcpy(&mData[0][0], values, sizeof(float) * 16);
        }
        
        explicit Matrix4(IN_SIZE(16) const float* values) noexcept {
            std::memcpy(&mData[0][0], values, sizeof(float) * 16);
        }

        VI_FORCE_INLINE float* operator[](uint8_t index) { return mData[index]; }
        VI_FORCE_INLINE const float* operator[](uint8_t index) const { return mData[index]; }

        Matrix4 operator*(const Matrix4& other);
        Matrix4& operator*=(const Matrix4& other);
    private:
        float mData[4][4];
    };
}