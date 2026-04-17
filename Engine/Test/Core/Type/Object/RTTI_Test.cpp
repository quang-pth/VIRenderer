#include<gtest/gtest.h>
#include"Core/Type/Object/RTTI.h"

namespace Test {
    using namespace VIEngine;
    
    class Base {
    DECLARE_RTTI
    public:
        virtual ~Base() = default;
    };
    DEFINE_RTTI_NO_PARENT(Base)

    class Derived : public Base {
        DECLARE_RTTI
    };
    DEFINE_RTTI(Derived, Base::RunTimeType)

    class Leaf : public Derived {
        DECLARE_RTTI
    };
    DEFINE_RTTI(Leaf, Derived::RunTimeType)

    class Stranger {
        DECLARE_RTTI
    };
    DEFINE_RTTI_NO_PARENT(Stranger)

    TEST(RTTITest, BasicInformation) {
        EXPECT_STREQ(Base::RunTimeType.GetTypeName(), "Base");
        EXPECT_EQ(Base::RunTimeType.GetTypeNameID(), StringID("Base"));
        
        EXPECT_EQ(Base::RunTimeType.GetParentClass(), nullptr);
        EXPECT_EQ(Derived::RunTimeType.GetParentClass(), &Base::RunTimeType);
        EXPECT_EQ(Leaf::RunTimeType.GetParentClass(), &Derived::RunTimeType);
    }

    TEST(RTTITest, IsTypeOf) {
        EXPECT_TRUE(Base::RunTimeType.IsTypeOf(Base::RunTimeType));
        EXPECT_TRUE(Derived::RunTimeType.IsTypeOf(Derived::RunTimeType));
        
        EXPECT_FALSE(Derived::RunTimeType.IsTypeOf(Base::RunTimeType));
        EXPECT_FALSE(Base::RunTimeType.IsTypeOf(Derived::RunTimeType));
    }

    TEST(RTTITest, IsDerivedFrom) {
        EXPECT_TRUE(Derived::RunTimeType.IsDerivedFrom(Base::RunTimeType));
        
        EXPECT_TRUE(Leaf::RunTimeType.IsDerivedFrom(Base::RunTimeType));
        EXPECT_TRUE(Leaf::RunTimeType.IsDerivedFrom(Derived::RunTimeType));
        
        EXPECT_FALSE(Base::RunTimeType.IsDerivedFrom(Derived::RunTimeType));
        
        EXPECT_FALSE(Leaf::RunTimeType.IsDerivedFrom(Stranger::RunTimeType));
        EXPECT_FALSE(Stranger::RunTimeType.IsDerivedFrom(Base::RunTimeType));
    }

    TEST(RTTITest, VirtualFunctionIntegration) {
        Base* polyLeaf = new Leaf();
        
        EXPECT_STREQ(polyLeaf->GetRunTimeTypeInfo().GetTypeName(), "Leaf");
        EXPECT_TRUE(polyLeaf->GetRunTimeTypeInfo().IsDerivedFrom(Base::RunTimeType));
        EXPECT_TRUE(polyLeaf->GetRunTimeTypeInfo().IsDerivedFrom(Derived::RunTimeType));
        
        delete polyLeaf;
    }
}