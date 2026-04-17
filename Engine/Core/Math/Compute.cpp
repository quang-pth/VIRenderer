#include"Core/Math/Compute.h"

namespace VIEngine::Math {
    #pragma region Vector2
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
            vector.X = 0;
            vector.Y = 0;
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
        return lhs.X * rhs.X + lhs.Y * rhs.Y;
    }

    Vector2 Lerp(const Vector2& source, const Vector2& destination, float t) {
        return source * (1.0f - t) + t * destination;
    }

    Vector2 Reflect(const Vector2& vector, const Vector2& normal) {
        return vector - 2.0f * Dot(normal, vector) * normal;
    }

    const float* GetValuePtr(const Vector2& vector) { 
        return &vector.X;
    }
    #pragma endregion Vector2

    #pragma region Vector3
    float GetLengthSquared(const Vector3& vector) {
        return Dot(vector, vector);
    }
    
    float GetLength(const Vector3& vector) {
        // TODO: implement fast squared-root
        return std::sqrtf(GetLengthSquared(vector));
    }

    void Normalize(Vector3& vector) {
        float length = GetLength(vector);
        vector /= length;
    }

    void SafeNormalize(Vector3& vector, float epsilon) {
        float length = GetLength(vector);
        if (Math::IsNearZero(length, epsilon)) {
            vector.X = 0;
            vector.Y = 0;
            return;
        }
        
        vector /= length;
    }

    Vector3 GetNormalize(const Vector3& vector) {
        float length = GetLength(vector);
        return vector / length;
    }
   
    Vector3 GetSafeNormalize(const Vector3& vector, float epsilon) {
        float length = GetLength(vector);
        if (Math::IsNearZero(length, epsilon)) {
            return Vector3::Zero;
        }
        return vector * (1.0f / length);
    }

    float Dot(const Vector3& lhs, const Vector3& rhs) {
        return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
    }

    Vector3 Lerp(const Vector3& source, const Vector3& destination, float t) {
        return source * (1.0f - t) + t * destination;
    }

    Vector3 Reflect(const Vector3& vector, const Vector3& normal) {
        return vector - 2.0f * Dot(normal, vector) * normal;
    }

    const float* GetValuePtr(const Vector3& vector) { 
        return &vector.X;
    }

    Vector3 Cross(const Vector3& lhs, const Vector3& rhs) {
        return {
            lhs.Y * rhs.Z - lhs.Z * rhs.Y,
            lhs.Z * rhs.X - lhs.X * rhs.Z,
            lhs.X * rhs.Y - lhs.Y * rhs.X
        };
    }
    #pragma endregion Vector3
}