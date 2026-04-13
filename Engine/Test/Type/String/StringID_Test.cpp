#include <gtest/gtest.h>
#include"Core/Type/String/StringID.h"

namespace VIEngine {
    TEST(StringIDTest, Consistency) {
        StringID id1("Player_Texture");
        StringID id2("Player_Texture");
        
        EXPECT_EQ(id1.GetData(), id2.GetData());
        EXPECT_TRUE(id1 == id2);
    }

    TEST(StringIDTest, Uniqueness) {
        StringID id1("Hero_Run");
        StringID id2("Hero_Idle");
        
        EXPECT_NE(id1.GetData(), id2.GetData());
        EXPECT_FALSE(id1 == id2);
    }

    TEST(StringIDTest, RawDataInitialization) {
        uint64_t raw = 123456789;
        StringID id(raw);
        EXPECT_EQ(id.GetData(), raw);
    }

    TEST(StringIDTest, EmptyString) {
        StringID id1("");
        StringID id2("");
        
        EXPECT_EQ(id1.GetData(), 0xcbf29ce484222325);
        EXPECT_EQ(id1, id2);
    }

    TEST(StringIDTest, STLContainerCompatibility) {
        std::unordered_set<StringID> idSet;
        StringID id1("Health_Bar");
        StringID id2("Mana_Bar");

        idSet.insert(id1);
        idSet.insert(id2);

        EXPECT_EQ(idSet.size(), 2);
        EXPECT_TRUE(idSet.find(StringID("Health_Bar")) != idSet.end());
    }

    TEST(StringIDTest, ConstexprHash) {
        constexpr uint64_t compileTimeHash = HashString("Static_Asset");
        StringID runtimeID("Static_Asset");
        EXPECT_EQ(runtimeID.GetData(), compileTimeHash);
    }
}