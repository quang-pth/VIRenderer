#pragma once

#include<gtest/gtest.h>
#include<glm/glm.hpp>
#include<glm/gtc/epsilon.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Core/Math/Math.h"
#include"Core/Math/Compute.h"
#include"Core/Math/Vector2.h"
#include"Core/Math/Vector3.h"
#include"Core/Math/Vector4.h"
#include"Core/Math/Matrix3.h"
#include"Core/Math/Matrix4.h"

#define EXPECT_VEC2_EQ(v_eng, v_glm) \
    EXPECT_FLOAT_EQ(v_eng.X, v_glm.x); \
    EXPECT_FLOAT_EQ(v_eng.Y, v_glm.y)

#define EXPECT_VEC2_NEAR(v_engine, v_glm, abs_error) \
    EXPECT_NEAR(v_engine.X, v_glm.x, abs_error); \
    EXPECT_NEAR(v_engine.Y, v_glm.y, abs_error)

#define EXPECT_VEC3_NEAR(v_engine, v_glm, abs_error) \
    EXPECT_NEAR(v_engine.X, v_glm.x, abs_error); \
    EXPECT_NEAR(v_engine.Y, v_glm.y, abs_error); \
    EXPECT_NEAR(v_engine.Z, v_glm.z, abs_error)

#define EXPECT_VEC3_EQ(v_eng, v_glm) \
    EXPECT_FLOAT_EQ(v_eng.X, v_glm.x); \
    EXPECT_FLOAT_EQ(v_eng.Y, v_glm.y); \
    EXPECT_FLOAT_EQ(v_eng.Z, v_glm.Z)

namespace Test {
    constexpr float BASE_EPSILON = 1e-6f;

    #pragma region Vector4
    static void ExpectVectorEqual(const VIEngine::Math::Vector4& lhs, const  VIEngine::Math::Vector4& rhs, float epsilon = BASE_EPSILON) {
        for (uint8_t i = 0; i < 4; ++i) {
            EXPECT_NEAR(lhs[i], rhs[i], epsilon);
        }
    }
    #pragma endregion Vector4

    #pragma region Matrix3
    static void ExpectMatrixNear(const VIEngine::Math::Matrix3& matrix, const glm::mat3& glmMatrix, float epsilon = BASE_EPSILON) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                EXPECT_NEAR(matrix[i][j], glmMatrix[i][j], epsilon);
            }
        }
    }

    static void ExpectMatrixNear(const VIEngine::Math::Matrix3& lhs, const VIEngine::Math::Matrix3& rhs, float epsilon = BASE_EPSILON) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                EXPECT_NEAR(lhs[i][j], rhs[i][j], epsilon);
            }
        }
    }

    static void ExpectMatrixNear(const glm::mat3& lhs, const glm::mat3& rhs, float epsilon = BASE_EPSILON) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                EXPECT_NEAR(lhs[i][j], rhs[i][j], epsilon);
            }
        }
    }
    #pragma endregion Matrix3

    #pragma region Matrix4
    static void ExpectMatrixNear(const VIEngine::Math::Matrix4& matrix, const glm::mat4& glmMatrix, float epsilon = BASE_EPSILON) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_NEAR(matrix[i][j], glmMatrix[i][j], epsilon);
            }
        }
    }

    static void ExpectMatrixNear(const VIEngine::Math::Matrix4& lhs, const VIEngine::Math::Matrix4& rhs, float epsilon = BASE_EPSILON) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_NEAR(lhs[i][j], rhs[i][j], epsilon);
            }
        }
    }

    static void ExpectMatrixNear(const glm::mat4& lhs, const glm::mat4& rhs, float epsilon = BASE_EPSILON) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_NEAR(lhs[i][j], rhs[i][j], epsilon);
            }
        }
    }
    #pragma endregion Matrix4
}