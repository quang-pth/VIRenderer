#include"Core/Math/Compute.h"

namespace VIEngine::Math {
    float GetLengthSquared(const Vector2& vector) {
        return Dot(vector, vector);
    }
    
    float GetLength(const Vector2& vector) {
        // TODO: implement fast squared-root
        return std::sqrtf(GetLengthSquared(vector));
    }

    void Normalize(Vector2& vector) {
        float length = GetLength(vector);
        vector /= length;
    }

    void SafeNormalize(Vector2& vector, float epsilon) {
        float length = GetLength(vector);
        if (Math::IsNearZero(length, epsilon)) {
            vector.mX = 0;
            vector.mY = 0;
            return;
        }
        
        vector /= length;
    }

    Vector2 GetNormalize(const Vector2& vector) {
        float length = GetLength(vector);
        return vector / length;
    }
   
    Vector2 GetSafeNormalize(const Vector2& vector, float epsilon) {
        float length = GetLength(vector);
        if (Math::IsNearZero(length, epsilon)) {
            return Vector2::Zero;
        }
        return vector * (1.0f / length);
    }

    float Dot(const Vector2& lhs, const Vector2& rhs) {
        return lhs.mX * rhs.mX + lhs.mY * rhs.mY;
    }

    Vector2 Lerp(const Vector2& source, const Vector2& destination, float t) {
        return source * (1.0f - t) + t * destination;
    }

    Vector2 Reflect(const Vector2& vector, const Vector2& normal) {
        return vector - 2.0f * Dot(normal, vector) * normal;
    }

    const float* GetValuePtr(const Vector2& vector) { 
        return &vector.mX;
    }
}