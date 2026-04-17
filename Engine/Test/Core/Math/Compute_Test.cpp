#include<gtest/gtest.h>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Core/Math/Compute.h"
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
}