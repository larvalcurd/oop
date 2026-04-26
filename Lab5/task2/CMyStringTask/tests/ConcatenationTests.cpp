#include <gtest/gtest.h>
#include "../src/CMyString.h"

TEST(ConcatenationTests, OperatorPlusAssign_NonEmptyStrings_AppendsCorrectly)
{
    CMyString s1("Hello");
    CMyString s2(", World!");
    s1 += s2;
    EXPECT_EQ(s1.GetLength(), 13u);
    EXPECT_STREQ(s1.GetStringData(), "Hello, World!");
}

TEST(ConcatenationTests, OperatorPlusAssign_EmptySource_StringUnchanged)
{
    CMyString s1("Hello");
    CMyString empty;
    s1 += empty;
    EXPECT_EQ(s1.GetLength(), 5u);
    EXPECT_STREQ(s1.GetStringData(), "Hello");
}

TEST(ConcatenationTests, OperatorPlusAssign_EmptyTarget_CopiesSource)
{
    CMyString empty;
    CMyString s2("World");
    empty += s2;
    EXPECT_EQ(empty.GetLength(), 5u);
    EXPECT_STREQ(empty.GetStringData(), "World");
}

TEST(ConcatenationTests, OperatorPlusAssign_SelfAppend_DoublesString)
{
    CMyString s("Repeat");
    s += s;
    EXPECT_EQ(s.GetLength(), 12u);
    EXPECT_STREQ(s.GetStringData(), "RepeatRepeat");
}

TEST(ConcatenationTests, OperatorPlusAssign_LargeAppend_ReallocatesMemory)
{
    CMyString s("Start"); 
    CMyString more("MoreText"); 
    size_t oldCap = s.GetCapacity();
    s += more;
    EXPECT_GT(s.GetCapacity(), oldCap); 
    EXPECT_EQ(s.GetLength(), 13u);

    EXPECT_STREQ(s.GetStringData(), "StartMoreText");
}

TEST(ConcatenationTests, OperatorPlus_TwoMyStrings_ReturnsConcatenated)
{
    CMyString s1("Hello");
    CMyString s2(" World");
    CMyString result = s1 + s2;
    EXPECT_EQ(result.GetLength(), 11u);
    EXPECT_STREQ(result.GetStringData(), "Hello World");

    EXPECT_STREQ(s1.GetStringData(), "Hello");
    EXPECT_STREQ(s2.GetStringData(), " World");
}

TEST(ConcatenationTests, OperatorPlus_StdStringAndMyString_ReturnsConcatenated)
{
    std::string stdStr = "std::";
    CMyString s2("suffix");
    CMyString result = stdStr + s2; 
    EXPECT_STREQ(result.GetStringData(), "std::suffix");
}

TEST(ConcatenationTests, OperatorPlus_CStringAndMyString_ReturnsConcatenated)
{
    const char* cstr = "C-";
    CMyString s2("style");
    CMyString result = cstr + s2;
    EXPECT_STREQ(result.GetStringData(), "C-style");
}

TEST(ConcatenationTests, OperatorPlusAssign_StringsWithNulls_PreservesBinaryData)
{
    const char raw1[] = {'A', '\0', 'B'};
    const char raw2[] = {'C', '\0', 'D'};
    CMyString s1(raw1, 3);
    CMyString s2(raw2, 3);
    s1 += s2;
    EXPECT_EQ(s1.GetLength(), 6u);
    const char* data = s1.GetStringData();
    EXPECT_EQ(data[0], 'A');
    EXPECT_EQ(data[1], '\0');
    EXPECT_EQ(data[2], 'B');
    EXPECT_EQ(data[3], 'C');
    EXPECT_EQ(data[4], '\0');
    EXPECT_EQ(data[5], 'D');
    EXPECT_EQ(data[6], '\0'); 
}