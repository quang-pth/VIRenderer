#include"Test/Core/Math/Helper.h"
    
namespace Test {
    using namespace VIEngine::Math;

    TEST(Vector4Test, Indexing) {
        Vector4 v;
        v.X = 1.0f;
        v.Y = 2.0f;
        v.Z = 3.0f;
        v.W = 1.0f;
        v[0] += 1.0f;
        v[1] += 1.0f;
        v[2] += 1.0f;
        v[3] *= 1.0f;
        EXPECT_FLOAT_EQ(v.X, 2.0f);
        EXPECT_FLOAT_EQ(v.Y, 3.0f);
        EXPECT_FLOAT_EQ(v.Z, 4.0f);
        EXPECT_FLOAT_EQ(v.W, 1.0f);
    }

    TEST(Vector4Test, BasicArithmeticAgainstGLM) {
        Vector4 v1(10.5f, -2.0f, 3.0f, 1.0f);
        Vector4 v2(3.0f, 4.5f, -5.5f, 1.0f);
        float scalar = 2.5f;

        glm::vec4 g1(10.5f, -2.0f, 3.0f, 1.0f);
        glm::vec4 g2(3.0f, 4.5f, -5.5f, 1.0f);

        Vector4 resAdd = v1 + v2;
        EXPECT_VEC4_NEAR(resAdd, (g1 + g2), BASE_EPSILON);

        Vector4 resMul = v1 * scalar;
        EXPECT_VEC4_NEAR(resMul, (g1 * scalar), BASE_EPSILON);

        v1 += v2;
        EXPECT_VEC4_NEAR(v1, (g1 + g2), BASE_EPSILON);
    }

    TEST(Vector4Test, Constants) {
        EXPECT_FLOAT_EQ(Vector4::Zero.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::Zero.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::Zero.Z, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::Zero.W, 0.0f);

        EXPECT_FLOAT_EQ(Vector4::UnitX.X, 1.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitX.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitX.Z, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitX.W, 0.0f);
        
        EXPECT_FLOAT_EQ(Vector4::UnitY.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitY.Y, 1.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitY.Z, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitY.W, 0.0f);

        EXPECT_FLOAT_EQ(Vector4::UnitZ.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitZ.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitZ.Z, 1.0f);
        EXPECT_FLOAT_EQ(Vector4::UnitZ.W, 0.0f);
        
        EXPECT_FLOAT_EQ(Vector4::NegUnitX.X, -1.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitX.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitX.Z, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitX.W, 0.0f);

        EXPECT_FLOAT_EQ(Vector4::NegUnitY.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitY.Y, -1.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitY.Z, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitY.W, 0.0f);

        EXPECT_FLOAT_EQ(Vector4::NegUnitZ.X, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitZ.Y, 0.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitZ.Z, -1.0f);
        EXPECT_FLOAT_EQ(Vector4::NegUnitZ.W, 0.0f);
    }

    TEST(Vector4Test, MemoryLayout) {
        Vector4 v(1.0f, 2.0f, 3.0f, 1.0f);
        float* ptr = reinterpret_cast<float*>(&v);
        EXPECT_EQ(ptr[0], 1.0f);
        EXPECT_EQ(ptr[1], 2.0f);
        EXPECT_EQ(ptr[2], 3.0f);
        EXPECT_EQ(ptr[3], 1.0f);
        EXPECT_EQ(sizeof(Vector4), sizeof(float) * 4);
        EXPECT_EQ(offsetof(Vector4, X), 0);
        EXPECT_EQ(offsetof(Vector4, Y), sizeof(float));
        EXPECT_EQ(offsetof(Vector4, Z), sizeof(float) * 2);
        EXPECT_EQ(offsetof(Vector4, W), sizeof(float) * 3);
    }

