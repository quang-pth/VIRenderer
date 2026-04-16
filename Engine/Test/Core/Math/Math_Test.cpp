#include<gtest/gtest.h>
#include"Core/Math/Math.h"

namespace VIEngine {
    using namespace Math;

    TEST(MathUtilsTest, AngleConversion) {
        EXPECT_NEAR(PI, 3.1415926535f, 1e-7f);
        
        EXPECT_NEAR(ToRadians(180.0f), PI, 1e-6f);
        EXPECT_NEAR(ToRadians(90.0f), PI_OVER_2, 1e-6f);
        EXPECT_NEAR(ToRadians(0.0f), 0.0f, 1e-6f);
        EXPECT_NEAR(ToRadians(360.0f), TWO_Pi, 1e-6f);

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

        EXPECT_NEAR(ToRadians(-90.0f), -PI_OVER_2, 1e-6f);
    }
}