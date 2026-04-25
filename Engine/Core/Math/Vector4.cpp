#include"Core/Math/Vector4.h"
#include"Core/Math/Math.h"
#include"Core/Math/Matrix4.h"

namespace VIEngine::Math {
    const Vector4 Vector4::Zero = {0.0f, 0.0f, 0.0f, 1.0f};
    const Vector4 Vector4::UnitX = {1.0f, 0.0f, 0.0f, 1.0f};
    const Vector4 Vector4::UnitY = {0.0f, 1.0f, 0.0f, 1.0f};
    const Vector4 Vector4::UnitZ = {0.0f, 0.0f, 1.0f, 1.0f};
    const Vector4 Vector4::NegUnitX = {-1.0f, 0.0f, 0.0f, 1.0f};
    const Vector4 Vector4::NegUnitY = {0.0f, -1.0f, 0.0f, 1.0f};
    const Vector4 Vector4::NegUnitZ = {0.0f, 0.0f, -1.0f, 1.0f};

    Vector4::Vector4() {
        *this = Vector4::Zero;
    }

    bool Vector4::operator==(const Vector4& other) const {
        return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
    }

    bool Vector4::operator!=(const Vector4& other) const {
        return !(*this == other);
    }

    Vector4 Vector4::operator+(const Vector4& other) const {
        return { X + other.X, Y + other.Y, Z + other.Z, W + other.W };
    }

    Vector4 Vector4::operator-(const Vector4& other) const {
        return { X - other.X, Y - other.Y, Z - other.Z, W - other.W };
    }

    Vector4& Vector4::operator+=(const Vector4& other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        W += other.W;
        return *this;
    }

    Vector4& Vector4::operator-=(const Vector4& other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        W -= other.W;
        return *this;
    }

    Vector4 Vector4::operator*(float scalar) const {
        return { X * scalar, Y * scalar, Z * scalar, W * scalar };
    }

    Vector4 Vector4::operator*(const Matrix4& matrix) const {   
        Vector4 transformed;
        transformed[0] = Data[0] * matrix[0][0] + Data[1] * matrix[1][0] + Data[2] * matrix[2][0] + Data[3] * matrix[3][0];
        transformed[1] = Data[0] * matrix[0][1] + Data[1] * matrix[1][1] + Data[2] * matrix[2][1] + Data[3] * matrix[3][1];
        transformed[2] = Data[0] * matrix[0][2] + Data[1] * matrix[1][2] + Data[2] * matrix[2][2] + Data[3] * matrix[3][2];
        transformed[3] = Data[0] * matrix[0][3] + Data[1] * matrix[1][3] + Data[2] * matrix[2][3] + Data[3] * matrix[3][3];
        return transformed;
    }

    Vector4 Vector4::operator/(float scalar) const {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        return *this * (1.0f / scalar);
    }

    Vector4& Vector4::operator*=(float scalar) {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
        return *this;
    }

    Vector4& Vector4::operator/=(float scalar) {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        *this *= (1.0f / scalar);
        return *this;
    }

    Vector4 operator*(float scalar, const Vector4& vector) {
        return vector * scalar;
    }
}