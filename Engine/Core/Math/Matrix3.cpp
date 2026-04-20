#include"Core/Math/Matrix3.h"

namespace VIEngine::Math {
    static float identity[3][3] ={
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f }
    };
    const Matrix3 Matrix3::Identity(&identity[0][0]);

    Matrix3::Matrix3() {
        *this = Identity;
    }

    Matrix3::Matrix3(float value) {
        std::memset(mData, value, sizeof(float) * 9);
    }

    Matrix3 Matrix3::operator*(const Matrix3& other) {
        float result[3][3];
        // 行0
        result[0][0] = mData[0][0] * other[0][0] + mData[0][1] * other[1][0] + mData[0][2] * other[2][0];
        result[0][1] = mData[0][0] * other[0][1] + mData[0][1] * other[1][1] + mData[0][2] * other[2][1];
        result[0][2] = mData[0][0] * other[0][2] + mData[0][1] * other[1][2] + mData[0][2] * other[2][2];
        // 行1
        result[1][0] = mData[1][0] * other[0][0] + mData[1][1] * other[1][0] + mData[1][2] * other[2][0];
        result[1][1] = mData[1][0] * other[0][1] + mData[1][1] * other[1][1] + mData[1][2] * other[2][1];
        result[1][2] = mData[1][0] * other[0][2] + mData[1][1] * other[1][2] + mData[1][2] * other[2][2];
        // 行2
        result[2][0] = mData[2][0] * other[0][0] + mData[2][1] * other[1][0] + mData[2][2] * other[2][0];
        result[2][1] = mData[2][0] * other[0][1] + mData[2][1] * other[1][1] + mData[2][2] * other[2][1];
        result[2][2] = mData[2][0] * other[0][2] + mData[2][1] * other[1][2] + mData[2][2] * other[2][2];
        return Matrix3(result);
    }

    Matrix3& Matrix3::operator*=(const Matrix3& other) {
        *this = *this * other;
        return *this;
    }
}