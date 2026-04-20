#include"Test/Core/Math/Helper.h"

namespace Test {
    using namespace VIEngine::Math;

    #pragma region Vector2MathTest
    TEST(Vector2MathTest, LengthAndDot) {
        Vector2 v(3.0f, 4.0f);
        glm::vec2 g(3.0f, 4.0f);

        EXPECT_FLOAT_EQ(GetLengthSquared(v), glm::dot(g, g));
        EXPECT_FLOAT_EQ(GetLengthSquared(v), 25.0f);

        EXPECT_FLOAT_EQ(GetLength(v), glm::length(g));
        EXPECT_FLOAT_EQ(GetLength(v), 5.0f);

        Vector2 v2(-1.0f, 2.0f);
        glm::vec2 g2(-1.0f, 2.0f);
        EXPECT_FLOAT_EQ(Dot(v, v2), glm::dot(g, g2)); 
    }

    TEST(Vector2MathTest, NormalizationAgainstGLM) {
        Vector2 v(10.0f, -5.0f);
        glm::vec2 g(10.0f, -5.0f);

        Vector2 vNorm = GetNormalize(v);
        glm::vec2 gNorm = glm::normalize(g);
        EXPECT_VEC2_NEAR(vNorm, gNorm, BASE_EPSILON);

        Vector2 vInPlace = v;
        Normalize(vInPlace);
        EXPECT_VEC2_NEAR(vInPlace, gNorm, BASE_EPSILON);

        Vector2 vZero(0.0f, 0.0f);
        Vector2 vSafe = GetSafeNormalize(vZero);
        EXPECT_FLOAT_EQ(vSafe.X, 0.0f);
        EXPECT_FLOAT_EQ(vSafe.Y, 0.0f);
    }

    TEST(Vector2MathTest, LerpAgainstGLM) {
        Vector2 start(0.0f, 0.0f);
        Vector2 end(10.0f, 5.0f);
        glm::vec2 gStart(0.0f, 0.0f);
        glm::vec2 gEnd(10.0f, 5.0f);
        
        float t = 0.35f;
        Vector2 vRes = Lerp(start, end, t);
        glm::vec2 gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, BASE_EPSILON);

