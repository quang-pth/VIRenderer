#pragma once

#define EXPECT_VEC2_EQ(v_eng, v_glm) \
    EXPECT_FLOAT_EQ(v_eng.X, v_glm.x); \
    EXPECT_FLOAT_EQ(v_eng.Y, v_glm.y)

#define EXPECT_VEC2_NEAR(v_engine, v_glm, abs_error) \
    EXPECT_NEAR(v_engine.X, v_glm.x, abs_error); \
    EXPECT_NEAR(v_engine.Y, v_glm.y, abs_error)

#define EXPECT_VEC3_NEAR(v_engine, v_glm, abs_error) \
    EXPECT_NEAR(v_engine.X, v_glm.x, abs_error); \
    EXPECT_NEAR(v_engine.Y, v_glm.y, abs_error); \
    EXPECT_NEAR(v_engine.Z, v_glm.z, abs_error)

#define EXPECT_VEC3_EQ(v_eng, v_glm) \
    EXPECT_FLOAT_EQ(v_eng.X, v_glm.x); \
    EXPECT_FLOAT_EQ(v_eng.Y, v_glm.y); \
    EXPECT_FLOAT_EQ(v_eng.Z, v_glm.Z)

namespace Test {
    constexpr float BASE_EPSILON = 1e-6f;
}