    TEST(Vector4Test, ConstructionAndMemory) {
        Vector4 v1;
        
        Vector4 v2(1.0f, 2.0f, 3.0f);
        EXPECT_FLOAT_EQ(v2.X, 1.0f);
        EXPECT_FLOAT_EQ(v2.Y, 2.0f);
        EXPECT_FLOAT_EQ(v2.Z, 3.0f);
        EXPECT_FLOAT_EQ(v2.W, 1.0f);

        Vector4 v3(5.0f, 1.0f);
        EXPECT_FLOAT_EQ(v3.X, 5.0f);
        EXPECT_FLOAT_EQ(v3.Y, 5.0f);
        EXPECT_FLOAT_EQ(v3.Z, 5.0f);
        EXPECT_FLOAT_EQ(v3.W, 1.0f);

        float data[] = { 10.0f, 20.0f, 30.0f, 2.0f };
        Vector4 v4(data);
        EXPECT_FLOAT_EQ(v4.X, 10.0f);
        EXPECT_FLOAT_EQ(v4.Y, 20.0f);
        EXPECT_FLOAT_EQ(v4.Z, 30.0f);
        EXPECT_FLOAT_EQ(v4.W, 2.0f);

        Vector3 vec3(1.0f, 2.0f, 3.0f);
        Vector4 convertedVec4(vec3);
        EXPECT_FLOAT_EQ(convertedVec4.X, vec3.X);
        EXPECT_FLOAT_EQ(convertedVec4.Y, vec3.Y);
        EXPECT_FLOAT_EQ(convertedVec4.Z, vec3.Z);
        EXPECT_FLOAT_EQ(convertedVec4.W, 1.0f);
    }

    TEST(Vector4Test, EqualityOperators) {
        Vector4 a(1.0f, 1.0f, 1.0f, 1.0f);
        Vector4 b(1.0f, 1.0f, 1.0f, 1.0f);
        Vector4 c(1.000001f, 1.0f, 1.0f, 0.5f);

        EXPECT_TRUE(a == b);
        EXPECT_FALSE(a != b);
        
        EXPECT_TRUE(a != c);
        EXPECT_FALSE(a == c);
    }

    TEST(Vector4Test, CommutativeMultiplication) {
        Vector4 v(2.0f, 3.0f, 5.0f, 1.0f);
        float s = 5.0f;
        
        Vector4 res1 = v * s;
        Vector4 res2 = s * v; 
        
        EXPECT_EQ(res1.X, res2.X);
        EXPECT_EQ(res1.Y, res2.Y);
        EXPECT_EQ(res1.Z, res2.Z);
        EXPECT_EQ(res1.W, res2.W);
    }

    TEST(Vector4Test, CompoundAssignment) {
        Vector4 v(1.0f, 2.0f, -1.0f, 1.0f);
        Vector4 other(3.0f, 4.0f, -2.0f, 1.0f);

        v += other;
        EXPECT_FLOAT_EQ(v.X, 4.0f);
        EXPECT_FLOAT_EQ(v.Y, 6.0f);
        EXPECT_FLOAT_EQ(v.Z, -3.0f);
        EXPECT_FLOAT_EQ(v.W, 2.0f);

        v -= Vector4(1.0f, 1.0f, 3.0f, 2.0f);
        EXPECT_FLOAT_EQ(v.X, 3.0f);
        EXPECT_FLOAT_EQ(v.Y, 5.0f);
        EXPECT_FLOAT_EQ(v.Z, -6.0f);
        EXPECT_FLOAT_EQ(v.W, 0.0f);

        v *= 2.0f;
        EXPECT_FLOAT_EQ(v.X, 6.0f);
        EXPECT_FLOAT_EQ(v.Y, 10.0f);
        EXPECT_FLOAT_EQ(v.Z, -12.0f);
        EXPECT_FLOAT_EQ(v.W, 0.0f);
        
        v /= 2.0f;
        EXPECT_FLOAT_EQ(v.X, 3.0f);
        EXPECT_FLOAT_EQ(v.Y, 5.0f);
        EXPECT_FLOAT_EQ(v.Z, -6.0f);
        EXPECT_FLOAT_EQ(v.W, 0.0f);
    }

    TEST(Vector4Test, AdvancedEdgeCases) {
        Vector4 v(123.45f, -67.89f, -33.333f, 1.0f);
        Vector4 zeroRes = v * 0.0f;
        EXPECT_FLOAT_EQ(zeroRes.X, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.Y, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.Z, 0.0f);
        EXPECT_FLOAT_EQ(zeroRes.W, 0.0f);

        Vector4 vSame(0.123456f, 0.123456f, 0.123456f, 0.5f);
        Vector4 diff = vSame - vSame;
        EXPECT_EQ(diff, Vector4::Zero);

        Vector4 large(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);
        Vector4 scaledLarge = large * 2.0f;
        EXPECT_TRUE(std::isinf(scaledLarge.X));
        EXPECT_TRUE(std::isinf(scaledLarge.Y));
        EXPECT_TRUE(std::isinf(scaledLarge.Z));
        EXPECT_TRUE(std::isinf(scaledLarge.W));

        Vector4 negZero(-0.0f, -0.0f, -0.0f, -0.0f);
        EXPECT_TRUE(negZero == Vector4::Zero); 
    }
}