#include<gtest/gtest.h>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Core/Math/Compute.h"

#define EXPECT_VEC2_NEAR(v_eng, v_glm, err) \
    EXPECT_NEAR(v_eng.mX, v_glm.x, err); \
    EXPECT_NEAR(v_eng.mY, v_glm.y, err)

#define EXPECT_VEC2_EQ(v_eng, v_glm) \
    EXPECT_FLOAT_EQ(v_eng.mX, v_glm.x); \
    EXPECT_FLOAT_EQ(v_eng.mY, v_glm.y)

namespace VIEngine {
    using namespace Math;

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
        EXPECT_VEC2_NEAR(vNorm, gNorm, 1e-6f);

        Vector2 vInPlace = v;
        Normalize(vInPlace);
        EXPECT_VEC2_NEAR(vInPlace, gNorm, 1e-6f);

        Vector2 vZero(0.0f, 0.0f);
        Vector2 vSafe = GetSafeNormalize(vZero);
        EXPECT_FLOAT_EQ(vSafe.mX, 0.0f);
        EXPECT_FLOAT_EQ(vSafe.mY, 0.0f);
    }

    TEST(Vector2MathTest, LerpAgainstGLM) {
        Vector2 start(0.0f, 0.0f);
        Vector2 end(10.0f, 5.0f);
        glm::vec2 gStart(0.0f, 0.0f);
        glm::vec2 gEnd(10.0f, 5.0f);
        
        float t = 0.35f;
        Vector2 vRes = Lerp(start, end, t);
        glm::vec2 gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, 1e-6f);

        t = 0;
        vRes = Lerp(start, end, t);
        gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, 1e-6f);
        
        t = 1;
        vRes = Lerp(start, end, t);
        gRes = glm::mix(gStart, gEnd, t);
        EXPECT_VEC2_NEAR(vRes, gRes, 1e-6f);
    }

    TEST(Vector2MathTest, ReflectAgainstGLM) {
        Vector2 incident(1.0f, -1.0f);
        Vector2 normal(0.0f, 1.0f); 
        glm::vec2 gIncident(1.0f, -1.0f);
        glm::vec2 gNormal(0.0f, 1.0f);

        Vector2 vRef = Reflect(incident, normal);
        glm::vec2 gRef = glm::reflect(gIncident, gNormal);

        EXPECT_VEC2_NEAR(vRef, gRef, 1e-6f);
    }

    TEST(Vector2MathTest, PointerAndAccess) {
        Vector2 v(1.23f, 4.56f);
        const float* ptr = GetValuePtr(v);

        ASSERT_NE(ptr, nullptr);
        EXPECT_EQ(ptr[0], v.mX);
        EXPECT_EQ(ptr[1], v.mY);
        
        glm::vec2 g(1.23f, 4.56f);
        float* gPtr = glm::value_ptr(g);
        EXPECT_FLOAT_EQ(ptr[0], gPtr[0]);
        EXPECT_FLOAT_EQ(ptr[1], gPtr[1]);
    }

    TEST(Vector2MathTest, SafeNormalizeThreshold) {
        float eps = 0.001f;
        Vector2 tiny(0.0005f, 0.0f);
        
        Vector2 res = GetSafeNormalize(tiny, eps);
        EXPECT_FLOAT_EQ(res.mX, 0.0f);
        EXPECT_FLOAT_EQ(res.mY, 0.0f);
        
        Vector2 notTiny(0.002f, 0.0f); 
        Vector2 res2 = GetSafeNormalize(notTiny, eps);
        EXPECT_NEAR(res2.mX, 1.0f, 1e-6f);
    }
}