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
        ExpectMatrixNear(m, glm::transpose(gm)); 
        
        Matrix3 transposed = GetTranspose(m);
        ExpectMatrixNear(transposed, gm); 

        Transpose(m);
        ExpectMatrixNear(m, gm);
    }

    TEST(Matrix3Test, TransposeSpecialMatrices) {
        Matrix3 identity = Matrix3::Identity; 
        Matrix3 identityT = GetTranspose(identity);
        ExpectMatrixNear(identityT, glm::mat3(1.0f));

        float values[3][3] = {
            {1, 0, 2}, 
            {0, 3, 4},
            {2, 4, 5}
        };
        Matrix3 sym{&values[0][0]};
        Matrix3 symT = GetTranspose(sym);
        ExpectMatrixNear(sym, symT);
    }

    TEST(Matrix3Test, TransposeDoubleFlip) {
        float values[3][3] = {
            {1, 0, 2}, 
            {0, 3, 4}, 
            {2, 4, 5}
        };
        Matrix3 matrix{&values[0][0]};
        Matrix3 tranposeMatrix = GetTranspose(GetTranspose(matrix));
        ExpectMatrixNear(matrix, tranposeMatrix);
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

    TEST(Matrix3Test, CreateScale2D) {
        float sx = 2.0f, sy = 3.0f;
        Matrix3 scaleMatrix = CreateScale2D(sx, sy);
        float expected[3][3] = {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat3(&expected[0][0]));

        // 0.5倍のスケーリングもテスト
        sx = 0.5f; sy = 0.5f;
        scaleMatrix = CreateScale2D(sx, sy);
        float expectedHalf[3][3] = {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat3(&expectedHalf[0][0]));

        // 負のスケーリングもテスト
        sx = -1.0f; sy = -2.0f;
        scaleMatrix = CreateScale2D(sx, sy);
        float expectedNegative[3][3] = {
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat3(&expectedNegative[0][0]));
    }

    TEST(Matrix3Test, CreateUniformScale2D) {
        float k = 2.5f;
        Matrix3 scaleMatrix = CreateScale2D(k);
        float expected[3][3] = {
            {k, 0.0f, 0.0f},
            {0.0f, k, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat3(&expected[0][0]));

        // 0.5倍のスケーリングもテスト
        k = 0.5f;
        scaleMatrix = CreateScale2D(k);
        float expectedHalf[3][3] = {
            {k, 0.0f, 0.0f},
            {0.0f, k, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat3(&expectedHalf[0][0]));

        // 負のスケーリングもテスト
        k = -1.0f;
        scaleMatrix = CreateScale2D(k);
        float expectedNegative[3][3] = {
            {k, 0.0f, 0.0f},
            {0.0f, k, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat3(&expectedNegative[0][0]));
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
        ExpectMatrixNear(rotationMatrix, glm::make_mat3(&expected[0][0]));

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
        ExpectMatrixNear(rotationMatrix, glm::make_mat3(&expected90[0][0]));

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
        ExpectMatrixNear(rotationMatrix, glm::make_mat3(&expected0[0][0]));
    }

    TEST(Matrix3Test, CreateTranslation) {
        float tx = 5.0f, ty = -3.0f;
        Matrix3 translationMatrix = CreateTranslation(tx, ty);
        float expected[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {tx, ty, 1.0f}
        };
        ExpectMatrixNear(translationMatrix, glm::make_mat3(&expected[0][0]));

        // 原点への平行移動もテスト
        tx = 0.0f; ty = 0.0f;
        translationMatrix = CreateTranslation(tx, ty);
        float expectedOrigin[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {tx, ty, 1.0f}
        };
        ExpectMatrixNear(translationMatrix, glm::make_mat3(&expectedOrigin[0][0]));

        // 負の平行移動もテスト
        tx = -2.0f; ty = -4.0f;
        translationMatrix = CreateTranslation(tx, ty);
        float expectedNegative[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {tx, ty, 1.0f}
        };
        ExpectMatrixNear(translationMatrix, glm::make_mat3(&expectedNegative[0][0]));
    }
    
    TEST(Matrix3Test, IsOrthonormal) {
        float values[3][3] = {
            {1, 0, 0}, 
            {0, 2, 0}, 
            {0, 0, 3}
        };
        Matrix3 orthonormalMatrix = Matrix3(values);
        EXPECT_TRUE(IsOrthonormal(orthonormalMatrix));
    }

    TEST(Matrix3Test, IsOrthonormalIdentityMatrix) {
        Matrix3 orthonormalMatrix = Matrix3::Identity;
        EXPECT_TRUE(IsOrthonormal(orthonormalMatrix));
    }

    TEST(Matrix3Test, IsNotOrthonormal) {
        float values[3][3] = {
            {1.0f, 2.0f, 3.0f},
            {0.0f, 1.0f, 4.0f},
            {5.0f, 6.0f, 0.0f}
        };
        Matrix3 nonOrthonormalMatrix = Matrix3(values);
        EXPECT_FALSE(IsOrthonormal(nonOrthonormalMatrix));
    }
    #pragma endregion Matrix3MathTest

    #pragma region Matrix4MathTest
    TEST(Matrix4Test, TransposeAgainstGLM) {
        float values[4][4] = {
            {1, 2, 3, 4}, 
            {5, 6, 7, 8}, 
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        }; 
        Matrix4 m{&values[0][0]};

        glm::mat4 gm = glm::mat4(
            1, 5, 9, 13,
            2, 6, 10,14,
            3, 7, 11,15,
            4, 8, 12,16
        );
        ExpectMatrixNear(m, glm::transpose(gm)); 
        
        Matrix4 transposed = GetTranspose(m);
    }

    TEST(Matrix4Test, TransposeSpecialMatrices) {
        Matrix4 identity = Matrix4::Identity; 
        Matrix4 identityT = GetTranspose(identity);
        ExpectMatrixNear(identityT, glm::mat4(1.0f));

        float values[4][4] = {
            {1, 0, 2, 0}, 
            {0, 3, 4, 0},
            {2, 4, 5, 0},
            {0, 0, 0, 1}
        };
        Matrix4 sym{&values[0][0]};
        Matrix4 symT = GetTranspose(sym);
        ExpectMatrixNear(sym, symT);
    }

    TEST(Matrix4Test, TransposeDoubleFlip) {
        float values[4][4] = {
            {1, 0, 2, 0}, 
            {0, 3, 4, 0}, 
            {2, 4, 5, 0},
            {0, 0, 0, 1}
        };
        Matrix4 matrix{&values[0][0]};
        Matrix4 tranposeMatrix = GetTranspose(GetTranspose(matrix));
        ExpectMatrixNear(matrix, tranposeMatrix);
    }

    TEST(Matrix4Test, GetValuePtr) {
        float values[4][4] = {
            {1, 0, 2, 0}, 
            {0, 3, 4, 0}, 
            {2, 4, 5, 0},
            {0, 0, 0, 1}
        };
        Matrix4 matrix{&values[0][0]};
        const float* matrixPtr = GetValuePtr(matrix);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_EQ(matrixPtr[i * 4 + j], matrix[i][j]);
            }
        }
    }

    TEST(Matrix4Test, CreateScale3D) {
        float sx = 2.0f, sy = 3.0f, sz = 4.0f;
        Matrix4 scaleMatrix = CreateScale3D(sx, sy, sz);
        float expected[4][4] = {
            {sx, 0.0f, 0.0f, 0.0f},
            {0.0f, sy, 0.0f, 0.0f},
            {0.0f, 0.0f, sz, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expected[0][0]));

        // 0.5倍のスケーリングもテスト
        sx = 0.5f; sy = 0.5f; sz = 0.5f;
        scaleMatrix = CreateScale3D(sx, sy, sz);
        float expectedHalf[4][4] = {
            {sx, 0.0f, 0.0f, 0.0f},
            {0.0f, sy, 0.0f, 0.0f},
            {0.0f, 0.0f, sz, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expectedHalf[0][0]));

        // 負のスケーリングもテスト
        sx = -1.0f; sy = -2.0f; sz = -3.0f;
        scaleMatrix = CreateScale3D(sx, sy, sz);
        float expectedNegative[4][4] = {
            {sx, 0.0f, 0.0f, 0.0f},
            {0.0f, sy, 0.0f, 0.0f},
            {0.0f, 0.0f, sz, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expectedNegative[0][0]));

        // 負のスケーリングもテスト
        sx = -1.0f; sy = -2.0f; sz = -3.0f;
        scaleMatrix = CreateScale3D(sx, sy, sz);
        float expectedNegative2[4][4] = {
            {sx, 0.0f, 0.0f, 0.0f},
            {0.0f, sy, 0.0f, 0.0f},
            {0.0f, 0.0f, sz, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expectedNegative2[0][0]));
    }

    TEST(Matrix4Test, CreateUniformScale3D) {
        float k = 2.5f;
        Matrix4 scaleMatrix = CreateScale3D(k);
        float expected[4][4] = {
            {k, 0.0f, 0.0f, 0.0f},
            {0.0f, k, 0.0f, 0.0f},
            {0.0f, 0.0f, k, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expected[0][0]));

        // 0.5倍のスケーリングもテスト
        k = 0.5f;
        scaleMatrix = CreateScale3D(k);
        float expectedHalf[4][4] = {
            {k, 0.0f, 0.0f, 0.0f},
            {0.0f, k, 0.0f, 0.0f},
            {0.0f, 0.0f, k, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expectedHalf[0][0]));

        // 負のスケーリングもテスト
        k = -1.0f;
        scaleMatrix = CreateScale3D(k);
        float expectedNegative[4][4] = {
            {k, 0.0f, 0.0f, 0.0f},
            {0.0f, k, 0.0f, 0.0f},
            {0.0f, 0.0f, k, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(scaleMatrix, glm::make_mat4(&expectedNegative[0][0]));
    }
    
    TEST(Matrix4Test, CreateRotationFromQuaternion) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Matrix4 rotation = CreateRotation(angle, axis);
        glm::mat4 glmRotation = glm::rotate(glm::mat4(1.0f), angle, glm::make_vec3(GetValuePtr(axis)));
        ExpectMatrixNear(rotation, glmRotation);
    }

    TEST(Matrix4Test, CreateRotationFromQuaternionX) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 0.0f, 0.0f);
        Normalize(axis);
        Matrix4 rotation = CreateRotation(angle, axis);
        glm::mat4 glmRotation = glm::rotate(glm::mat4(1.0f), angle, glm::make_vec3(GetValuePtr(axis)));
        ExpectMatrixNear(rotation, glmRotation);
    }

    TEST(Matrix4Test, CreateRotationFromQuaternionY) {
        float angle = ToRadians(45.0f);
        Vector3 axis(0.0f, 1.0f, 0.0f);
        Normalize(axis);
        Matrix4 rotation = CreateRotation(angle, axis);
        glm::mat4 glmRotation = glm::rotate(glm::mat4(1.0f), angle, glm::make_vec3(GetValuePtr(axis)));
        ExpectMatrixNear(rotation, glmRotation);
    }

    TEST(Matrix4Test, CreateRotationFromQuaternionZ) {
        float angle = ToRadians(45.0f);
        Vector3 axis(0.0f, 0.0f, 1.0f);
        Normalize(axis);
        Matrix4 rotation = CreateRotation(angle, axis);
        glm::mat4 glmRotation = glm::rotate(glm::mat4(1.0f), angle, glm::make_vec3(GetValuePtr(axis)));
        ExpectMatrixNear(rotation, glmRotation);
    }

    TEST(Matrix4Test, CreateRotationX) {
        float angle = ToRadians(45.0f);
        Matrix4 rotationMatrix = CreateRotationX(angle);
        float c = Cos(angle);
        float s = Sin(angle);
        float expected[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, c, s, 0.0f},
            {0.0f, -s, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected[0][0]));

        // 90度回転もテスト
        angle = ToRadians(90.0f);
        rotationMatrix = CreateRotationX(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected90[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, c, s, 0.0f},
            {0.0f, -s, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected90[0][0]));

        // 0度回転もテスト
        angle = ToRadians(0.0f);
        rotationMatrix = CreateRotationX(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected0[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, c, s, 0.0f},
            {0.0f, -s, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected0[0][0]));

        // 負の角度もテスト
        angle = ToRadians(-45.0f);
        rotationMatrix = CreateRotationX(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expectedNegative[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, c, s, 0.0f},
            {0.0f, -s, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expectedNegative[0][0]));

        // 360度回転もテスト
        angle = ToRadians(360.0f);
        rotationMatrix = CreateRotationX(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected360[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, c, s, 0.0f},
            {0.0f, -s, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected360[0][0]));
    }

    TEST(Matrix4Test, CreateRotationY) {
        float angle = ToRadians(45.0f);
        Matrix4 rotationMatrix = CreateRotationY(angle);
        float c = Cos(angle);
        float s = Sin(angle);
        float expected[4][4] = {
            {c, 0.0f, -s, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {s, 0.0f, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected[0][0]));

        // 90度回転もテスト
        angle = ToRadians(90.0f);
        rotationMatrix = CreateRotationY(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected90[4][4] = {
            {c, 0.0f, -s, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {s, 0.0f, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected90[0][0]));

        // 0度回転もテスト
        angle = ToRadians(0.0f);
        rotationMatrix = CreateRotationY(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected0[4][4] = {
            {c, 0.0f, -s, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {s, 0.0f, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected0[0][0]));

        // 負の角度もテスト
        angle = ToRadians(-45.0f);
        rotationMatrix = CreateRotationY(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expectedNegative[4][4] = {
            {c, 0.0f, -s, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {s, 0.0f, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expectedNegative[0][0]));

        // 360度回転もテスト
        angle = ToRadians(360.0f);
        rotationMatrix = CreateRotationY(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected360[4][4] = {
            {c, 0.0f, -s, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {s, 0.0f, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected360[0][0]));
    }

    TEST(Matrix4Test, CreateRotationZ) {
        float angle = ToRadians(45.0f);
        Matrix4 rotationMatrix = CreateRotationZ(angle);
        float c = Cos(angle);
        float s = Sin(angle);
        float expected[4][4] = {
            {c, s, 0.0f, 0.0f},
            {-s, c, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected[0][0]));

        // 90度回転もテスト
        angle = ToRadians(90.0f);
        rotationMatrix = CreateRotationZ(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected90[4][4] = {
            {c, s, 0.0f, 0.0f},
            {-s, c, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected90[0][0]));

        // 0度回転もテスト
        angle = ToRadians(0.0f);
        rotationMatrix = CreateRotationZ(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected0[4][4] = {
            {c, s, 0.0f, 0.0f},
            {-s, c, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected0[0][0]));

        // 負の角度もテスト
        angle = ToRadians(-45.0f);
        rotationMatrix = CreateRotationZ(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expectedNegative[4][4] = {
            {c, s, 0.0f, 0.0f},
            {-s, c, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expectedNegative[0][0]));

        // 360度回転もテスト
        angle = ToRadians(360.0f);
        rotationMatrix = CreateRotationZ(angle);
        c = Cos(angle);
        s = Sin(angle);
        float expected360[4][4] = {
            {c, s, 0.0f, 0.0f},
            {-s, c, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        ExpectMatrixNear(rotationMatrix, glm::make_mat4(&expected360[0][0]));
    }

    TEST(Matrix4Test, CreateTranslation) {
        float tx = 5.0f, ty = -3.0f, tz = 2.0f;
        Matrix4 translationMatrix = CreateTranslation(tx, ty, tz);
        float expected[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {tx, ty, tz, 1.0f}
        };
        ExpectMatrixNear(translationMatrix, glm::make_mat4(&expected[0][0]));

        // 原点への平行移動もテスト
        tx = 0.0f; ty = 0.0f; tz = 0.0f;
        translationMatrix = CreateTranslation(tx, ty, tz);
        float expectedOrigin[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {tx, ty, tz, 1.0f}
        };
        ExpectMatrixNear(translationMatrix, glm::make_mat4(&expectedOrigin[0][0]));

        // 負の平行移動もテスト
        tx = -2.0f; ty = -4.0f; tz = -1.0f;
        translationMatrix = CreateTranslation(tx, ty, tz);
        float expectedNegative[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {tx, ty, tz, 1.0f}
        };
        ExpectMatrixNear(translationMatrix, glm::make_mat4(&expectedNegative[0][0]));
    }

    TEST(Matrix4MathTest, CreateLookAt) {
        Vector3 position(0.0f, 0.0f, 0.0f);
        Vector3 target(0.0f, 0.0f, 1.0f);
        Vector3 up(0.0f, 1.0f, 0.0f);
        Matrix4 lookAtMatrix = CreateLookAt(position, target, up);
        glm::mat4 glmLookAt = glm::lookAt(
            glm::vec3(position.X, position.Y, position.Z),
            glm::vec3(target.X, target.Y, target.Z),
            glm::vec3(up.X, up.Y, up.Z)
        );
        ExpectMatrixNear(lookAtMatrix, glmLookAt);
    }

    TEST(Matrix4MathTest, LookAtTransform) {
        Vector3 position(0.0f, 0.0f, 0.0f);
        Vector3 target(0.0f, 0.0f, 1.0f);
        Vector3 up(0.0f, 1.0f, 0.0f);
        Matrix4 lookAtMatrix = CreateLookAt(position, target, up);
        Vector4 point(0.0f, 0.0f, 1.0f);
        Vector4 transformedPoint = point * lookAtMatrix;
        glm::mat4 glmLookAt = glm::lookAt(
            glm::vec3(position.X, position.Y, position.Z),
            glm::vec3(target.X, target.Y, target.Z),
            glm::vec3(up.X, up.Y, up.Z)
        );
        glm::vec4 expected = glmLookAt * glm::vec4(point.X, point.Y, point.Z, point.W);
        ExpectVectorEqual(transformedPoint, Vector4(expected.x, expected.y, expected.z, expected.w)); 
    }

    TEST(Matrix4MathTest, LookAtTransformTargetLeft) {
        Vector3 position(0.0f, 0.0f, 0.0f);
        Vector3 target(0.0f, 0.0f, 1.0f);
        Vector3 up(0.0f, 1.0f, 0.0f);
        Matrix4 lookAtMatrix = CreateLookAt(position, target, up);
        Vector4 point(-1.0f, 0.0f, 1.0f);
        Vector4 transformedPoint = point * lookAtMatrix;
        glm::mat4 glmLookAt = glm::lookAt(
            glm::vec3(position.X, position.Y, position.Z),
            glm::vec3(target.X, target.Y, target.Z),
            glm::vec3(up.X, up.Y, up.Z)
        );
        glm::vec4 expected = glmLookAt * glm::vec4(point.X, point.Y, point.Z, point.W);
        ExpectVectorEqual(transformedPoint, Vector4(expected.x, expected.y, expected.z, expected.w)); 
    }

    TEST(Matrix4MathTest, LookAtTransformTargetRight) {
        Vector3 position(0.0f, 0.0f, 0.0f);
        Vector3 target(0.0f, 0.0f, 1.0f);
        Vector3 up(0.0f, 1.0f, 0.0f);
        Matrix4 lookAtMatrix = CreateLookAt(position, target, up);
        Vector4 point(1.0f, 0.0f, 1.0f);
        Vector4 transformedPoint = point * lookAtMatrix;
        glm::mat4 glmLookAt = glm::lookAt(
            glm::vec3(position.X, position.Y, position.Z),
            glm::vec3(target.X, target.Y, target.Z),
            glm::vec3(up.X, up.Y, up.Z)
        );
        glm::vec4 expected = glmLookAt * glm::vec4(point.X, point.Y, point.Z, point.W);
        ExpectVectorEqual(transformedPoint, Vector4(expected.x, expected.y, expected.z, expected.w)); 
    }

    TEST(Matrix4MathTest, LookAtTransformTargetArbitrarily) {
        Vector3 position(1.0f, 2.0f, 3.0f);
        Vector3 target(4.0f, 5.0f, 6.0f);
        Vector3 up(0.0f, 1.0f, 0.0f);
        Matrix4 lookAtMatrix = CreateLookAt(position, target, up);
        Vector4 point(7.0f, 8.0f, 9.0f);
        Vector4 transformedPoint = point * lookAtMatrix;
        glm::mat4 glmLookAt = glm::lookAt(
            glm::vec3(position.X, position.Y, position.Z),
            glm::vec3(target.X, target.Y, target.Z),
            glm::vec3(up.X, up.Y, up.Z)
        );
        glm::vec4 expected = glmLookAt * glm::vec4(point.X, point.Y, point.Z, point.W);
        ExpectVectorEqual(transformedPoint, Vector4(expected.x, expected.y, expected.z, expected.w)); 
    }

    TEST(Matrix4MathTest, CreateOrtho) {
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        float expected[4][4] = {
            {2.0f / width, 0.0f, 0.0f, 0.0f},
            {0.0f, 2.0f / height, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f / (zFar - zNear), 0.0f},
            {0.0f, 0.0f, zNear / (zNear - zFar), 1.0f}
        };
        ExpectMatrixNear(orthoMatrix, Matrix4(expected));
    }

    TEST(Matrix4MathTest, OrthoTransform) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point(400.0f, 300.0f, 100.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_VEC4_NEAR(transformedPoint, expected, baseEpsilon);
    }

    TEST(Matrix4MathTest, OrthoTransformNegative) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point = Vector4(-400.0f, -300.0f, 100.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_VEC4_NEAR(transformedPoint, expected, baseEpsilon);
    }

    TEST(Matrix4MathTest, OrthoTransformHalf) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point = Vector4(200.0f, 150.0f, 50.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_NEAR(transformedPoint.X, expected.x, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Z, 0.5f, baseEpsilon);
        EXPECT_NEAR(transformedPoint.W, expected.w, baseEpsilon);
    }

    TEST(Matrix4MathTest, OrthoTransformHalfNegative) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point = Vector4(-200.0f, -150.0f, 50.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_NEAR(transformedPoint.X, expected.x, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Z, 0.5f, baseEpsilon);
        EXPECT_NEAR(transformedPoint.W, expected.w, baseEpsilon);
    }

    TEST(Matrix4MathTest, OrthoTransformWidthQuarter) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point = Vector4(100.0f, 75.0f, 25.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_NEAR(transformedPoint.X, expected.x, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Z, 0.25f, baseEpsilon);
        EXPECT_NEAR(transformedPoint.W, expected.w, baseEpsilon);
    }

    TEST(Matrix4MathTest, OrthoTransformWidthQuarterNegative) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point = Vector4(-100.0f, -75.0f, 25.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_NEAR(transformedPoint.X, expected.x, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Z, 0.25f, baseEpsilon);
        EXPECT_NEAR(transformedPoint.W, expected.w, baseEpsilon);
    }

    TEST(Matrix4MathTest, OrthoTransformOrigin) {
        float baseEpsilon = 0.001f;
        float width = 800.0f, height = 600.0f, zNear = 0.1f, zFar = 100.0f;
        Matrix4 orthoMatrix = CreateOrtho(width, height, zNear, zFar);
        Vector4 point = Vector4(0.0f, 0.0f, 0.0f);
        Vector4 transformedPoint = point * orthoMatrix;
        glm::mat4 glmOrtho = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -zNear, -zFar);
        glm::vec4 expected = glmOrtho * glm::vec4(point.X, point.Y, point.Z, point.W);
        EXPECT_NEAR(transformedPoint.X, expected.x, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y, baseEpsilon);
        EXPECT_NEAR(transformedPoint.Z, -0.001f, baseEpsilon);
        EXPECT_NEAR(transformedPoint.W, expected.w, baseEpsilon);
    }

    TEST(Matrix4MathTest, CreatePerspective) {
        float fov = ToRadians(60.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        float xScale = Cot(fov * 0.5f);
        float yScale = xScale * aspect;
        float expected[4][4] = {
            {xScale, 0.0f, 0.0f, 0.0f},
            {0.0f, yScale, 0.0f, 0.0f},
            {0.0f, 0.0f, zFar / (zFar - zNear), 1.0f},
            {0.0f, 0.0f, -zNear * zFar / (zFar - zNear), 0.0f}
        };
        ExpectMatrixNear(perspectiveMatrix, Matrix4(expected));
    }

    TEST(Matrix4Test, PerspectiveTransformAlpha90) {
        float fov = ToRadians(90.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(400.0f, 300.0f, 50.0f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);
        
        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 49.9499f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4Test, PerspectiveTransformBoundary) {
        float fov = ToRadians(90.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(50.0f, 50.0f, 50.0f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);

        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 49.9499f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4Test, PerspectiveTransformBoundaryNegative) {
        float fov = ToRadians(90.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(-50.0f, -50.0f, 50.0f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);

        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 49.9499f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4Test, PerspectiveTransformCenter) {
        float fov = ToRadians(90.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(0.0f, 0.0f, 50.0f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);

        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 49.9499f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4Test, PerspectiveTransformNearest) {
        float fov = ToRadians(90.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(0.0f, 0.0f, 0.1f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);

        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 0.0f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4Test, PerspectiveTransformFarest) {
        float fov = ToRadians(90.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(0.0f, 0.0f, 100.0f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);

        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 99.9999f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4Test, PerspectiveTransformAlpha60) {
        float fov = ToRadians(60.0f);
        float aspect = 800.0f / 600.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        // cot(fov / 2) = 1.73205
        // -> f / (f - n) = 1.001, -n * f / (f - n) = -0.1001
        Matrix4 perspectiveMatrix = CreatePerspective(fov, aspect, zNear, zFar);
        Vector4 point(2.0f, 1.0f, 10.0f);
        Vector4 transformedPoint = point * perspectiveMatrix;
        glm::mat4 glmPerspective = glm::perspective(fov, aspect, -zNear, -zFar);
        glm::vec4 expected = glmPerspective * glm::vec4(point.X, point.Y, point.Z, point.W);

        float epsilon = 0.0001;
        EXPECT_NEAR(transformedPoint.X, expected.x * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Y, expected.y * aspect, epsilon);
        EXPECT_NEAR(transformedPoint.Z, 9.9099f, epsilon);
        EXPECT_NEAR(transformedPoint.W, -expected.w, epsilon);
    }

    TEST(Matrix4MathTest, Invert) {
        float values[4][4] = {
            {1.0f, 2.0f, 3.0f, 0.0f},
            {0.0f, 1.0f, 4.0f, 0.0f},
            {5.0f, 6.0f, 0.0f, 0.0f},
            {7.0f, 8.0f, 9.0f, 1.0f}
        };
        bool invertedSuccess = false;
        Matrix4 original(values);
        Matrix4 invertedMatrix(values);
        Invert(invertedMatrix, invertedSuccess);
        Matrix4 identity = original * invertedMatrix;
        EXPECT_TRUE(invertedSuccess);
        ExpectMatrixNear(identity, Matrix4::Identity);
    }

    TEST(Matrix4MathTest, GetInvert) {
        float values[4][4] = {
            {1.0f, 2.0f, 3.0f, 0.0f},
            {0.0f, 1.0f, 4.0f, 0.0f},
            {5.0f, 6.0f, 0.0f, 0.0f},
            {7.0f, 8.0f, 9.0f, 1.0f}
        };
        bool invertedSuccess = false;
        Matrix4 original(values);
        Matrix4 invertedMatrix = GetInvert(original, invertedSuccess);
        Matrix4 identity = original * invertedMatrix;
        EXPECT_TRUE(invertedSuccess);
        ExpectMatrixNear(identity, Matrix4::Identity);
    }

    TEST(Matrix4MathTest, NotInvertable) {
        float notInvertable[4][4] = {
            {1.0f, 2.0f, 3.0f, 0.0f},
            {2.0f, 4.0f, 6.0f, 0.0f},
            {3.0f, 6.0f, 9.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        bool invertedSucess = false;
        Matrix4 original(notInvertable);
        Matrix4 invertMatrix(notInvertable);
        Invert(invertMatrix, invertedSucess);
        EXPECT_FALSE(invertedSucess);
        ExpectMatrixNear(original, invertMatrix);
    }

    TEST(Matrix4MathTest, GetNotInvertable) {
        float notInvertable[4][4] = {
            {1.0f, 2.0f, 3.0f, 0.0f},
            {2.0f, 4.0f, 6.0f, 0.0f},
            {3.0f, 6.0f, 9.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        bool invertedSucess = false;
        Matrix4 original(notInvertable);
        Matrix4 invertMatrix = GetInvert(original, invertedSucess);
        EXPECT_FALSE(invertedSucess);
        ExpectMatrixNear(original, invertMatrix);
    }

    TEST(Matrix4Test, InvertIdentity) {
        bool invertedSuccess = false;
        Matrix4 identity = Matrix4::Identity;
        Matrix4 invertedMatrix = identity;
        Invert(invertedMatrix, invertedSuccess);
        EXPECT_TRUE(invertedSuccess);
        ExpectMatrixNear(invertedMatrix, Matrix4::Identity);
    }

    TEST(Matrix4Test, GetInvertIdentity) {
        bool invertedSuccess = false;
        Matrix4 identity = Matrix4::Identity;
        Matrix4 invertedMatrix = GetInvert(identity, invertedSuccess);
        EXPECT_TRUE(invertedSuccess);
        ExpectMatrixNear(invertedMatrix, Matrix4::Identity);
    }

    TEST(Matrix4Test, IsOrthonormal) {
        Matrix4 orthonormalMatrix = 
            CreateRotationX(ToRadians(30.0f)) * 
            CreateRotationY(ToRadians(45.0f)) * 
            CreateRotationZ(ToRadians(60.0f));
        EXPECT_TRUE(IsOrthonormal(orthonormalMatrix));
    }

    TEST(Matrix4Test, IsOrthonormalIdentityMatrix) {
        Matrix4 orthonormalMatrix = Matrix4::Identity;
        EXPECT_TRUE(IsOrthonormal(orthonormalMatrix));
    }

    TEST(Matrix4Test, IsNotOrthonormal) {
        float values[4][4] = {
            {1.0f, 2.0f, 3.0f, 0.0f},
            {0.0f, 1.0f, 4.0f, 0.0f},
            {5.0f, 6.0f, 0.0f, 0.0f},
            {7.0f, 8.0f, 9.0f, 1.0f}
        };
        Matrix4 nonOrthonormalMatrix = Matrix4(values);
        EXPECT_FALSE(IsOrthonormal(nonOrthonormalMatrix));
    }
    #pragma endregion Matrix4MathTest

    #pragma region QuaternionTest
    TEST(QuaternionTest, Conjugate) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);
        Quaternion expected(q.W, -q.X, -q.Y, -q.Z);
        Conjugate(q);
        EXPECT_FLOAT_EQ(q.W, expected.W);
        EXPECT_FLOAT_EQ(q.X, expected.X);
        EXPECT_FLOAT_EQ(q.Y, expected.Y);
        EXPECT_FLOAT_EQ(q.Z, expected.Z);
    }

    TEST(QuaternionTest, GetConjugate) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);
        Quaternion expected(q.W, -q.X, -q.Y, -q.Z);
        Quaternion conjugated = GetConjugate(q);
        EXPECT_FLOAT_EQ(conjugated.W, expected.W);
        EXPECT_FLOAT_EQ(conjugated.X, expected.X);
        EXPECT_FLOAT_EQ(conjugated.Y, expected.Y);
        EXPECT_FLOAT_EQ(conjugated.Z, expected.Z);
    }

    TEST(QuaternionTest, Invert) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);
        glm::quat glmQuat = glm::quat(q.W, q.X, q.Y, q.Z);
        Invert(q);
        glm::quat invertedGlmQuat = glm::inverse(glmQuat);
        EXPECT_QUAT_EQ_NEAR(q, invertedGlmQuat, BASE_EPSILON);
    }

    TEST(QuaternionTest, GetInvert) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);
        Quaternion inverted = GetInvert(q);
        glm::quat glmQuat = glm::quat(q.W, q.X, q.Y, q.Z);
        glm::quat invertedGlmQuat = glm::inverse(glmQuat);
        EXPECT_QUAT_EQ_NEAR(inverted, invertedGlmQuat, BASE_EPSILON);
    }

    TEST(QuaternionTest, Difference) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Difference(q1, q2);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::inverse(glmQ1) * glmQ2;

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, Lerp) {
        float t = 0.3f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Lerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::lerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, LerpMin) {
        float t = 0.0f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Lerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::lerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, LerpCenter) {
        float t = 0.5f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Lerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::lerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, LerpMax) {
        float t = 1.0f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Lerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::lerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, Slerp) {
        float t = 0.3f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Slerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::slerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, SlerpMin) {
        float t = 0.0f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Slerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::slerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, SlerpCenter) {
        float t = 0.5f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Slerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::slerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, SlerpMax) {
        float t = 0.5f;

        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        Quaternion result = Slerp(q1, q2, t);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        glm::quat expected = glm::slerp(glmQ1, glmQ2, t);

        EXPECT_QUAT_EQ_NEAR(result, expected, BASE_EPSILON);
    }

    TEST(QuaternionTest, Exponent) {
        float angle = ToRadians(30.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);

        float exp = 1.5f;
        Exponent(q, exp);

        // newAlpha = (angle / 2) * exp = 15.0 * 1.5 = 22.5
        // newW = cos(newAlpha) = cos(22.5)
        // newXYZ = xyz * sin(newAlpha) / sin(angle /)
        Quaternion expected = Quaternion(Cos(ToRadians(22.5f)), axis.X * Sin(ToRadians(22.5f)), axis.Y * Sin(ToRadians(22.5f)), axis.Z * Sin(ToRadians(22.5f)));
        EXPECT_NEAR(q.W, expected.W, BASE_EPSILON);
        EXPECT_NEAR(q.X, expected.X, BASE_EPSILON);
        EXPECT_NEAR(q.Y, expected.Y, BASE_EPSILON);
        EXPECT_NEAR(q.Z, expected.Z, BASE_EPSILON);
    }

    TEST(QuaternionTest, GetExponent) {
        float angle = ToRadians(30.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);

        float exp = 1.5f;
        q = GetExponent(q, exp);

        // newAlpha = (angle / 2) * exp = 15.0 * 1.5 = 22.5
        // newW = cos(newAlpha) = cos(22.5)
        // newXYZ = xyz * sin(newAlpha) / sin(angle /)
        Quaternion expected = Quaternion(Cos(ToRadians(22.5f)), axis.X * Sin(ToRadians(22.5f)), axis.Y * Sin(ToRadians(22.5f)), axis.Z * Sin(ToRadians(22.5f)));
        EXPECT_NEAR(q.W, expected.W, BASE_EPSILON);
        EXPECT_NEAR(q.X, expected.X, BASE_EPSILON);
        EXPECT_NEAR(q.Y, expected.Y, BASE_EPSILON);
        EXPECT_NEAR(q.Z, expected.Z, BASE_EPSILON);
    }

    TEST(QuaternionTest, Dot) {
        float angle = ToRadians(45.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q1(angle, axis);

        float angle2 = ToRadians(90.0f);
        Vector3 axis2(1.0f, 0.0f, 1.0f);
        Normalize(axis2);
        Quaternion q2(angle2, axis2);
        float result = Dot(q1, q2);

        glm::quat glmQ1 = glm::quat(q1.W, q1.X, q1.Y, q1.Z);
        glm::quat glmQ2 = glm::quat(q2.W, q2.X, q2.Y, q2.Z);
        float expected = glm::dot(glmQ1, glmQ2);
        
        EXPECT_FLOAT_EQ(result, expected);
    }

    TEST(QuaternionTest, IsIdentity) {
        float angle = ToRadians(0.0f);
        Vector3 axis(1.0f, 1.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);
        EXPECT_TRUE(IsIdentity(q));
    }

    TEST(QuaternionTest, GetValuePtr) {
        float angle = ToRadians(60.0f);
        Vector3 axis(1.0f, 2.0f, 0.5f);
        Normalize(axis);
        Quaternion q(angle, axis);
        const float* qPtr = GetValuePtr(q);
        EXPECT_FLOAT_EQ(qPtr[0], Cos(angle / 2.0f));
        EXPECT_FLOAT_EQ(qPtr[1], axis.X * Sin(angle / 2.0f));
        EXPECT_FLOAT_EQ(qPtr[2], axis.Y * Sin(angle / 2.0f));
        EXPECT_FLOAT_EQ(qPtr[3], axis.Z * Sin(angle / 2.0f));
    }

    TEST(QuaternionTest, GetVector) {
        float angle = ToRadians(90.0f);
        Vector3 axis(3.0f, 0.0f, 1.0f);
        Normalize(axis);
        Quaternion q(angle, axis);
        Vector3 vector = GetVector(q);
        EXPECT_FLOAT_EQ(vector.X, axis.X * Sin(angle / 2.0f));
        EXPECT_FLOAT_EQ(vector.Y, axis.Y * Sin(angle / 2.0f));
        EXPECT_FLOAT_EQ(vector.Z, axis.Z * Sin(angle / 2.0f));
    }
    #pragma endregion QuaternionTest
}