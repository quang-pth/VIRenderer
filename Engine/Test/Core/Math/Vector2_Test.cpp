#include<gtest/gtest.h>
#include<glm/glm.hpp>
#include<glm/gtc/epsilon.hpp>
#include"Core/Math/Vector2.h"
#include"Core/Math/Compute.h"
#include"Test/Core/Math/Helper.h"

namespace Test {
    using namespace VIEngine::Math;

    TEST(Vector2Test, BasicArithmeticAgainstGLM) {
        Vector2 v1(10.5f, -2.0f);
        Vector2 v2(3.0f, 4.5f);
        float scalar = 2.5f;

        glm::vec2 g1(10.5f, -2.0f);
        glm::vec2 g2(3.0f, 4.5f);

        Vector2 resAdd = v1 + v2;
        EXPECT_VEC2_NEAR(resAdd, (g1 + g2), 1e-5f);

        Vector2 resMul = v1 * scalar;
        EXPECT_VEC2_NEAR(resMul, (g1 * scalar), 1e-5f);

        v1 += v2;
        EXPECT_VEC2_NEAR(v1, (g1 + g2), 1e-5f);
    }

    TEST(Vector2Test, Constants) {
        EXPECT_FLOAT_EQ(Vector2::Zero.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector2::Zero.Y, 0.0f);
        
        EXPECT_FLOAT_EQ(Vector2::UnitX.X, 1.0f);
        EXPECT_FLOAT_EQ(Vector2::UnitX.Y, 0.0f);
        
        EXPECT_FLOAT_EQ(Vector2::UnitY.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector2::UnitY.Y, 1.0f);
        
        EXPECT_FLOAT_EQ(Vector2::NegUnitX.X, -1.0f);
        EXPECT_FLOAT_EQ(Vector2::NegUnitX.Y, 0.0f);

        EXPECT_FLOAT_EQ(Vector2::NegUnitY.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector2::NegUnitY.Y, -1.0f);
    }

    TEST(Vector2Test, LengthUnitVector) {
        EXPECT_FLOAT_EQ(GetLength(Vector2::UnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLength(Vector2::UnitY), 1.0f);
        
        EXPECT_FLOAT_EQ(GetLength(Vector2::NegUnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLength(Vector2::NegUnitY), 1.0f);
    }

    TEST(Vector2Test, LengthSquaredUnitVector) {
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector2::UnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector2::UnitY), 1.0f);
        
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector2::NegUnitX), 1.0f);
        EXPECT_FLOAT_EQ(GetLengthSquared(Vector2::NegUnitY), 1.0f);
    }

    TEST(Vector2Test, MemoryLayout) {
        Vector2 v(1.0f, 2.0f);
        float* ptr = reinterpret_cast<float*>(&v);
        EXPECT_EQ(ptr[0], 1.0f);
        EXPECT_EQ(ptr[1], 2.0f);
        EXPECT_EQ(sizeof(Vector2), sizeof(float) * 2);
        EXPECT_EQ(offsetof(Vector2, X), 0);
        EXPECT_EQ(offsetof(Vector2, Y), sizeof(float));
    }

    TEST(Vector2Test, ConstructionAndMemory) {
        Vector2 v1;
        
        Vector2 v2(1.0f, 2.0f);
        EXPECT_FLOAT_EQ(v2.X, 1.0f);
        EXPECT_FLOAT_EQ(v2.Y, 2.0f);

        Vector2 v3(5.0f);
        EXPECT_FLOAT_EQ(v3.X, 5.0f);
        EXPECT_FLOAT_EQ(v3.Y, 5.0f);

        float data[] = { 10.0f, 20.0f };
        Vector2 v4(data);
        EXPECT_FLOAT_EQ(v4.X, 10.0f);
        EXPECT_FLOAT_EQ(v4.Y, 20.0f);
    }

    TEST(Vector2Test, EqualityOperators) {
        Vector2 a(1.0f, 1.0f);
        Vector2 b(1.0f, 1.0f);
        Vector2 c(1.000001f, 1.0f);

        EXPECT_TRUE(a == b);
        EXPECT_FALSE(a != b);
        
        EXPECT_TRUE(a != c);
        EXPECT_FALSE(a == c);
    }

    TEST(Vector2Test, CommutativeMultiplication) {
        Vector2 v(2.0f, 3.0f);
        float s = 5.0f;
        
        Vector2 res1 = v * s;
        Vector2 res2 = s * v; 
        
        EXPECT_EQ(res1.X, res2.X);
        EXPECT_EQ(res1.Y, res2.Y);
    }

    TEST(Vector2Test, CompoundAssignment) {
        Vector2 v(1.0f, 2.0f);
        Vector2 other(3.0f, 4.0f);

        v += other;
        EXPECT_FLOAT_EQ(v.X, 4.0f);
        EXPECT_FLOAT_EQ(v.Y, 6.0f);

        v -= Vector2(1.0f, 1.0f);
        EXPECT_FLOAT_EQ(v.X, 3.0f);
        EXPECT_FLOAT_EQ(v.Y, 5.0f);

        v *= 2.0f;
        EXPECT_FLOAT_EQ(v.X, 6.0f);
        EXPECT_FLOAT_EQ(v.Y, 10.0f);

        v /= 2.0f;
        EXPECT_FLOAT_EQ(v.X, 3.0f);
        EXPECT_FLOAT_EQ(v.Y, 5.0f);
    }

    TEST(Vector2Test, AdvancedEdgeCases) {
        Vector2 v(123.45f, -67.89f);
        Vector2 zeroRes = v * 0.0f;
        EXPECT_FLOAT_EQ(zeroRes.X, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.Y, 0.0f);

        Vector2 vSame(0.123456f, 0.123456f);
        Vector2 diff = vSame - vSame;
        EXPECT_EQ(diff, Vector2::Zero);

        Vector2 large(FLT_MAX, FLT_MAX);
        Vector2 scaledLarge = large * 2.0f;
        EXPECT_TRUE(std::isinf(scaledLarge.X));

        Vector2 negZero(-0.0f, -0.0f);
        EXPECT_TRUE(negZero == Vector2::Zero); 
    }
}