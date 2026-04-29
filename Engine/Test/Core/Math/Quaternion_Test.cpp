#include"Test/Core/Math/Helper.h"

namespace Test{
    using namespace VIEngine::Math;

    TEST(QuaternionTest, ConstructionDirectly) {
        float values[4] = {1.0f, 2.0f, 3.0f, 4.0f};
        Quaternion q{values};

        EXPECT_FLOAT_EQ(q.W, 1.0f);
        EXPECT_FLOAT_EQ(q.X, 2.0f);
        EXPECT_FLOAT_EQ(q.Y, 3.0f);
        EXPECT_FLOAT_EQ(q.Z, 4.0f);

        EXPECT_FLOAT_EQ(q[0], 1.0f);
        EXPECT_FLOAT_EQ(q[1], 2.0f);
        EXPECT_FLOAT_EQ(q[2], 3.0f);
        EXPECT_FLOAT_EQ(q[3], 4.0f);
    }

    TEST(QuaternionTest, ConstructionByAxisAndAngle) {
        Vector3 axis{1.0f, 2.0f, 3.0f};
        float angle = ToRadians(45.0f);
        Quaternion q(angle, axis);
        float halfAngle = angle / 2.0f;
        EXPECT_FLOAT_EQ(q.W, Cos(halfAngle));
        EXPECT_FLOAT_EQ(q.X, axis.X * Sin(halfAngle));
        EXPECT_FLOAT_EQ(q.Y, axis.Y * Sin(halfAngle));
        EXPECT_FLOAT_EQ(q.Z, axis.Z * Sin(halfAngle));

        EXPECT_FLOAT_EQ(q[0], Cos(halfAngle));
        EXPECT_FLOAT_EQ(q[1], axis.X * Sin(halfAngle));
        EXPECT_FLOAT_EQ(q[2], axis.Y * Sin(halfAngle));
        EXPECT_FLOAT_EQ(q[3], axis.Z * Sin(halfAngle));
    }

    TEST(QuaternionTest, ConstructionByArray) {
        float values[4] = {1.0f, 2.0f, 3.0f, 4.0f};
        Quaternion q(values);

        EXPECT_FLOAT_EQ(q.W, 1.0f);
        EXPECT_FLOAT_EQ(q.X, 2.0f);
        EXPECT_FLOAT_EQ(q.Y, 3.0f);
        EXPECT_FLOAT_EQ(q.Z, 4.0f);

        EXPECT_FLOAT_EQ(q[0], 1.0f);
        EXPECT_FLOAT_EQ(q[1], 2.0f);
        EXPECT_FLOAT_EQ(q[2], 3.0f);
        EXPECT_FLOAT_EQ(q[3], 4.0f);
    }

    TEST(QuaternionTest, ConstructionAgainstGLM) {
        Vector3 axis(0.0f, 1.0f, 0.0f);
        float angle = ToRadians(90.0f);
        Quaternion q = Quaternion(angle, axis);
        glm::quat glmQ = glm::angleAxis(angle, glm::vec3(axis.X, axis.Y, axis.Z));
        EXPECT_QUAT_EQ_NEAR(q, glmQ, BASE_EPSILON);
    }

    TEST(QuaternionTest, Indexing) {
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        q[0] += 1.0f;
        q[1] += 1.0f;
        q[2] += 1.0f;
        q[3] += 1.0f;

        EXPECT_FLOAT_EQ(q.W, 2.0f);
        EXPECT_FLOAT_EQ(q.X, 3.0f);
        EXPECT_FLOAT_EQ(q.Y, 4.0f);
        EXPECT_FLOAT_EQ(q.Z, 5.0f);
    }

    TEST(QuaternionTest, Identity) {
        EXPECT_FLOAT_EQ(Quaternion::Identity.W, 1.0f);
        EXPECT_FLOAT_EQ(Quaternion::Identity.X, 0.0f);
        EXPECT_FLOAT_EQ(Quaternion::Identity.Y, 0.0f);
        EXPECT_FLOAT_EQ(Quaternion::Identity.Z, 0.0f);
    }

    TEST(QuaternionTest, Addition) {
        Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
        Quaternion sum = q1 + q2;

        EXPECT_FLOAT_EQ(sum.W, 6.0f);
        EXPECT_FLOAT_EQ(sum.X, 8.0f);
        EXPECT_FLOAT_EQ(sum.Y, 10.0f);
        EXPECT_FLOAT_EQ(sum.Z, 12.0f);
    }

    TEST(QuaternionTest, AdditionEquals) {
        Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
        q1 += q2;

        EXPECT_FLOAT_EQ(q1.W, 6.0f);
        EXPECT_FLOAT_EQ(q1.X, 8.0f);
        EXPECT_FLOAT_EQ(q1.Y, 10.0f);
        EXPECT_FLOAT_EQ(q1.Z, 12.0f);
    }

