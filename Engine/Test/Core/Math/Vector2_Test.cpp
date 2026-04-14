#include<gtest/gtest.h>
#include<glm/glm.hpp>
#include<glm/gtc/epsilon.hpp>
#include"Core/Math/Vector2.h"

#define EXPECT_VEC2_NEAR(v_engine, v_glm, abs_error) \
    EXPECT_NEAR(v_engine.mX, v_glm.x, abs_error); \
    EXPECT_NEAR(v_engine.mY, v_glm.y, abs_error)

namespace VIEngine {
    using namespace Math;

    glm::vec2 ToGLM(const Vector2& vector) { return glm::vec2(vector.mX, vector.mY); };

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

    TEST(Vector2Test, DivisionByZero) {
        Vector2 v(1.0f, 1.0f);
        #if DEBUG
            EXPECT_DEATH({
                v / 0.0f;
            }, "");
        #endif
    }

    TEST(Vector2Test, Constants) {
        EXPECT_FLOAT_EQ(Vector2::Zero.mX, 0.0f);
        EXPECT_FLOAT_EQ(Vector2::Zero.mY, 0.0f);
        EXPECT_FLOAT_EQ(Vector2::UnitX.mX, 1.0f);
        EXPECT_FLOAT_EQ(Vector2::UnitX.mY, 0.0f);
        EXPECT_FLOAT_EQ(Vector2::NegUnitY.mY, -1.0f);
    }

    TEST(Vector2Test, MemoryLayout) {
        Vector2 v(1.0f, 2.0f);
        float* ptr = reinterpret_cast<float*>(&v);
        EXPECT_EQ(ptr[0], 1.0f);
        EXPECT_EQ(ptr[1], 2.0f);
        EXPECT_EQ(sizeof(Vector2), sizeof(float) * 2);
        EXPECT_EQ(offsetof(Vector2, mX), 0);
        EXPECT_EQ(offsetof(Vector2, mY), sizeof(float));
    }

    TEST(Vector2Test, ConstructionAndMemory) {
        Vector2 v1;
        
        Vector2 v2(1.0f, 2.0f);
        EXPECT_FLOAT_EQ(v2.mX, 1.0f);
        EXPECT_FLOAT_EQ(v2.mY, 2.0f);

        Vector2 v3(5.0f);
        EXPECT_FLOAT_EQ(v3.mX, 5.0f);
        EXPECT_FLOAT_EQ(v3.mY, 5.0f);

        float data[] = { 10.0f, 20.0f };
        Vector2 v4(data);
        EXPECT_FLOAT_EQ(v4.mX, 10.0f);
        EXPECT_FLOAT_EQ(v4.mY, 20.0f);
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
        
        EXPECT_EQ(res1.mX, res2.mX);
        EXPECT_EQ(res1.mY, res2.mY);
    }

    TEST(Vector2Test, CompoundAssignment) {
        Vector2 v(1.0f, 2.0f);
        Vector2 other(3.0f, 4.0f);

        v += other;
        EXPECT_FLOAT_EQ(v.mX, 4.0f);
        EXPECT_FLOAT_EQ(v.mY, 6.0f);

        v -= Vector2(1.0f, 1.0f);
        EXPECT_FLOAT_EQ(v.mX, 3.0f);
        EXPECT_FLOAT_EQ(v.mY, 5.0f);

        v *= 2.0f;
        EXPECT_FLOAT_EQ(v.mX, 6.0f);
        EXPECT_FLOAT_EQ(v.mY, 10.0f);

        v /= 2.0f;
        EXPECT_FLOAT_EQ(v.mX, 3.0f);
        EXPECT_FLOAT_EQ(v.mY, 5.0f);
    }

    TEST(Vector2Test, AdvancedEdgeCases) {
        Vector2 v(123.45f, -67.89f);
        Vector2 zeroRes = v * 0.0f;
        EXPECT_FLOAT_EQ(zeroRes.mX, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.mY, 0.0f);

        Vector2 vSame(0.123456f, 0.123456f);
        Vector2 diff = vSame - vSame;
        EXPECT_EQ(diff, Vector2::Zero);

        Vector2 large(FLT_MAX, FLT_MAX);
        Vector2 scaledLarge = large * 2.0f;
        EXPECT_TRUE(std::isinf(scaledLarge.mX));

        Vector2 negZero(-0.0f, -0.0f);
        EXPECT_TRUE(negZero == Vector2::Zero); 
    }
}