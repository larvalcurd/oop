#include "StringUtils.h"
#include <gtest/gtest.h>

// ==================== toLower ====================

TEST(ToLower, AsciiLowercase)
{
	EXPECT_EQ(toLower("hello"), "hello");
}

TEST(ToLower, AsciiUppercase)
{
	EXPECT_EQ(toLower("HELLO"), "hello");
}

TEST(ToLower, AsciiMixedCase)
{
	EXPECT_EQ(toLower("HeLLo WoRLd"), "hello world");
}

TEST(ToLower, EmptyString)
{
	EXPECT_EQ(toLower(""), "");
}

TEST(ToLower, Numbers)
{
	EXPECT_EQ(toLower("Test123"), "test123");
}

TEST(ToLower, CyrillicUppercase)
{
	EXPECT_EQ(toLower("ПРИВЕТ"), "привет");
}

TEST(ToLower, CyrillicLowercase)
{
	EXPECT_EQ(toLower("привет"), "привет");
}

TEST(ToLower, CyrillicMixedCase)
{
	EXPECT_EQ(toLower("ПрИвЕт"), "привет");
}

TEST(ToLower, CyrillicYo)
{
	EXPECT_EQ(toLower("Ёж"), "ёж");
	EXPECT_EQ(toLower("ёж"), "ёж");
	EXPECT_EQ(toLower("ЁЖИК"), "ёжик");
}

TEST(ToLower, CyrillicFullAlphabet)
{
	EXPECT_EQ(toLower("АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"),
		"абвгдежзийклмнопрстуфхцчшщъыьэюя");
}

TEST(ToLower, MixedLatinCyrillic)
{
	EXPECT_EQ(toLower("Hello ПРИВЕТ"), "hello привет");
}

TEST(ToLower, CyrillicPhrase)
{
	EXPECT_EQ(toLower("Красная Площадь"), "красная площадь");
}

// ==================== trim ====================

TEST(Trim, NoWhitespace)
{
	EXPECT_EQ(trim("hello"), "hello");
}

TEST(Trim, LeadingSpaces)
{
	EXPECT_EQ(trim("   hello"), "hello");
}

TEST(Trim, TrailingSpaces)
{
	EXPECT_EQ(trim("hello   "), "hello");
}

TEST(Trim, BothSidesSpaces)
{
	EXPECT_EQ(trim("   hello   "), "hello");
}

TEST(Trim, Tabs)
{
	EXPECT_EQ(trim("\thello\t"), "hello");
}

TEST(Trim, Newlines)
{
	EXPECT_EQ(trim("\nhello\r\n"), "hello");
}

TEST(Trim, InternalSpacesPreserved)
{
	EXPECT_EQ(trim("  hello world  "), "hello world");
}

TEST(Trim, EmptyString)
{
	EXPECT_EQ(trim(""), "");
}

TEST(Trim, OnlyWhitespace)
{
	EXPECT_EQ(trim("   \t\r\n  "), "");
}

TEST(Trim, CyrillicWithSpaces)
{
	EXPECT_EQ(trim("  Привет мир  "), "Привет мир");
}

// ==================== hasCyrillic ====================

TEST(HasCyrillic, PureAscii)
{
	EXPECT_FALSE(hasCyrillic("hello world"));
}

TEST(HasCyrillic, PureCyrillic)
{
	EXPECT_TRUE(hasCyrillic("привет"));
}

TEST(HasCyrillic, MixedText)
{
	EXPECT_TRUE(hasCyrillic("hello привет"));
}

TEST(HasCyrillic, EmptyString)
{
	EXPECT_FALSE(hasCyrillic(""));
}

TEST(HasCyrillic, NumbersOnly)
{
	EXPECT_FALSE(hasCyrillic("12345"));
}

TEST(HasCyrillic, SingleCyrillicChar)
{
	EXPECT_TRUE(hasCyrillic("а"));
}

TEST(HasCyrillic, CyrillicYo)
{
	EXPECT_TRUE(hasCyrillic("ё"));
	EXPECT_TRUE(hasCyrillic("Ё"));
}

TEST(HasCyrillic, SpecialCharsNoCyrillic)
{
	EXPECT_FALSE(hasCyrillic("!@#$%^&*()"));
}