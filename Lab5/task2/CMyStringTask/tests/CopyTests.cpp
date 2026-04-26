#include <gtest/gtest.h>
#include "../src/CMyString.h"

TEST(CopyTests, ConstructorCopy_ValidString_CopiesData)
{
    CMyString original("Hello");
    CMyString copy(original);

    EXPECT_EQ(copy.GetLength(), 5u);
    EXPECT_STREQ(copy.GetStringData(), "Hello");

    EXPECT_NE(original.GetStringData(), copy.GetStringData());
}

TEST(CopyTests, ConstructorCopy_EmptyString_LengthIsZero)
{
    CMyString empty;
    CMyString copy(empty);

    EXPECT_EQ(copy.GetLength(), 0u);
    EXPECT_EQ(copy.GetCapacity(), 0u);
    
    
    const char* data = copy.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], '\0');


    EXPECT_EQ(empty.GetStringData(), copy.GetStringData());
}

TEST(CopyTests, ConstructorCopy_StringWithNull_PreservesLength)
{
    const char raw[] = {'A', 'B', '\0', 'C', 'D'};
    CMyString original(raw, 5);
    CMyString copy(original);

    EXPECT_EQ(copy.GetLength(), 5u);
    EXPECT_EQ(copy.GetCapacity(), 5u);

    const char* data = copy.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], 'A');
    EXPECT_EQ(data[1], 'B');
    EXPECT_EQ(data[2], '\0');   
    EXPECT_EQ(data[3], 'C');
    EXPECT_EQ(data[4], 'D');    
    EXPECT_EQ(data[5], '\0');
}

TEST(CopyTests, OperatorAssign_EmptyString_ReinitializesString)
{
    CMyString s1("non-empty");
    CMyString empty;
    s1 = empty;

    EXPECT_EQ(s1.GetLength(), 0u);
    EXPECT_EQ(s1.GetCapacity(), 0u);

    const char* data = s1.GetStringData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], '\0');
}

TEST(CopyTests, OperatorAssign_SelfAssignment_StaysValid)
{
    CMyString s("Hello");
    s = s;

    EXPECT_EQ(s.GetLength(), 5u);
    EXPECT_STREQ(s.GetStringData(), "Hello");
}

TEST(CopyTests, OperatorAssign_GeneralCase_SourceIsUnchanged)
{
    CMyString s1("Hello");
    CMyString s2("World");
    s2 = s1;

    EXPECT_EQ(s1.GetLength(), 5u);
    EXPECT_STREQ(s1.GetStringData(), "Hello");

    EXPECT_EQ(s2.GetLength(), 5u);
    EXPECT_STREQ(s2.GetStringData(), "Hello");
}

TEST(CopyTests, OperatorAssign_FromCString_UsesConvertingConstructor)
{
    CMyString s("Old");

    s = "NewValue";

    EXPECT_EQ(s.GetLength(), 8u);
    EXPECT_STREQ(s.GetStringData(), "NewValue");
}

TEST(CopyTests, OperatorAssign_FromStdString_UsesConvertingConstructorAndPreservesEmbeddedNulls)
{
    std::string source;
    source.push_back('A');
    source.push_back('\0');
    source.push_back('B');

    CMyString s("Old");
    s = source;

    ASSERT_EQ(s.GetLength(), 3u);
    EXPECT_EQ(s[0], 'A');
    EXPECT_EQ(s[1], '\0');
    EXPECT_EQ(s[2], 'B');
    EXPECT_EQ(s.GetStringData()[3], '\0');
}
