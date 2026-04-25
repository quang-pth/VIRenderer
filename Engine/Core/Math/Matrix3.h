#pragma once

#include"Core/pch.h"

namespace VIEngine::Math {
    class VI_API Matrix3 {
    public:
        static const Matrix3 Identity;
        static const Matrix3 Zero;
    public:
        Matrix3();
        
        Matrix3(const Matrix3&) = default;
        Matrix3& operator=(const Matrix3&) = default;

        Matrix3(Matrix3&&) = default;
        Matrix3& operator=(Matrix3&&) = default;
        
        explicit Matrix3(float values[3][3]) noexcept {
            std::memcpy(&mData[0][0], values, sizeof(float) * 9);   
        }
        
        explicit Matrix3(IN_SIZE(9) const float* values) noexcept {
            std::memcpy(&mData[0][0], values, sizeof(float) * 9);   
        }

        VI_FORCE_INLINE float* operator[](uint8_t index) { return mData[index]; }
        VI_FORCE_INLINE const float* operator[](uint8_t index) const { return mData[index]; }

        Matrix3 operator*(const Matrix3& other);
        Matrix3& operator*=(const Matrix3& other);
    private:
        float mData[3][3];
    };
}