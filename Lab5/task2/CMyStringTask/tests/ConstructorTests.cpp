#include <gtest/gtest.h>
#include "../src/CMyString.h"

TEST(ConstructorTests, DefaultConstructor_ShouldCreateEmptyString)
{
    CMyString s; 
    EXPECT_EQ(s.GetLength(), 0);
    EXPECT_EQ(s.GetCapacity(), 0u);
    const char* data = s.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], '\0');
}

TEST(ConstructorTests, ConstructorFromCString_ShouldCopyData)
{
    CMyString s("Hello");
    EXPECT_EQ(s.GetLength(), 5u);
    EXPECT_EQ(s.GetCapacity(), 5u);
    EXPECT_STREQ(s.GetStringData(), "Hello");
}

TEST(ConstructorTests, ConstructorFromCString_HandleNullptr_ShouldCreateEmptyString)
{
    CMyString s(nullptr);
    EXPECT_EQ(s.GetLength(), 0u);
    EXPECT_EQ(s.GetCapacity(), 0u);
    const char* data = s.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], '\0');
}

TEST(ConstructorTests, ConstructorWithLength_ShouldHandleEmbeddedNull)
{
    const char raw[] = {'A', 'B', '\0', 'C', 'D'};
    CMyString s(raw, 5);

    EXPECT_EQ(s.GetLength(), 5u);
    EXPECT_EQ(s.GetCapacity(), 5u);

    const char* data = s.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], 'A');
    EXPECT_EQ(data[1], 'B');
    EXPECT_EQ(data[2], '\0');   
    EXPECT_EQ(data[3], 'C');
    EXPECT_EQ(data[4], 'D');
    EXPECT_EQ(data[5], '\0'); 
}

TEST(ConstructorTests, ConstructorWithLength_ZeroLength_ShouldCreateEmptyString)
{
    CMyString s("Hello", 0);

    EXPECT_EQ(s.GetLength(), 0u);
    EXPECT_EQ(s.GetCapacity(), 0u);

    const char* data = s.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_STREQ(s.GetStringData(), "");
    EXPECT_EQ(data[0], '\0');
}