#include <gtest/gtest.h>
#include "../src/CMyString.h"

TEST(MoveTests, MoveConstructor_TransferOwhership_SourceBecomesEmpty)
{
    CMyString original("Hello, Move!");
    const char* oldData = original.GetStringData();

    CMyString target(std::move(original));  

    EXPECT_EQ(target.GetLength(), 12u);
    EXPECT_STREQ(target.GetStringData(), "Hello, Move!");
    EXPECT_EQ(target.GetStringData(), oldData);

    EXPECT_EQ(original.GetLength(), 0u);
    EXPECT_EQ(original.GetCapacity(), 0u);
    const char* sourceData = original.GetStringData();
    ASSERT_NE(sourceData, nullptr);
    EXPECT_EQ(sourceData[0], '\0');
}

TEST(MoveTests, MoveConstructor_EmptySource_ResultsInEmptyTarget)
{
    CMyString empty;
    CMyString target(std::move(empty));

    EXPECT_EQ(target.GetLength(), 0u);
    EXPECT_EQ(target.GetCapacity(), 0u);
    const char* targetData = target.GetStringData();
    ASSERT_NE(targetData, nullptr);
    EXPECT_EQ(targetData[0], '\0');

    EXPECT_STREQ(target.GetStringData(), "");
    EXPECT_EQ(empty.GetStringData(), target.GetStringData());
}

TEST(MoveTests, MoveAssignment_TransferOwnership_SourceBecomesEmpty)
{
    CMyString s1("Move Assignment");
    CMyString s2("temp");

    const char* oldData = s1.GetStringData();
    s2 = std::move(s1);

    EXPECT_EQ(s2.GetLength(), 15u);
    EXPECT_STREQ(s2.GetStringData(), "Move Assignment");
    EXPECT_EQ(s2.GetStringData(), oldData);

    EXPECT_EQ(s1.GetLength(), 0u);
    EXPECT_EQ(s1.GetCapacity(), 0u);
    EXPECT_STREQ(s1.GetStringData(), "");
}

TEST(MoveTests, MoveAssignment_SelfAssignment_NoChange)
{
    CMyString s("Self Move");
    const char* oldData = s.GetStringData();

    s = std::move(s);

    EXPECT_EQ(s.GetLength(), 9u);
    EXPECT_STREQ(s.GetStringData(), "Self Move");
    EXPECT_EQ(s.GetStringData(), oldData);
}

TEST(MoveTests, MoveConstructor_StringWithEmbeddedNulls_PreservesData)
{
    const char raw[] = {'A', 'B', '\0', 'C', 'D'};
    CMyString original(raw, 5);
    const char* oldData = original.GetStringData();

    CMyString target(std::move(original));

    EXPECT_EQ(target.GetLength(), 5u);
    EXPECT_EQ(target.GetCapacity(), 5u);

    const char* data = target.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], 'A');
    EXPECT_EQ(data[1], 'B');
    EXPECT_EQ(data[2], '\0');   
    EXPECT_EQ(data[3], 'C');
    EXPECT_EQ(data[4], 'D');    
    EXPECT_EQ(data[5], '\0');

    EXPECT_EQ(target.GetStringData(), oldData);

    EXPECT_EQ(original.GetLength(), 0u);
    EXPECT_EQ(original.GetCapacity(), 0u);
    const char* sourceData = original.GetStringData();
    ASSERT_NE(sourceData, nullptr);
    EXPECT_EQ(sourceData[0], '\0');
}