    TEST(QuaternionTest, Subtraction) {
        Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
        Quaternion diff = q1 - q2;

        EXPECT_FLOAT_EQ(diff.W, -4.0f);
        EXPECT_FLOAT_EQ(diff.X, -4.0f);
        EXPECT_FLOAT_EQ(diff.Y, -4.0f);
        EXPECT_FLOAT_EQ(diff.Z, -4.0f);
    }

    TEST(QuaternionTest, SubtractionEquals) {
        Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
        q1 -= q2;

        EXPECT_FLOAT_EQ(q1.W, -4.0f);
        EXPECT_FLOAT_EQ(q1.X, -4.0f);
        EXPECT_FLOAT_EQ(q1.Y, -4.0f);
        EXPECT_FLOAT_EQ(q1.Z, -4.0f);
    }

    TEST(QuaternionTest, MultiplyByQuaternion) {
        Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
        Quaternion result = q1 * q2;
        // q1 * q2 -> w = w1 * w2 - dot(v1, v2), xyz = w1 * v2 + w2 * v1 + cross(v1, v2)
        // dot(v1, v2) = 1 * 5 + 2 * 6 + 3 * 7 = 38
        // w = 4 * 8 - 38 = -60
        // cross(v1, v2) = (3 * 8 - 4 * 7, 4 * 6 - 2 * 8, 2 * 8 - 4 * 6) = (24 - 28, 24 - 16, 16 - 24) = (-4, 8, -8)
        // x = 1 * 6 + 5 * 2 - 4 = 6 + 10 - 4 = 12;
        // y = 1 * 7 + 5 * 3 + 8 = 7 + 15 + 8 = 30;
        // z = 1 * 8 + 5 * 4 - 6 * 2 - (-8) = 8 + 20 - 12 + 8 = 24;
        EXPECT_FLOAT_EQ(result.W, -60.0f);
        EXPECT_FLOAT_EQ(result.X, 12.0f);
        EXPECT_FLOAT_EQ(result.Y, 30.0f);
        EXPECT_FLOAT_EQ(result.Z, 24.0f);
    }
    
    TEST(QuaternionTest, MultiplyEqualsByQuaternion) {
        Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
        q1 *= q2;
        // q1 * q2 -> w = w1 * w2 - dot(v1, v2), xyz = w1 * v2 + w2 * v1 + cross(v1, v2)
        // dot(v1, v2) = 1 * 5 + 2 * 6 + 3 * 7 = 38
        // w = 4 * 8 - 38 = -60
        // cross(v1, v2) = (3 * 8 - 4 * 7, 4 * 6 - 2 * 8, 2 * 8 - 4 * 6) = (24 - 28, 24 - 16, 16 - 24) = (-4, 8, -8)
        // x = 1 * 6 + 5 * 2 - 4 = 6 + 10 - 4 = 12;
        // y = 1 * 7 + 5 * 3 + 8 = 7 + 15 + 8 = 30;
        // z = 1 * 8 + 5 * 4 - 6 * 2 - (-8) = 8 + 20 - 12 + 8 = 24;
        EXPECT_FLOAT_EQ(q1.W, -60.0f);
        EXPECT_FLOAT_EQ(q1.X, 12.0f);
        EXPECT_FLOAT_EQ(q1.Y, 30.0f);
        EXPECT_FLOAT_EQ(q1.Z, 24.0f);
    }

    TEST(QuaternionTest, MultiplyByScalar) {
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        float scalar = 2.0f;
        Quaternion result = q * scalar;

        EXPECT_FLOAT_EQ(result.W, 2.0f);
        EXPECT_FLOAT_EQ(result.X, 4.0f);
        EXPECT_FLOAT_EQ(result.Y, 6.0f);
        EXPECT_FLOAT_EQ(result.Z, 8.0f);
    }

    TEST(QuaternionTest, MultiplyEqualsByScalar) {
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        float scalar = 2.0f;
        q *= scalar;

        EXPECT_FLOAT_EQ(q.W, 2.0f);
        EXPECT_FLOAT_EQ(q.X, 4.0f);
        EXPECT_FLOAT_EQ(q.Y, 6.0f);
        EXPECT_FLOAT_EQ(q.Z, 8.0f);
    }

    TEST(QuaternionTest, DividedByScalar) {
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        float scalar = 2.0f;
        Quaternion result = q / scalar;

        EXPECT_FLOAT_EQ(result.W, 0.5f);
        EXPECT_FLOAT_EQ(result.X, 1.0f);
        EXPECT_FLOAT_EQ(result.Y, 1.5f);
        EXPECT_FLOAT_EQ(result.Z, 2.0f);
    }

    TEST(QuaternionTest, DividedEqualsByScalar) {
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        float scalar = 2.0f;
        q /= scalar;

        EXPECT_FLOAT_EQ(q.W, 0.5f);
        EXPECT_FLOAT_EQ(q.X, 1.0f);
        EXPECT_FLOAT_EQ(q.Y, 1.5f);
        EXPECT_FLOAT_EQ(q.Z, 2.0f);
    }
}