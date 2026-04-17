#include"Core/Math/Vector2.h"
#include"Core/Math/Math.h"

namespace VIEngine::Math {
    const Vector2 Vector2::Zero = {0.0f};
    const Vector2 Vector2::UnitX = {1.0f, 0.0f};
    const Vector2 Vector2::UnitY = {0.0f, 1.0f};
    const Vector2 Vector2::NegUnitX = {-1.0f, 0.0f};
    const Vector2 Vector2::NegUnitY = {0.0f, -1.0f};

    bool Vector2::operator==(const Vector2& other) const {
        return X == other.X && Y == other.Y;
    }

    bool Vector2::operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    Vector2 Vector2::operator+(const Vector2& other) const {
        return { X + other.X, Y + other.Y };
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return { X - other.X, Y - other.Y };
    }

    Vector2& Vector2::operator+=(const Vector2& other) {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other) {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    Vector2 Vector2::operator*(float scalar) const {
        return { X * scalar, Y * scalar };
    }

    Vector2 Vector2::operator/(float scalar) const {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        return { X / scalar, Y / scalar };
    }

    Vector2& Vector2::operator*=(float scalar) {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(float scalar) {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    Vector2 operator*(float scalar, const Vector2& vector) {
        return vector * scalar;
    }
}