        t = 0;
        vRes = Lerp(start, end, t);
        gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, BASE_EPSILON);
        
        t = 1;
        vRes = Lerp(start, end, t);
        gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, BASE_EPSILON);
    }

    TEST(Vector2MathTest, ReflectAgainstGLM) {
        Vector2 incident(1.0f, -1.0f);
        Vector2 normal(0.0f, 1.0f); 
        glm::vec2 gIncident(1.0f, -1.0f);
        glm::vec2 gNormal(0.0f, 1.0f);

        Vector2 vRef = Reflect(incident, normal);
        glm::vec2 gRef = glm::reflect(gIncident, gNormal);

        EXPECT_VEC2_NEAR(vRef, gRef, BASE_EPSILON);
    }

    TEST(Vector2MathTest, PointerAndAccess) {
        Vector2 v(1.23f, 4.56f);
        const float* ptr = GetValuePtr(v);

        ASSERT_NE(ptr, nullptr);
        EXPECT_EQ(ptr[0], v.X);
        EXPECT_EQ(ptr[1], v.Y);
        
        glm::vec2 g(1.23f, 4.56f);
        float* gPtr = glm::value_ptr(g);
        EXPECT_FLOAT_EQ(ptr[0], gPtr[0]);
        EXPECT_FLOAT_EQ(ptr[1], gPtr[1]);
    }

    TEST(Vector2MathTest, SafeNormalizeThreshold) {
        float eps = 0.001f;
        Vector2 tiny(0.0005f, 0.0f);
        
        Vector2 res = GetSafeNormalize(tiny, eps);
        EXPECT_FLOAT_EQ(res.X, 0.0f);
        EXPECT_FLOAT_EQ(res.Y, 0.0f);
        
        Vector2 notTiny(0.002f, 0.0f); 
        Vector2 res2 = GetSafeNormalize(notTiny, eps);
        EXPECT_NEAR(res2.X, 1.0f, BASE_EPSILON);
    }
    #pragma endregion Vector2MathTest

    #pragma region Vector3MathTest
    TEST(Vector3MathTest, LengthAndDot) {
        Vector3 v(3.0f, 4.0f, 5.0f);
        glm::vec3 g(3.0f, 4.0f, 5.0f);

        EXPECT_FLOAT_EQ(GetLengthSquared(v), glm::dot(g, g));
        EXPECT_FLOAT_EQ(GetLengthSquared(v), 50.0f);

        EXPECT_FLOAT_EQ(GetLength(v), glm::length(g));

        Vector3 v2(-1.0f, 2.0f, 3.0f);
        glm::vec3 g2(-1.0f, 2.0f, 3.0f);
        EXPECT_FLOAT_EQ(Dot(v, v2), glm::dot(g, g2)); 
    }

    TEST(Vector3MathTest, NormalizationAgainstGLM) {
        Vector3 v(10.0f, -5.0f, 6.7f);
        glm::vec3 g(10.0f, -5.0f, 6.7f);

        Vector3 vNorm = GetNormalize(v);
        glm::vec3 gNorm = glm::normalize(g);
        EXPECT_VEC2_NEAR(vNorm, gNorm, BASE_EPSILON);

        Vector3 vInPlace = v;
        Normalize(vInPlace);
        EXPECT_VEC2_NEAR(vInPlace, gNorm, BASE_EPSILON);

        Vector3 vZero(0.0f);
        Vector3 vSafe = GetSafeNormalize(vZero);
        EXPECT_FLOAT_EQ(vSafe.X, 0.0f);
        EXPECT_FLOAT_EQ(vSafe.Y, 0.0f);
        EXPECT_FLOAT_EQ(vSafe.Z, 0.0f);
    }

    TEST(Vector3MathTest, LerpAgainstGLM) {
        Vector3 start(-1.0f, -5.2f, 10.35f);
        Vector3 end(10.0f, 5.0f, 20.0f);
        glm::vec3 gStart(-1.0f, -5.2f, 10.35);
        glm::vec3 gEnd(10.0f, 5.0f, 20.0f);
        
        float t = 0.35f;
        Vector3 vRes = Lerp(start, end, t);
        glm::vec3 gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, BASE_EPSILON);

        t = 0;
        vRes = Lerp(start, end, t);
        gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, BASE_EPSILON);
        
        t = 1;
        vRes = Lerp(start, end, t);
        gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, BASE_EPSILON);
    }

    TEST(Vector3MathTest, ReflectAgainstGLM) {
        Vector3 incident(1.0f, -1.0f, 5.0f);
        Vector3 normal(0.0f, 1.0f, 1.0f); 
        glm::vec3 gIncident(1.0f, -1.0f, 5.0f);
        glm::vec3 gNormal(0.0f, 1.0f, 1.0f);

        Vector3 vRef = Reflect(incident, normal);
        glm::vec3 gRef = glm::reflect(gIncident, gNormal);

        EXPECT_VEC2_NEAR(vRef, gRef, BASE_EPSILON);
    }

    TEST(Vector3MathTest, PointerAndAccess) {
        Vector3 v(1.23f, 4.56f, 5.0f);
        const float* ptr = GetValuePtr(v);

        ASSERT_NE(ptr, nullptr);
        EXPECT_EQ(ptr[0], v.X);
        EXPECT_EQ(ptr[1], v.Y);
        EXPECT_EQ(ptr[2], v.Z);
        
        glm::vec3 g(1.23f, 4.56f, 5.0f);
        float* gPtr = glm::value_ptr(g);
        EXPECT_FLOAT_EQ(ptr[0], gPtr[0]);
        EXPECT_FLOAT_EQ(ptr[1], gPtr[1]);
        EXPECT_FLOAT_EQ(ptr[2], gPtr[2]);
    }

    TEST(Vector3MathTest, SafeNormalizeThreshold) {
        float eps = 0.001f;
        Vector3 tiny(0.0005f, 0.0f, 0.0f);
        
        Vector3 res = GetSafeNormalize(tiny, eps);
        EXPECT_FLOAT_EQ(res.X, 0.0f);
        EXPECT_FLOAT_EQ(res.Y, 0.0f);
        EXPECT_FLOAT_EQ(res.Z, 0.0f);
        
        Vector3 notTiny(0.002f, 0.0f, 0.0f); 
        Vector3 res2 = GetSafeNormalize(notTiny, eps);
        EXPECT_NEAR(res2.X, 1.0f, BASE_EPSILON);
    }
    #pragma endregion Vector3MathTest

    #pragma region Matrix3MathTest
    TEST(Matrix3Test, TransposeAgainstGLM) {
        float values[3][3] = {
            {1, 2, 3}, 
            {4, 5, 6}, 
            {7, 8, 9}
        }; 
        Matrix3 m{&values[0][0]};

        glm::mat3 gm = glm::mat3(
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
        );
        ExpectMatrix3Near(m, glm::transpose(gm)); 
        
        Matrix3 transposed = GetTranspose(m);
        ExpectMatrix3Near(transposed, gm); 

        Transpose(m);
        ExpectMatrix3Near(m, gm);
    }

    TEST(Matrix3Test, TransposeSpecialMatrices) {
        Matrix3 identity = Matrix3::Identity; 
        Matrix3 identityT = GetTranspose(identity);
        ExpectMatrix3Near(identityT, glm::mat3(1.0f));

        float values[3][3] = {
            {1, 0, 2}, 
            {0, 3, 4},
            {2, 4, 5}
        };
        Matrix3 sym{&values[0][0]};
        Matrix3 symT = GetTranspose(sym);
        ExpectMatrix3Near(sym, symT);
    }

    TEST(Matrix3Test, TransposeDoubleFlip) {
        float values[3][3] = {
            {1, 0, 2}, 
            {0, 3, 4}, 
            {2, 4, 5}
        };
        Matrix3 matrix{&values[0][0]};
        Matrix3 tranposeMatrix = GetTranspose(GetTranspose(matrix));
        ExpectMatrix3Near(matrix, tranposeMatrix);
    }

    TEST(Matrix3Test, GetValuePtr) {
        float values[3][3] = {
            {1, 0, 2}, 
            {0, 3, 4}, 
            {2, 4, 5}
        };
        Matrix3 matrix{&values[0][0]};
        const float* matrixPtr = GetValuePtr(matrix);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                EXPECT_EQ(matrixPtr[i * 3 + j], matrix[i][j]);
            }
        }
    }

    TEST(Matrix3Test, CreateScale) {
        float sx = 2.0f, sy = 3.0f;
        Matrix3 scaleMatrix = CreateScale(sx, sy);
        float expected[3][3] = {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(scaleMatrix, glm::make_mat3(&expected[0][0]));

        // 0.5倍のスケーリングもテスト
        sx = 0.5f; sy = 0.5f;
        scaleMatrix = CreateScale(sx, sy);
        float expectedHalf[3][3] = {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(scaleMatrix, glm::make_mat3(&expectedHalf[0][0]));

        // 負のスケーリングもテスト
        sx = -1.0f; sy = -2.0f;
        scaleMatrix = CreateScale(sx, sy);
        float expectedNegative[3][3] = {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(scaleMatrix, glm::make_mat3(&expectedNegative[0][0]));
    }

    TEST(Matrix3Test, CreateUniformScale) {
        float k = 2.5f;
        Matrix3 scaleMatrix = CreateScale(k);
        float expected[3][3] = {
            {k, 0.0f, 0.0f},
            {0.0f, k, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(scaleMatrix, glm::make_mat3(&expected[0][0]));

        // 0.5倍のスケーリングもテスト
        k = 0.5f;
        scaleMatrix = CreateScale(k);
        float expectedHalf[3][3] = {
            {k, 0.0f, 0.0f},
            {0.0f, k, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(scaleMatrix, glm::make_mat3(&expectedHalf[0][0]));

        // 負のスケーリングもテスト
        k = -1.0f;
        scaleMatrix = CreateScale(k);
        float expectedNegative[3][3] = {
            {k, 0.0f, 0.0f},
            {0.0f, k, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(scaleMatrix, glm::make_mat3(&expectedNegative[0][0]));
    }

    TEST(Matrix3Test, CreateRotation) {
        float angle = ToRadians(45.0f);
        Matrix3 rotationMatrix = CreateRotation(angle);
        float c = Cos(angle);
        float s = Sin(angle);
        float expected[3][3] = {
            {c, s, 0.0f},
            {-s, c, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(rotationMatrix, glm::make_mat3(&expected[0][0]));

        // 90度回転もテスト
        angle = ToRadians(90.0f);
        rotationMatrix = CreateRotation(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected90[3][3] = {
            {c, s, 0.0f},
            {-s, c, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(rotationMatrix, glm::make_mat3(&expected90[0][0]));

        // 0度回転もテスト
        angle = ToRadians(0.0f);
        rotationMatrix = CreateRotation(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected0[3][3] = {
            {c, s, 0.0f},
            {-s, c, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrix3Near(rotationMatrix, glm::make_mat3(&expected0[0][0]));
    }

    TEST(Matrix3Test, CreateTranslation) {
        float tx = 5.0f, ty = -3.0f;
        Matrix3 translationMatrix = CreateTranslation(tx, ty);
        float expected[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {tx, ty, 1.0f}
        };
        ExpectMatrix3Near(translationMatrix, glm::make_mat3(&expected[0][0]));

        // 原点への平行移動もテスト
        tx = 0.0f; ty = 0.0f;
        translationMatrix = CreateTranslation(tx, ty);
        float expectedOrigin[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {tx, ty, 1.0f}
        };
        ExpectMatrix3Near(translationMatrix, glm::make_mat3(&expectedOrigin[0][0]));

        // 負の平行移動もテスト
        tx = -2.0f; ty = -4.0f;
        translationMatrix = CreateTranslation(tx, ty);
        float expectedNegative[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {tx, ty, 1.0f}
        };
        ExpectMatrix3Near(translationMatrix, glm::make_mat3(&expectedNegative[0][0]));
    }
    #pragma endregion Matrix3MathTest
}