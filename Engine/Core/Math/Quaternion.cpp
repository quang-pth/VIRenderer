#include"Core/Math/Quaternion.h"
#include"Core/Math/Math.h"

namespace VIEngine::Math {
    const Quaternion Quaternion::Identity{1.0f, 0.0f, 0.0f, 0.0f};

    Quaternion::Quaternion() {
        *this = Quaternion::Identity;
    }

    Quaternion::Quaternion(float angle, const Vector3& axis) {
        float alpha = angle * 0.5f;
        W = Cos(alpha);
        X = Sin(alpha) * axis.X;
        Y = Sin(alpha) * axis.Y;
        Z = Sin(alpha) * axis.Z;
    }

    Quaternion Quaternion::operator+(const Quaternion& other) const {
        return Quaternion(W + other.W, X + other.X, Y + other.Y, Z + other.Z);
    }

    Quaternion& Quaternion::operator+=(const Quaternion& other) {
        *this = *this + other;
        return *this;
    }

    Quaternion Quaternion::operator-(const Quaternion& other) const {
        return Quaternion(W - other.W, X - other.X, Y - other.Y, Z - other.Z);
    }

    Quaternion& Quaternion::operator-=(const Quaternion& other) {
        *this = *this - other;
        return *this;
    }

    Quaternion Quaternion::operator-() const {
        return Quaternion(-W, -X, -Y, -Z);
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const {
        Quaternion result;
        // q1 * q2 -> w = w1 * w2 - dot(v1, v2), xyz = w1 * v2 + w2 * v1 + cross(v1, v2)
        result.W = W * other.W - (X * other.X + Y * other.Y + Z * other.Z);
        result.X = W * other.X + X * other.W + Y * other.Z - Z * other.Y;
        result.Y = W * other.Y + Y * other.W + Z * other.X - X * other.Z;
        result.Z = W * other.Z + Z * other.W + X * other.Y - Y * other.X;
        return result;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& other) {
        *this = *this * other;
        return *this;
    }

    Quaternion Quaternion::operator*(float scalar) const {
        return Quaternion(W * scalar, X * scalar, Y * scalar, Z * scalar);
    }

    Quaternion& Quaternion::operator*=(float scalar) {
        *this = *this * scalar;
        return *this;
    }

    Quaternion Quaternion::operator/(float scalar) const {
        return *this * (1.0f / scalar);
    }

    Quaternion& Quaternion::operator/=(float scalar) {
        *this = *this * (1.0f / scalar);
        return *this;
    }

    Quaternion operator*(float scalar, const Quaternion& quaternion) {
        return quaternion * scalar;
    }
}