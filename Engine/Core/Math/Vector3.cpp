#include"Core/Math/Vector3.h"
#include"Core/Math/Math.h"

namespace VIEngine::Math {
    const Vector3 Vector3::Zero = {0.0f};
    const Vector3 Vector3::UnitX = {1.0f, 0.0f, 0.0f};
    const Vector3 Vector3::UnitY = {0.0f, 1.0f, 0.0f};
    const Vector3 Vector3::UnitZ = {0.0f, 0.0f, 1.0f};
    const Vector3 Vector3::NegUnitX = {-1.0f, 0.0f, 0.0f};
    const Vector3 Vector3::NegUnitY = {0.0f, -1.0f, 0.0f};
    const Vector3 Vector3::NegUnitZ = {0.0f, 0.0f, -1.0f};

    bool Vector3::operator==(const Vector3& other) const {
        return X == other.X && Y == other.Y && Z == other.Z;
    }

    bool Vector3::operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    Vector3 Vector3::operator+(const Vector3& other) const {
        return { X + other.X, Y + other.Y, Z + other.Z };
    }

    Vector3 Vector3::operator-(const Vector3& other) const {
        return { X - other.X, Y - other.Y, Z - other.Z };
    }

    Vector3& Vector3::operator+=(const Vector3& other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3 Vector3::operator*(float scalar) const {
        return { X * scalar, Y * scalar, Z * scalar };
    }

    Vector3 Vector3::operator/(float scalar) const {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        return { X / scalar, Y / scalar, Z / scalar };
    }

    Vector3& Vector3::operator*=(float scalar) {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    Vector3& Vector3::operator/=(float scalar) {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    Vector3 operator*(float scalar, const Vector3& vector) {
        return vector * scalar;
    }
}