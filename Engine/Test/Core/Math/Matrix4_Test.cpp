#include"Test/Core/Math/Helper.h"

namespace Test {
    using namespace VIEngine::Math;

    TEST(Matrix4Test, ConstructionAndAccess) {
        float values[4][4] = {
            {1.0f, 2.0f, 3.0f, 4.0f},
            {5.0f, 6.0f, 7.0f, 8.0f},
            {9.0f, 10.0f, 11.0f, 12.0f},
            {13.0f, 14.0f, 15.0f, 16.0f}
        };
        Matrix4 m{&values[0][0]};

        EXPECT_FLOAT_EQ(m[0][0], 1.0f);
        EXPECT_FLOAT_EQ(m[1][1], 6.0f);
        EXPECT_FLOAT_EQ(m[2][2], 11.0f);
        EXPECT_FLOAT_EQ(m[3][3], 16.0f);

        float* rawPtr = m[0];
        EXPECT_EQ(rawPtr[4], 5.0f);
        EXPECT_EQ(rawPtr[10], 11.0f);
        EXPECT_EQ(rawPtr[15], 16.0f);
    }

    TEST(Matrix4Test, MultiplicationAgainstGLM) {
        float aValues[4][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        };
        Matrix4 m1(&aValues[0][0]);

        float bValues[4][4] = {
            {16, 15, 14, 13},
            {12, 11, 10, 9},
            {8, 7, 6, 5},
            {4, 3, 2, 1}
        };
        Matrix4 m2(&bValues[0][0]);
        Matrix4 res = m1 * m2;

        glm::mat4 g1 = glm::make_mat4(&aValues[0][0]);
        glm::mat4 g2 = glm::make_mat4(&bValues[0][0]);
        glm::mat4 gRes = g2 * g1;

        ExpectMatrixNear(m1, g1);
        ExpectMatrixNear(m2, g2);
        ExpectMatrixNear(res, gRes);

        m1 *= m2;
        ExpectMatrixNear(m1, gRes);
    }

    TEST(Matrix4Test, SpecialMatrices) {
        float values[4][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        };
        Matrix4 m{&values[0][0]};
        Matrix4 identity = Matrix4::Identity;
        
        Matrix4 res = m * identity;
        ExpectMatrixNear(res, m);
    }
}