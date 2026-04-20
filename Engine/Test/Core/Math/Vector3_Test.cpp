#include"Test/Core/Math/Helper.h"
    
namespace Test {
    using namespace VIEngine::Math;

    TEST(Vector3Test, BasicArithmeticAgainstGLM) {
        Vector3 v1(10.5f, -2.0f, 3.0f);
        Vector3 v2(3.0f, 4.5f, -5.5f);
        float scalar = 2.5f;

        glm::vec3 g1(10.5f, -2.0f, 3.0f);
        glm::vec3 g2(3.0f, 4.5f, -5.5f);

        Vector3 resAdd = v1 + v2;
        EXPECT_VEC3_NEAR(resAdd, (g1 + g2), BASE_EPSILON);

        Vector3 resMul = v1 * scalar;
        EXPECT_VEC3_NEAR(resMul, (g1 * scalar), BASE_EPSILON);

        v1 += v2;
        EXPECT_VEC3_NEAR(v1, (g1 + g2), BASE_EPSILON);
    }

    TEST(Vector3Test, CrossProduct) {
        Vector3 v1(1.0f, 0.0f, 0.0f);
        Vector3 v2(0.0f, 1.0f, 0.0f);
        Vector3 cross = Cross(v1, v2);
        EXPECT_FLOAT_EQ(cross.X, 0.0f);
        EXPECT_FLOAT_EQ(cross.Y, 0.0f);
        EXPECT_FLOAT_EQ(cross.Z, 1.0f);

        Vector3 v3(1.0f, 2.0f, 3.0f);
        Vector3 v4(4.0f, 5.0f, 6.0f);
        Vector3 cross2 = Cross(v3, v4);
        EXPECT_FLOAT_EQ(cross2.X, -3.0f);
        EXPECT_FLOAT_EQ(cross2.Y, 6.0f);
        EXPECT_FLOAT_EQ(cross2.Z, -3.0f);

        Vector3 v5(1.0f, 1.0f, 1.0f);
        Vector3 crossParallel = Cross(v5, v5);
        EXPECT_EQ(crossParallel, Vector3::Zero);

        glm::vec3 g3(1.0f, 2.0f, 3.0f);
        glm::vec3 g4(4.0f, 5.0f, 6.0f);
        glm::vec3 gCross = glm::cross(g3, g4);
        EXPECT_VEC3_NEAR(cross2, gCross, BASE_EPSILON);
    }

