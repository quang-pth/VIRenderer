#include"Core/Math/Compute.h"
#include"Core/Math/Vector2.h"
#include"Core/Math/Vector3.h"
#include"Core/Math/Matrix3.h"
#include"Core/Math/Matrix4.h"
#include"Core/Math/Quaternion.h"

namespace VIEngine::Math {
    #pragma region Vector2
    float GetLengthSquared(const Vector2& vector) {
        return Dot(vector, vector);
    }
    
    float GetLength(const Vector2& vector) {
        // TODO: implement fast squared-root
        return Sqrtf(GetLengthSquared(vector));
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
        return source + (destination - source) * t;
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

    #pragma region Matrix3
    void Transpose(Matrix3& matrix) {
        std::swap(matrix[0][1], matrix[1][0]);   
        std::swap(matrix[0][2], matrix[2][0]);
        std::swap(matrix[1][2], matrix[2][1]);
    }

    Matrix3 GetTranspose(const Matrix3& matrix) {
        Matrix3 result = matrix;
        Transpose(result);
        return result;
    }

    const float* GetValuePtr(const Matrix3& matrix) { return &matrix[0][0]; }

    Matrix3 CreateScale(float x, float y) {
        float scale[3][3]= {
            {x, 0.0f, 0.0f},
            {0.0f, y, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        return Matrix3(scale);
    }

    Matrix3 CreateScale(float k) {
        return CreateScale(k, k);
    }

    Matrix3 CreateRotation(float theta) {
        float rotation[3][3] = {
            {Math::Cos(theta), Math::Sin(theta), 0.0f},
            {-Math::Sin(theta), Math::Cos(theta), 0.0f},
            {0.0f, 0.0f, 1.0f},
        };
        return Matrix3(rotation);
    }

    Matrix3 CreateTranslation(float x, float y) {
        float translate[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {x,    y,    1.0f},
        };
        return Matrix3(translate);
    }

    Matrix3 CreateTranslation(const Vector2& position) {
        return CreateTranslation(position.X, position.Y);
    }
    #pragma endregion Matrix3

    #pragma region Matrix4
    void Transpose(Matrix4& matrix) {
        std::swap(matrix[0][1], matrix[1][0]);   
        std::swap(matrix[0][2], matrix[2][0]);
        std::swap(matrix[0][3], matrix[3][0]);
        std::swap(matrix[1][2], matrix[2][1]);
        std::swap(matrix[1][3], matrix[3][1]);
        std::swap(matrix[2][3], matrix[3][2]);
    }

    Matrix4 GetTranspose(const Matrix4& matrix) {
        Matrix4 result = matrix;
        Transpose(result);
        return result;
    }

    const float* GetValuePtr(const Matrix4& matrix) { return &matrix[0][0]; }

    Matrix4 CreateScale(float x, float y, float z) {
        float scale[4][4]= {
            {x, 0.0f, 0.0f, 0.0f},
            {0.0f, y, 0.0f, 0.0f},
            {0.0f, 0.0f, z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Matrix4(scale);
    }

    Matrix4 CreateUScale(float k) {
        return CreateScale(k, k, k);
    }

    Matrix4 CreateRotation(float theta, const Vector3& axis) {
        // return CreateRotation(Quaternion(theta, axis));
        return Matrix4();
    }

    Matrix4 CreateRotation(const Quaternion& quaternion) {
        // TODO
        return Matrix4();
    }

    Matrix4 CreateRotationX(float theta) {
        float rotation[4][4] = {
            {1.0f,  0.0f,           0.0f,       0.0f},
            {0.0f,  Cos(theta),     Sin(theta), 0.0f},
            {0.0f,  -Sin(theta),    Cos(theta), 0.0f},
            {0.0f,  0.0f,           0.0f,       1.0f}
        };
        return Matrix4(rotation);
    }

    Matrix4 CreateRotationY(float theta) {
        float rotation[4][4] = {
            {Cos(theta),    0.0f,   -Sin(theta),    0.0f},
            {0.0f,          1.0f,   0.0f,           0.0f},
            {Sin(theta),    0.0f,   Cos(theta),     0.0f},
            {0.0f,          0.0f,   0.0f,           1.0f}
        };
        return Matrix4(rotation);
    }

    Matrix4 CreateRotationZ(float theta) {
        float rotation[4][4] = {
            {Cos(theta),    Sin(theta),    0.0f,    0.0f},
            {-Sin(theta),   Cos(theta),    0.0f,    0.0f},
            {0.0f,          0.0f,          1.0f,    0.0f},
            {0.0f,          0.0f,          0.0f,    1.0f}
        };
        return Matrix4(rotation);
    }

    Matrix4 CreateTranslation(float x, float y, float z) {
        float translate[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {x,    y,    z,    1.0f}
        };
        return Matrix4(translate);
    }

    Matrix4 CreateTranslation(const Vector3& position) {
        return CreateTranslation(position.X, position.Y, position.Z);
    }

    Matrix4 CreateLookAt(const Vector3& position, const Vector3& target, const Vector3& worldUp) {
        Vector3 forward = position - target;
        Normalize(forward);
        Vector3 right = Cross(worldUp, forward);
        Normalize(right);
        Vector3 up = Cross(forward, right);
        Normalize(up);
        // 左手座標系でのビュー行列は、右ベクトル、上ベクトル、前ベクトルを行ベクトルとして持ち、
        // 平行移動成分はカメラ位置に対して右ベクトル、上ベクトル、前ベクトルの内積の負の値になる
        Vector3 translation;
        translation.X = -Dot(right, position);
        translation.Y = -Dot(up, position);
        translation.Z = -Dot(forward, position);
        // 直交座標系であるため、回転行列の逆行列は転置行列になる
        float lookAt[4][4] = {
            {right.X,       up.X,           forward.X,      0.0f},
            {right.Y,       up.Y,           forward.Y,      0.0f},
            {right.Z,       up.Z,           forward.Z,      0.0f},
            {translation.X, translation.Y,  translation.Z,  1.0f}
        };
        return Matrix4(lookAt);
    }

    Matrix4 CreateOrtho(float width, float height, float n, float f) {
        float ortho[4][4] =
		{
			{ 2.0f / width, 0.0f,           0.0f,                   0.0f },
			{ 0.0f,         2.0f / height,  0.0f,                   0.0f },
			{ 0.0f,         0.0f,           1.0f / (f - n),    0.0f },
			{ 0.0f,         0.0f,           n / (n - f),    1.0f }
		};
		return Matrix4(ortho);
    }

    Matrix4 CreatePerspective(float fieldOfView, float aspectRatio, float n, float f) {
		float xScale = Cot(fieldOfView / 2.0f);
		float yScale = xScale * aspectRatio;
		float perspective[4][4] =
		{
			{ xScale,   0.0f,   0.0f,                       0.0f },
			{ 0.0f,     yScale, 0.0f,                       0.0f },
			{ 0.0f,     0.0f,   f / (f - n),         1.0f },
			{ 0.0f,     0.0f,   -n * f / (f - n), 0.0f }
		};
		return Matrix4(perspective);
    }
    #pragma endregion Matrix4


    #pragma region Quaternion
    void Invert(Quaternion& quaternion) {
        quaternion.W *= -1;
    }

    Quaternion GetInvert(const Quaternion& quaternion) {
        return Quaternion(-quaternion.W, quaternion.X, quaternion.Y, quaternion.Z);
    }

    Quaternion Difference(const Quaternion& q1, const Quaternion& q2) {
        return q2 * GetInvert(q1);
    }

    Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) {
        // 公式：(sin(1 - t) * omega / sin(Omega)) * q0 + (sin(t * Omega) / sin(Omega)) * q1
        float cosOmega = Dot(q1, q2);
        // q1とq2が反対のクォータニオンであれば、q1を反転させて最短距離のクォータニオンを使用する
        Quaternion negateQuat;
        if (cosOmega < 0.0f) {
            negateQuat = GetInvert(q1);
            // 反転させたクォータニオンを使用するため、cosOmegaも反転させる
            cosOmega = -cosOmega;
        }
        
        // cosOmegaが1に近い場合、sin(Omega)が0に近くなり、計算が不安定になるため、線形補間を使用する
        if (cosOmega > 0.9999f) return Lerp(q1, q2, t);

        float sinOmega = Sqrtf(1.0f - cosOmega * cosOmega);
        float omega = Atan2(sinOmega, cosOmega);
        float oneOverOmega = 1.0f / omega;
        float k0 = Sin(1.0f - t) * omega * oneOverOmega;
        float k1 = Sin(t * omega) * oneOverOmega;
        return k0 * q1 + k1 * q2;
    }

    Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) {
        return q1 + (q2 - q1) * t;
    }

    void Exponent(Quaternion& quaternion, float exp) {
        // 単位クォータニオンの場合、回転がないため、指数関数的に変化させても同じクォータニオンになる
        if (!IsIdentity(quaternion)) {
            float alpha = Acos(quaternion.W);
            float newAlpha = alpha * exp;
            quaternion.W = Cos(newAlpha);

            float multiple = Sin(newAlpha) / Sin(alpha);
            quaternion.X *= multiple;
            quaternion.Y *= multiple;
            quaternion.Z *= multiple;
        }
    }

    Quaternion GetExponent(const Quaternion& quaternion, float exp) {
        Quaternion result = quaternion;
        Exponent(result, exp);
        return result;
    }

    bool IsIdentity(const Quaternion& quaternion) {
        return quaternion.W > 0.9999f;
    }

    float Dot(const Quaternion& q1, const Quaternion& q2) {
        float result = 0;
        // クォータニオンの内積は、対応する要素の積の和で計算される
        for (uint8_t i = 0; i < 4; ++i) {
            result += q1[i] * q2[i];
        }
        return result;
    }

    const float* GetValuePtr(const Quaternion& quaternion) { return &quaternion.X; }
    #pragma endregion Quaternion
}