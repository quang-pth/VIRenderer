#pragma once

#include"Core/Math/Math.h"

namespace VIEngine::Math {
    class Vector2;
    class Vector3;
    class Matrix3;
    class Matrix4;
    class Quaternion;

    #pragma region Vector2
    // ベクトルの長さの二乗を計算する
    float GetLengthSquared(const Vector2& vector);
    // ベクトルの長さを計算する
    float GetLength(const Vector2& vector);
    // ベクトルを正規化するが、長さが0かどうかのチェックは行わない
    void Normalize(Vector2& vector);
    // ベクトルを正規化するが、epsilonで長さが0に近いかどうかを判断し、近い場合はゼロベクトルにする
    void SafeNormalize(Vector2& vector, float epsilon = BASE_EPSILON);
    // ベクトルを正規化した新しいベクトルを返すが、長さが0かどうかのチェックは行わない
    Vector2 GetNormalize(const Vector2& vector);
    // ベクトルを正規化した新しいベクトルを返すが、epsilonで長さが0に近いかどうかを判断し、近い場合はゼロベクトルを返す
    Vector2 GetSafeNormalize(const Vector2& vector, float epsilon = BASE_EPSILON);
    // 2つのベクトルの内積を計算する
    float Dot(const Vector2& lhs, const Vector2& rhs);
    // 2つのベクトルを線形補間する
    Vector2 Lerp(const Vector2& source, const Vector2& destination, float t);
    // ベクトルを法線ベクトルで反射させる
    Vector2 Reflect(const Vector2& vector, const Vector2& normal);
    // ベクトルの値へのポインタを取得する
    const float* GetValuePtr(const Vector2& vector);
    #pragma endregion Vector2

    #pragma region Vector3
    // ベクトルの長さの二乗を計算する
    float GetLengthSquared(const Vector3& vector);
    // ベクトルの長さを計算する
    float GetLength(const Vector3& vector);
    // ベクトルを正規化するが、長さが0かどうかのチェックは行わない
    void Normalize(Vector3& vector);
    // ベクトルを正規化するが、epsilonで長さが0に近いかどうかを判断し、近い場合はゼロベクトルにする
    void SafeNormalize(Vector3& vector, float epsilon = BASE_EPSILON);
    // ベクトルを正規化した新しいベクトルを返すが、長さが0かどうかのチェックは行わない
    Vector3 GetNormalize(const Vector3& vector);
    // ベクトルを正規化した新しいベクトルを返すが、epsilonで長さが0に近いかどうかを判断し、近い場合はゼロベクトルを返す
    Vector3 GetSafeNormalize(const Vector3& vector, float epsilon = BASE_EPSILON);
    // 2つのベクトルの内積を計算する
    float Dot(const Vector3& lhs, const Vector3& rhs);
    // 2つのベクトルを線形補間する
    Vector3 Lerp(const Vector3& source, const Vector3& destination, float t);
    // ベクトルを法線ベクトルで反射させる
    Vector3 Reflect(const Vector3& vector, const Vector3& normal);
    // ベクトルの値へのポインタを取得する
    const float* GetValuePtr(const Vector3& vector);
    // 2つのベクトルの外積を計算する
    Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
    #pragma endregion Vector3

    #pragma region Matrix3
    // 行列を転置する
    void Transpose(Matrix3& matrix);
    // 行列の転置を返す
    Matrix3 GetTranspose(const Matrix3& matrix);
    // 行列の値へのポインタを取得する
    const float* GetValuePtr(const Matrix3& vector);
    // x,y方向のスケーリング行列を作成する
    Matrix3 CreateScale(float x, float y);
    // x,y方向の同一スケーリング行列を作成する
    Matrix3 CreateScale(float k);
    // z軸回転行列を作成する
    Matrix3 CreateRotation(float theta);
    // 2D平行移動行列を作成する
    Matrix3 CreateTranslation(float x, float y);
    // 2D平行移動行列を作成する
    Matrix3 CreateTranslation(const Vector2& position);
    #pragma endregion Matrix3

    #pragma region Matrix4
    // 行列を転置する
    void Transpose(Matrix4& matrix);
    // 行列の転置を返す
    Matrix4 GetTranspose(const Matrix4& matrix);
    // 行列の値へのポインタを取得する
    const float* GetValuePtr(const Matrix4& vector);
    // x,y,z方向のスケーリング行列を作成する
    Matrix4 CreateScale(float x, float y, float z);
    // x,y,z方向の同一スケーリング行列を作成する
    Matrix4 CreateUScale(float k);
    // 回転軸と回転角から回転行列を作成する
    Matrix4 CreateRotation(float theta, const Vector3& axis);
    // クォータニオンから回転行列を作成する
    Matrix4 CreateRotation(const Quaternion& quaternion);
    // x軸回転行列を作成する
    Matrix4 CreateRotationX(float theta);
    // y軸回転行列を作成する
    Matrix4 CreateRotationY(float theta);
    // z軸回転行列を作成する
    Matrix4 CreateRotationZ(float theta);
    // 2D平行移動行列を作成する
    Matrix4 CreateTranslation(float x, float y, float z);
    // 2D平行移動行列を作成する
    Matrix4 CreateTranslation(const Vector3& position);
    // カメラの位置、注視点、ワールドアップベクトルからビュー行列を作成する
    Matrix4 CreateLookAt(const Vector3& position, const Vector3& target, const Vector3& worldUp);
    // // 幅、高さ、近面、遠面から正射影行列を作成する
    Matrix4 CreateOrtho(float width, float height, float near, float far);
    // // 視野角（ラジアン）、アスペクト比、近面、遠面から透視投影行列を作成する
    Matrix4 CreatePerspective(float fieldOfView, float aspectRatio, float near, float far);
    #pragma endregion Matrix4

    #pragma region Quaternion
    // クォータニオンを反転する
    void Invert(Quaternion& quaternion);
    // クォータニオンの反転を返す。XYZ成分は同じで、W成分が符号反転したクォータニオンになる
    Quaternion GetInvert(const Quaternion& quaternion);
    // クォータニオンq1からq2への回転を表すクォータニオンを返す
    Quaternion Difference(const Quaternion& q1, const Quaternion& q2);
    // クォータニオンを球面線形補間する
    Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
    // クォータニオンを線形補間する
    Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
    // クォータニオンを指数関数的に変化させる
    void Exponent(Quaternion& quaternion, float exp);
    // クォータニオンを指数関数的に変化させた新しいクォータニオンを返す
    Quaternion GetExponent(const Quaternion& quaternion, float exp);
    // クォータニオンが単位クォータニオンかどうかを判断する
    bool IsIdentity(const Quaternion& quaternion);
    // 2つのクォータニオンの内積を計算する
    float Dot(const Quaternion& q1, const Quaternion& q2);
    // クォータニオンの値へのポインタを取得する
    const float* GetValuePtr(const Quaternion& quaternion);
    #pragma endregion Quaternion
}