    TEST(Vector3Test, Constants) {
        EXPECT_FLOAT_EQ(Vector3::Zero.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::Zero.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::Zero.Z, 0.0f);

        EXPECT_FLOAT_EQ(Vector3::UnitX.X, 1.0f);
        EXPECT_FLOAT_EQ(Vector3::UnitX.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::UnitX.Z, 0.0f);

        EXPECT_FLOAT_EQ(Vector3::UnitY.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::UnitY.Y, 1.0f);
        EXPECT_FLOAT_EQ(Vector3::UnitY.Z, 0.0f);

        EXPECT_FLOAT_EQ(Vector3::UnitZ.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::UnitZ.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::UnitZ.Z, 1.0f);
        
        EXPECT_FLOAT_EQ(Vector3::NegUnitX.X, -1.0f);
        EXPECT_FLOAT_EQ(Vector3::NegUnitX.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::NegUnitX.Z, 0.0f);

        EXPECT_FLOAT_EQ(Vector3::NegUnitY.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::NegUnitY.Y, -1.0f);
        EXPECT_FLOAT_EQ(Vector3::NegUnitY.Z, 0.0f);

        EXPECT_FLOAT_EQ(Vector3::NegUnitZ.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::NegUnitZ.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector3::NegUnitZ.Z, -1.0f);
    }

    
    TEST(Vector3Test, LengthUnitVector) {
        EXPECT_FLOAT_EQ(GetLength(Vector3::UnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLength(Vector3::UnitY), 1.0f);
        EXPECT_FLOAT_EQ(GetLength(Vector3::UnitZ), 1.0f);

        EXPECT_FLOAT_EQ(GetLength(Vector3::NegUnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLength(Vector3::NegUnitY), 1.0f);
        EXPECT_FLOAT_EQ(GetLength(Vector3::NegUnitZ), 1.0f);
    }

    TEST(Vector3Test, LengthSquaredUnitVector) {
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector3::UnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector3::UnitY), 1.0f);
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector3::UnitZ), 1.0f);

        EXPECT_FLOAT_EQ(GetLengthSquared(Vector3::NegUnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector3::NegUnitY), 1.0f);
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector3::NegUnitZ), 1.0f);
    }

    TEST(Vector3Test, MemoryLayout) {
        Vector3 v(1.0f, 2.0f, 3.0f);
        float* ptr = reinterpret_cast<float*>(&v);
        EXPECT_EQ(ptr[0], 1.0f);
        EXPECT_EQ(ptr[1], 2.0f);
        EXPECT_EQ(ptr[2], 3.0f);
        EXPECT_EQ(sizeof(Vector3), sizeof(float) * 3);
        EXPECT_EQ(offsetof(Vector3, X), 0);
        EXPECT_EQ(offsetof(Vector3, Y), sizeof(float));
        EXPECT_EQ(offsetof(Vector3, Z), sizeof(float) * 2);
    }

    TEST(Vector3Test, ConstructionAndMemory) {
        Vector3 v1;
        
        Vector3 v2(1.0f, 2.0f, 3.0f);
        EXPECT_FLOAT_EQ(v2.X, 1.0f);
        EXPECT_FLOAT_EQ(v2.Y, 2.0f);
        EXPECT_FLOAT_EQ(v2.Z, 3.0f);

        Vector3 v3(5.0f);
        EXPECT_FLOAT_EQ(v3.X, 5.0f);
        EXPECT_FLOAT_EQ(v3.Y, 5.0f);
        EXPECT_FLOAT_EQ(v3.Z, 5.0f);

        float data[] = { 10.0f, 20.0f, 30.0f };
        Vector3 v4(data);
        EXPECT_FLOAT_EQ(v4.X, 10.0f);
        EXPECT_FLOAT_EQ(v4.Y, 20.0f);
        EXPECT_FLOAT_EQ(v4.Z, 30.0f);
    }

    TEST(Vector3Test, EqualityOperators) {
        Vector3 a(1.0f, 1.0f, 1.0f);
        Vector3 b(1.0f, 1.0f, 1.0f);
        Vector3 c(1.000001f, 1.0f, 1.0f);

        EXPECT_TRUE(a == b);
        EXPECT_FALSE(a != b);
        
        EXPECT_TRUE(a != c);
        EXPECT_FALSE(a == c);
    }

    TEST(Vector3Test, CommutativeMultiplication) {
        Vector3 v(2.0f, 3.0f, 5.0f);
        float s = 5.0f;
        
        Vector3 res1 = v * s;
        Vector3 res2 = s * v; 
        
        EXPECT_EQ(res1.X, res2.X);
        EXPECT_EQ(res1.Y, res2.Y);
        EXPECT_EQ(res1.Z, res2.Z);
    }

    TEST(Vector3Test, CompoundAssignment) {
        Vector3 v(1.0f, 2.0f, -1.0f);
        Vector3 other(3.0f, 4.0f, -2.0f);

        v += other;
        EXPECT_FLOAT_EQ(v.X, 4.0f);
        EXPECT_FLOAT_EQ(v.Y, 6.0f);
        EXPECT_FLOAT_EQ(v.Z, -3.0f);

        v -= Vector3(1.0f, 1.0f, 3.0f);
        EXPECT_FLOAT_EQ(v.X, 3.0f);
        EXPECT_FLOAT_EQ(v.Y, 5.0f);
        EXPECT_FLOAT_EQ(v.Z, -6.0f);

        v *= 2.0f;
        EXPECT_FLOAT_EQ(v.X, 6.0f);
        EXPECT_FLOAT_EQ(v.Y, 10.0f);
        EXPECT_FLOAT_EQ(v.Z, -12.0f);
        
        v /= 2.0f;
        EXPECT_FLOAT_EQ(v.X, 3.0f);
        EXPECT_FLOAT_EQ(v.Y, 5.0f);
        EXPECT_FLOAT_EQ(v.Z, -6.0f);
    }

    TEST(Vector3Test, AdvancedEdgeCases) {
        Vector3 v(123.45f, -67.89f, -33.333f);
        Vector3 zeroRes = v * 0.0f;
        EXPECT_FLOAT_EQ(zeroRes.X, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.Y, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.Z, 0.0f);

        Vector3 vSame(0.123456f, 0.123456f, 0.123456f);
        Vector3 diff = vSame - vSame;
        EXPECT_EQ(diff, Vector3::Zero);

        Vector3 large(FLT_MAX, FLT_MAX, FLT_MAX);
        Vector3 scaledLarge = large * 2.0f;
        EXPECT_TRUE(std::isinf(scaledLarge.X));

        Vector3 negZero(-0.0f, -0.0f, -0.0f);
        EXPECT_TRUE(negZero == Vector3::Zero); 
    }
}