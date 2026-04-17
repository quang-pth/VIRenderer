#pragma once

#include"Core/Math/Math.h"
#include"Core/Math/Vector2.h"
#include"Core/Math/Vector3.h"

namespace VIEngine::Math {
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
}