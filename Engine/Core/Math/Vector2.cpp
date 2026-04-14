#include"Core/Math/Vector2.h"
#include"Core/Math/Math.h"

namespace VIEngine::Math {
    const Vector2 Vector2::Zero = {0.0f};
    const Vector2 Vector2::UnitX = {1.0f, 0.0f};
    const Vector2 Vector2::UnitY = {0.0f, 1.0f};
    const Vector2 Vector2::NegUnitX = {-1.0f, 0.0f};
    const Vector2 Vector2::NegUnitY = {0.0f, -1.0f};

    bool Vector2::operator==(const Vector2& other) const {
        return mX == other.mX && mY == other.mY;
    }

    bool Vector2::operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    Vector2 Vector2::operator+(const Vector2& other) const {
        return { mX + other.mX, mY + other.mY };
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return { mX - other.mX, mY - other.mY };
    }

    Vector2& Vector2::operator+=(const Vector2& other) {
        mX += other.mX;
        mY += other.mY;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other) {
        mX -= other.mX;
        mY -= other.mY;
        return *this;
    }

    Vector2 Vector2::operator*(float scalar) const {
        return { mX * scalar, mY * scalar };
    }

    Vector2 Vector2::operator/(float scalar) const {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        return { mX / scalar, mY / scalar };
    }

    Vector2& Vector2::operator*=(float scalar) {
        mX *= scalar;
        mY *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(float scalar) {
        VI_ASSERT(!Math::IsNearZero(scalar) && "Division by scalar that is near to zero");
        mX /= scalar;
        mY /= scalar;
        return *this;
    }

    Vector2 operator*(float scalar, const Vector2& vector) {
        return vector * scalar;
    }
}