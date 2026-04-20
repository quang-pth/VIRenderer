#include"Test/Core/Math/Helper.h"

namespace Test {
    using namespace VIEngine::Math;

    TEST(Matrix3Test, ConstructionAndAccess) {
        float values[3][3] = {
            {1.0f, 2.0f, 3.0f},
            {4.0f, 5.0f, 6.0f},
            {7.0f, 8.0f, 9.0f}
        };
        Matrix3 m{&values[0][0]};

        EXPECT_FLOAT_EQ(m[0][0], 1.0f);
        EXPECT_FLOAT_EQ(m[1][1], 5.0f);
        EXPECT_FLOAT_EQ(m[2][2], 9.0f);

        float* rawPtr = m[0];
        EXPECT_EQ(rawPtr[3], 4.0f);
        EXPECT_EQ(rawPtr[8], 9.0f);
    }

    TEST(Matrix3Test, MultiplicationAgainstGLM) {
        float aValues[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        Matrix3 m1(&aValues[0][0]);

        float bValues[3][3] = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}
        };
        Matrix3 m2(&bValues[0][0]);
        Matrix3 res = m1 * m2;

        glm::mat3 g1 = glm::make_mat3(&aValues[0][0]);
        glm::mat3 g2 = glm::make_mat3(&bValues[0][0]);
        glm::mat3 gRes = g2 * g1;

        ExpectMatrix3Near(m1, g1);
        ExpectMatrix3Near(m2, g2);
        ExpectMatrix3Near(res, gRes);

        m1 *= m2;
        ExpectMatrix3Near(m1, gRes);
    }

    TEST(Matrix3Test, SpecialMatrices) {
        float values[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        Matrix3 m{&values[0][0]};
        Matrix3 identity = Matrix3::Identity;
        
        Matrix3 res = m * identity;
        ExpectMatrix3Near(m, res);
        
        Matrix3 zero{0.0f};
        Matrix3 resZero = m * zero;
        ExpectMatrix3Near(zero, resZero);
    }
}