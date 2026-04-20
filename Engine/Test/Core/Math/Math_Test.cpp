#include"Test/Core/Math/Helper.h"

namespace Test {
    using namespace VIEngine::Math;

    TEST(MathUtilsTest, AngleConversion) {
        EXPECT_NEAR(PI, 3.1415926535f, 1e-7f);
        
        EXPECT_NEAR(ToRadians(180.0f), PI, BASE_EPSILON);
        EXPECT_NEAR(ToRadians(90.0f), PI_OVER_2, BASE_EPSILON);
        EXPECT_NEAR(ToRadians(0.0f), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(ToRadians(360.0f), TWO_Pi, BASE_EPSILON);

        EXPECT_NEAR(ToDegrees(PI), 180.0f, 1e-5f);
        EXPECT_NEAR(ToDegrees(PI_OVER_2), 90.0f, 1e-5f);
        
        float angle = 45.0f;
        EXPECT_NEAR(ToDegrees(ToRadians(angle)), angle, 1e-5f);
    }

    TEST(MathUtilsTest, IsNearZero) {
        EXPECT_TRUE(IsNearZero(0.0f));
        EXPECT_TRUE(IsNearZero(0.0009f));
        EXPECT_TRUE(IsNearZero(-0.0009f));
        EXPECT_FALSE(IsNearZero(0.0011f));

        EXPECT_TRUE(IsNearZero(0.1f, 0.2f));
        EXPECT_FALSE(IsNearZero(0.3f, 0.2f));

        EXPECT_TRUE(IsNearZero(1e-10f));
    }

    TEST(MathUtilsTest, MinMaxClamp) {
        EXPECT_EQ(Min(10, 20), 10);
        EXPECT_EQ(Max(10, 20), 20);

        EXPECT_FLOAT_EQ(Min(1.5f, -0.5f), -0.5f);
        EXPECT_FLOAT_EQ(Max(1.5f, -0.5f), 1.5f);

        EXPECT_EQ(Clamp(15, 10, 20), 15);
        EXPECT_EQ(Clamp(5, 10, 20), 10);
        EXPECT_EQ(Clamp(25, 10, 20), 20);

        EXPECT_FLOAT_EQ(Clamp(0.5f, 0.0f, 1.0f), 0.5f);
    }

    TEST(MathUtilsTest, EdgeCases) {
        EXPECT_EQ(Clamp(10, 50, 50), 50);

        EXPECT_EQ(Clamp(100.0f, 0.0f, MAX_NUMBER), 100.0f);
        EXPECT_EQ(Clamp(MAX_NUMBER, 0.0f, 100.0f), 100.0f);
        EXPECT_EQ(Clamp(10, 100, 30), 30);

        EXPECT_TRUE(std::isinf(MAX_NUMBER));
        EXPECT_TRUE(MAX_NUMBER > 1e30f);
        EXPECT_TRUE(MIN_NUMBER < -1e30f);

        EXPECT_NEAR(ToRadians(-90.0f), -PI_OVER_2, BASE_EPSILON);
    }

    TEST(MathUtilsTest, Sin) {
        EXPECT_NEAR(Sin(0.0f), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(Sin(PI_OVER_2), 1.0f, BASE_EPSILON);
        EXPECT_NEAR(Sin(PI), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(Sin(TWO_Pi), 0.0f, BASE_EPSILON);
    }

    TEST(MathUtilsTest, Cos) {
        EXPECT_NEAR(Cos(0.0f), 1.0f, BASE_EPSILON);
        EXPECT_NEAR(Cos(PI_OVER_2), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(Cos(PI), -1.0f, BASE_EPSILON);
        EXPECT_NEAR(Cos(TWO_Pi), 1.0f, BASE_EPSILON);
    }

    TEST(MathUtilsTest, Tan) {
        EXPECT_NEAR(Tan(0.0f), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(Tan(PI_OVER_4), 1.0f, BASE_EPSILON);
        EXPECT_NEAR(Tan(-PI_OVER_4), -1.0f, BASE_EPSILON);
    }

    TEST(MathUtilsTest, Cot) {
        EXPECT_NEAR(Cot(PI_OVER_4), 1.0f, BASE_EPSILON);
        EXPECT_NEAR(Cot(-PI_OVER_4), -1.0f, BASE_EPSILON);
    }

    TEST(MathUtilsTest, Acos) {
        EXPECT_NEAR(Acos(1.0f), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(Acos(0.0f), PI_OVER_2, BASE_EPSILON);
        EXPECT_NEAR(Acos(-1.0f), PI, BASE_EPSILON);
    }

    TEST(MathUtilsTest, Atan2) {
        EXPECT_NEAR(Atan2(0.0f, 1.0f), 0.0f, BASE_EPSILON);
        EXPECT_NEAR(Atan2(1.0f, 0.0f), PI_OVER_2, BASE_EPSILON);
        EXPECT_NEAR(Atan2(0.0f, -1.0f), PI, BASE_EPSILON);
        EXPECT_NEAR(Atan2(-1.0f, 0.0f), -PI_OVER_2, BASE_EPSILON);
    }

    TEST(MathUtilsTest, ClampVector2ScalarAgainstGLM) {
        Vector2 v(10.5f, -5.0f);
        glm::vec2 g(10.5f, -5.0f);
        float minVal = 0.0f;
        float maxVal = 5.0f;

        Vector2 clamped = Clamp(v, minVal, maxVal);
        glm::vec2 gClamped = glm::clamp(g, minVal, maxVal);

        EXPECT_VEC2_NEAR(clamped, gClamped, BASE_EPSILON);
    }
    
    TEST(MathUtilsTest, ClampVector2AgainstGLM) {
        Vector2 v(10.5f, -5.0f);
        Vector2 minVec(0.0f, 0.0f);
        Vector2 maxVec(5.0f, 5.0f);

        glm::vec2 g(10.5f, -5.0f);
        glm::vec2 gMin(0.0f, 0.0f);
        glm::vec2 gMax(5.0f, 5.0f);

        Vector2 clamped = Clamp(v, minVec, maxVec);
        glm::vec2 gClamped = glm::clamp(g, gMin, gMax);

        EXPECT_VEC2_NEAR(clamped, gClamped, BASE_EPSILON);
    }

    TEST(MathUtilsTest, ClampVector3ScalarAgainstGLM) {
        Vector3 v(10.5f, -5.0f, 2.0f);
        float minVal = 0.0f;
        float maxVal = 5.0f;

        glm::vec3 g(10.5f, -5.0f, 2.0f);
        Vector3 clamped = Clamp(v, minVal, maxVal);
        glm::vec3 gClamped = glm::clamp(g, minVal, maxVal);

        EXPECT_VEC3_NEAR(clamped, gClamped, BASE_EPSILON);
    }

    TEST(MathUtilsTest, ClampVector3AgainstGLM) {
        Vector3 v(10.5f, -5.0f, 2.0f);
        Vector3 minVec(0.0f, 0.0f, 1.0f);
        Vector3 maxVec(5.0f, 5.0f, 3.0f);

        glm::vec3 g(10.5f, -5.0f, 2.0f);
        glm::vec3 gMin(0.0f, 0.0f, 1.0f);
        glm::vec3 gMax(5.0f, 5.0f, 3.0f);

        Vector3 clamped = Clamp(v, minVec, maxVec);
        glm::vec3 gClamped = glm::clamp(g, gMin, gMax);

        EXPECT_VEC3_NEAR(clamped, gClamped, BASE_EPSILON);
    }


}