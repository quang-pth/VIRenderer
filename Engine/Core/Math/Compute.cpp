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

    Matrix3 CreateScale2D(float x, float y) {
        float scale[3][3]= {
            {x, 0.0f, 0.0f},
            {0.0f, y, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        return Matrix3(scale);
    }

    Matrix3 CreateScale2D(float k) {
        return CreateScale2D(k, k);
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

    bool IsOrthonormal(const Matrix3& matrix) {
        Vector3 forward(matrix[0][0], matrix[0][1], matrix[0][2]);
        Normalize(forward);
        
        Vector3 strafe(matrix[1][0], matrix[1][1], matrix[1][2]);
        Normalize(strafe);
        
        Vector3 up(matrix[2][0], matrix[2][1], matrix[2][2]);
        Normalize(up);

        if (!IsNearZero(Dot(forward, strafe))) return false;
        if (!IsNearZero(Dot(forward, up))) return false;
        if (!IsNearZero(Dot(up, forward))) return false;

        return true;
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

    Matrix4 CreateScale3D(float x, float y, float z) {
        float scale[4][4]= {
            {x, 0.0f, 0.0f, 0.0f},
            {0.0f, y, 0.0f, 0.0f},
            {0.0f, 0.0f, z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Matrix4(scale);
    }

    Matrix4 CreateScale3D(float k) {
        return CreateScale3D(k, k, k);
    }

    Matrix4 CreateRotation(float theta, const Vector3& axis) {
        return CreateRotation(Quaternion(theta, axis));
    }

    Matrix4 CreateRotation(const Quaternion& quaternion) {
        Matrix4 rotation;

        rotation[0][0] = 1 - 2 * (quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z);
        rotation[0][1] = 2 * (quaternion.X * quaternion.Y +  quaternion.W * quaternion.Z);
        rotation[0][2] = 2 * (quaternion.X * quaternion.Z - quaternion.W * quaternion.Y);

        rotation[1][0] = 2 * (quaternion.X * quaternion.Y - quaternion.W * quaternion.Z);
        rotation[1][1] = 1 - 2 * (quaternion.X * quaternion.X + quaternion.Z * quaternion.Z);
        rotation[1][2] = 2 * (quaternion.Y * quaternion.Z + quaternion.W * quaternion.X);

        rotation[2][0] = 2 * (quaternion.X * quaternion.Z + quaternion.W * quaternion.Y);
        rotation[2][1] = 2 * (quaternion.Y * quaternion.Z - quaternion.W * quaternion.X);
        rotation[2][2] = 1 - 2 * (quaternion.X * quaternion.X + quaternion.Y * quaternion.Y);

        rotation[3][3] = 1.0f;

        return rotation;
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
        Vector3 strafe = Cross(worldUp, forward);
        Normalize(strafe);
        Vector3 up = Cross(forward, strafe);
        // 左手座標系でのビュー行列は、右ベクトル、上ベクトル、前ベクトルを行ベクトルとして持ち、
        // 平行移動成分はカメラ位置に対して右ベクトル、上ベクトル、前ベクトルの内積の負の値になる
        Vector3 translation;
        translation.X = -Dot(strafe, position);
        translation.Y = -Dot(up, position);
        translation.Z = -Dot(forward, position);
        // 直交座標系であるため、回転行列の逆行列は転置行列になる
        float lookAt[4][4] = {
            {strafe.X,       up.X,           forward.X,      0.0f},
            {strafe.Y,       up.Y,           forward.Y,      0.0f},
            {strafe.Z,       up.Z,           forward.Z,      0.0f},
            {translation.X,  translation.Y,  translation.Z,  1.0f}
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

    void Invert(Matrix4& matrix, bool& invertSuccess) {
        invertSuccess = true;
        // 逆行列を計算する前に、行列が正規直交行列であるかどうかを判断する
        if (IsOrthonormal(matrix)) {
            // 正規直交行列であれば、回転行列の逆行列は転置行列になるため、転置行列を計算して返す
            Transpose(matrix);
            return;
        }

        float tmp[12];
        float src[16];
        float dst[16];
        float det;

        // 1行を1列にする
        src[0] = matrix[0][0];
        src[4] = matrix[0][1];
        src[8] = matrix[0][2];
        src[12] = matrix[0][3];

        // 2行を2列にする
        src[1] = matrix[1][0];
        src[5] = matrix[1][1];
        src[9] = matrix[1][2];
        src[13] = matrix[1][3];

        // 3行を3列にする
        src[2] = matrix[2][0];
        src[6] = matrix[2][1];
        src[10] = matrix[2][2];
        src[14] = matrix[2][3];

        // 4行を4列にする
        src[3] = matrix[3][0];
        src[7] = matrix[3][1];
        src[11] = matrix[3][2];
        src[15] = matrix[3][3];

        // cofactorを計算するための一時的な変数を計算する
        tmp[0] = src[10] * src[15];
        tmp[1] = src[11] * src[14];
        tmp[2] = src[9] * src[15];
        tmp[3] = src[11] * src[13];
        tmp[4] = src[9] * src[14];
        tmp[5] = src[10] * src[13];
        tmp[6] = src[8] * src[15];
        tmp[7] = src[11] * src[12];
        tmp[8] = src[8] * src[14];
        tmp[9] = src[10] * src[12];
        tmp[10] = src[8] * src[13];
        tmp[11] = src[9] * src[12];

        // cofactorを計算する
        dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
        dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
        dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
        dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
        dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
        dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
        dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
        dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];


        // 行列式を計算する
        det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];
        if (IsNearZero(det)) {
            // 行列が特異行列であるため、逆行列は存在しない
            invertSuccess = false;
            return;
        }

        dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
        dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
        dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
        dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
        dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
        dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
        dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
        dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

        // cofactorを計算するための一時的な変数を計算する
        tmp[0] = src[2] * src[7];
        tmp[1] = src[3] * src[6];
        tmp[2] = src[1] * src[7];
        tmp[3] = src[3] * src[5];
        tmp[4] = src[1] * src[6];
        tmp[5] = src[2] * src[5];
        tmp[6] = src[0] * src[7];
        tmp[7] = src[3] * src[4];
        tmp[8] = src[0] * src[6];
        tmp[9] = src[2] * src[4];
        tmp[10] = src[0] * src[5];
        tmp[11] = src[1] * src[4];

        // cofactorを計算する
        dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
        dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
        dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
        dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
        dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
        dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
        dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
        dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
        dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
        dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
        dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
        dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
        dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
        dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
        dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
        dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

        det = 1 / det;
        for (int j = 0; j < 16; j++)
        {
            dst[j] *= det;
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] = dst[i * 4 + j];
            }
        }
    }

    Matrix4 GetInvert(const Matrix4& matrix, bool& invertSuccess) {
        Matrix4 result = matrix;
        Invert(result, invertSuccess);
        return result;
    }

    bool IsOrthonormal(const Matrix4& matrix) {
        Vector3 forward(matrix[0][0], matrix[0][1], matrix[0][2]);
        Normalize(forward);
        
        Vector3 strafe(matrix[1][0], matrix[1][1], matrix[1][2]);
        Normalize(strafe);
        
        Vector3 up(matrix[2][0], matrix[2][1], matrix[2][2]);
        Normalize(up);

        if (!IsNearZero(Dot(forward, strafe))) return false;
        if (!IsNearZero(Dot(forward, up))) return false;
        if (!IsNearZero(Dot(up, forward))) return false;

        return true;
    }

    #pragma endregion Matrix4


    #pragma region Quaternion
    void Conjugate(Quaternion& quaternion) {
        quaternion.X *= -1;
        quaternion.Y *= -1;
        quaternion.Z *= -1;
    }
    
    void Invert(Quaternion& quaternion) {
        Conjugate(quaternion);
        quaternion *= (1.0f / Dot(quaternion, quaternion));
    }

    Quaternion GetConjugate(const Quaternion& quaternion) {
        return Quaternion(quaternion.W, -quaternion.X, -quaternion.Y, -quaternion.Z);
    }

    Quaternion GetInvert(const Quaternion& quaternion) {
        return GetConjugate(quaternion) * (1.0f / Dot(quaternion, quaternion));
    }

    Quaternion Difference(const Quaternion& q1, const Quaternion& q2) {
        return GetInvert(q1) * q2;
    }

    Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) {
        return q1 + (q2 - q1) * t;
    }

    // https://gamemath.com/book/orient.html#quaternion_slerp
    Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) {
        // 公式：(sin(1 - t) * omega / sin(Omega)) * q0 + (sin(t * Omega) / sin(Omega)) * q1
        float cosAngle = Dot(q1, q2);
        // q1とq2が反対のクォータニオンであれば、q1を反転させて最短距離のクォータニオンを使用する
        Quaternion negateQ2 = q2;
        if (cosAngle < 0.0f) {
            negateQ2 = -negateQ2;
            // 反転させたクォータニオンを使用するため、cosOmegaも反転させる
            cosAngle = -cosAngle;
        }
        
        // cosOmegaが1に近い場合、sin(Omega)が0に近くなり、計算が不安定になるため、線形補間を使用する
        if (cosAngle > 1.0f - BASE_EPSILON) return Lerp(q1, negateQ2, t);

        float sinAngle = Sqrtf(1.0f - cosAngle * cosAngle);
        float angle = Atan2(sinAngle, cosAngle);
        float oneOverSinAngle = 1.0f / sinAngle;
        float k0 = Sin((1.0f - t) * angle) * oneOverSinAngle;
        float k1 = Sin(t * angle) * oneOverSinAngle;
        return k0 * q1 + k1 * negateQ2;
    }

    void Exponent(Quaternion& quaternion, float exp) {
        // 単位クォータニオンの場合、回転がないため、指数関数的に変化させても同じクォータニオンになる
        if (!IsIdentity(quaternion)) {
            float alpha = Acos(quaternion.W); // alpha = angle / 2
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
        return quaternion.W > 1.0f - BASE_EPSILON && 
            IsNearZero(quaternion.X) && 
            IsNearZero(quaternion.Y) && 
            IsNearZero(quaternion.Z);
    }

    float Dot(const Quaternion& q1, const Quaternion& q2) {
        float result = 0;
        // クォータニオンの内積は、対応する要素の積の和で計算される
        for (uint8_t i = 0; i < 4; ++i) {
            result += q1[i] * q2[i];
        }
        return result;
    }

    const float* GetValuePtr(const Quaternion& quaternion) { return &quaternion.Data[0]; }
    Vector3 GetVector(const Quaternion& quaternion) { return Vector3{quaternion.X, quaternion.Y, quaternion.Z}; }
    #pragma endregion Quaternion
}