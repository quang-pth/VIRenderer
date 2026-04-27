#include"Core/Math/Matrix4.h"

namespace VIEngine::Math {
        static float identity[4][4] ={
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    const Matrix4 Matrix4::Identity(&identity[0][0]);
    
    static float zero[4][4] ={
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f }
    };
    const Matrix4 Matrix4::Zero(&zero[0][0]);

    Matrix4::Matrix4() {
        *this = Zero;
    }

    Matrix4 Matrix4::operator*(const Matrix4& other) {
        float result[4][4];
        // 行0
        result[0][0] = mData[0][0] * other[0][0] + mData[0][1] * other[1][0] + mData[0][2] * other[2][0] + mData[0][3] * other[3][0];
        result[0][1] = mData[0][0] * other[0][1] + mData[0][1] * other[1][1] + mData[0][2] * other[2][1] + mData[0][3] * other[3][1];
        result[0][2] = mData[0][0] * other[0][2] + mData[0][1] * other[1][2] + mData[0][2] * other[2][2] + mData[0][3] * other[3][2];
        result[0][3] = mData[0][0] * other[0][3] + mData[0][1] * other[1][3] + mData[0][2] * other[2][3] + mData[0][3] * other[3][3];
        // 行1
        result[1][0] = mData[1][0] * other[0][0] + mData[1][1] * other[1][0] + mData[1][2] * other[2][0] + mData[1][3] * other[3][0];
        result[1][1] = mData[1][0] * other[0][1] + mData[1][1] * other[1][1] + mData[1][2] * other[2][1] + mData[1][3] * other[3][1];
        result[1][2] = mData[1][0] * other[0][2] + mData[1][1] * other[1][2] + mData[1][2] * other[2][2] + mData[1][3] * other[3][2];
        result[1][3] = mData[1][0] * other[0][3] + mData[1][1] * other[1][3] + mData[1][2] * other[2][3] + mData[1][3] * other[3][3];
        // 行2
        result[2][0] = mData[2][0] * other[0][0] + mData[2][1] * other[1][0] + mData[2][2] * other[2][0] + mData[2][3] * other[3][0];
        result[2][1] = mData[2][0] * other[0][1] + mData[2][1] * other[1][1] + mData[2][2] * other[2][1] + mData[2][3] * other[3][1];
        result[2][2] = mData[2][0] * other[0][2] + mData[2][1] * other[1][2] + mData[2][2] * other[2][2] + mData[2][3] * other[3][2];
        result[2][3] = mData[2][0] * other[0][3] + mData[2][1] * other[1][3] + mData[2][2] * other[2][3] + mData[2][3] * other[3][3];
        // 行3
        result[3][0] = mData[3][0] * other[0][0] + mData[3][1] * other[1][0] + mData[3][2] * other[2][0] + mData[3][3] * other[3][0];
        result[3][1] = mData[3][0] * other[0][1] + mData[3][1] * other[1][1] + mData[3][2] * other[2][1] + mData[3][3] * other[3][1];
        result[3][2] = mData[3][0] * other[0][2] + mData[3][1] * other[1][2] + mData[3][2] * other[2][2] + mData[3][3] * other[3][2];
        result[3][3] = mData[3][0] * other[0][3] + mData[3][1] * other[1][3] + mData[3][2] * other[2][3] + mData[3][3] * other[3][3];
        return Matrix4(result);
    }

    Matrix4& Matrix4::operator*=(const Matrix4& other) {
        *this = *this * other;
        return *this;
    }
}