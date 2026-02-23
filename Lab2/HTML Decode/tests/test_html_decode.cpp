#include <gtest/gtest.h>
#include "html_decode.h"

// ============================================================
// TryDecodeEntity tests
// ============================================================

TEST(TryDecodeEntity, DecodesLessThan)
{
	auto result = TryDecodeEntity("&lt;");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result.value(), '<');
}

TEST(TryDecodeEntity, DecodesGreaterThan)
{
	auto result = TryDecodeEntity("&gt;");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result.value(), '>');
}

TEST(TryDecodeEntity, DecodesAmpersand)
{
	auto result = TryDecodeEntity("&amp;");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result.value(), '&');
}

TEST(TryDecodeEntity, DecodesQuote)
{
	auto result = TryDecodeEntity("&quot;");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result.value(), '"');
}

TEST(TryDecodeEntity, DecodesApos)
{
	auto result = TryDecodeEntity("&apos;");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result.value(), '\'');
}

TEST(TryDecodeEntity, ReturnsNulloptForUnknown)
{
	auto result = TryDecodeEntity("&unknown;");
	EXPECT_FALSE(result.has_value());
}

TEST(TryDecodeEntity, ReturnsNulloptForEmpty)
{
	auto result = TryDecodeEntity("");
	EXPECT_FALSE(result.has_value());
}

TEST(TryDecodeEntity, ReturnsNulloptForInvalid)
{
	auto result = TryDecodeEntity("&invalid");
	EXPECT_FALSE(result.has_value());
}

TEST(TryDecodeEntity, CaseSensitive)
{
	auto result = TryDecodeEntity("&LT;");
	EXPECT_FALSE(result.has_value());
}

// ============================================================
// HtmlDecode tests - Basic cases
// ============================================================

TEST(HtmlDecode, EmptyString)
{
	EXPECT_EQ(HtmlDecode(""), "");
}

TEST(HtmlDecode, NoEntities)
{
	EXPECT_EQ(HtmlDecode("Hello World"), "Hello World");
}

TEST(HtmlDecode, SingleEntity)
{
	EXPECT_EQ(HtmlDecode("&lt;"), "<");
	EXPECT_EQ(HtmlDecode("&gt;"), ">");
	EXPECT_EQ(HtmlDecode("&amp;"), "&");
	EXPECT_EQ(HtmlDecode("&quot;"), "\"");
	EXPECT_EQ(HtmlDecode("&apos;"), "'");
}

TEST(HtmlDecode, EntityAtStart)
{
	EXPECT_EQ(HtmlDecode("&lt;tag"), "<tag");
}

TEST(HtmlDecode, EntityAtEnd)
{
	EXPECT_EQ(HtmlDecode("tag&gt;"), "tag>");
}

TEST(HtmlDecode, EntityInMiddle)
{
	EXPECT_EQ(HtmlDecode("a&amp;b"), "a&b");
}

// ============================================================
// HtmlDecode tests - Multiple entities
// ============================================================

TEST(HtmlDecode, MultipleEntities)
{
	EXPECT_EQ(HtmlDecode("&lt;&gt;&amp;"), "<>&");
}

TEST(HtmlDecode, MultipleEntitiesWithText)
{
	EXPECT_EQ(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"),
		"Cat <says> \"Meow\". M&M's");
}

TEST(HtmlDecode, ConsecutiveEntities)
{
	EXPECT_EQ(HtmlDecode("&lt;&lt;&lt;"), "<<<");
}

// ============================================================
// HtmlDecode tests - Invalid/incomplete entities
// ============================================================

TEST(HtmlDecode, UnknownEntity)
{
	EXPECT_EQ(HtmlDecode("&unknown;"), "&unknown;");
}

TEST(HtmlDecode, IncompleteEntityNoSemicolon)
{
	EXPECT_EQ(HtmlDecode("&lt"), "&lt");
}

TEST(HtmlDecode, AmpersandWithoutEntity)
{
	EXPECT_EQ(HtmlDecode("&"), "&");
	EXPECT_EQ(HtmlDecode("M&M"), "M&M");
}

TEST(HtmlDecode, AmpersandFollowedByAmpersand)
{
	EXPECT_EQ(HtmlDecode("&&"), "&&");
	EXPECT_EQ(HtmlDecode("&&&"), "&&&");
}

TEST(HtmlDecode, EntityTooLong)
{
	// Если между & и ; больше MAX_ENTITY_LENGTH (6) символов
	EXPECT_EQ(HtmlDecode("&verylongtag;"), "&verylongtag;");
}

TEST(HtmlDecode, PartialMatch)
{
	EXPECT_EQ(HtmlDecode("&l"), "&l");
	EXPECT_EQ(HtmlDecode("&lt"), "&lt");
}

TEST(HtmlDecode, AmpersandBeforeSemicolon)
{
	EXPECT_EQ(HtmlDecode("&a&b;"), "&a&b;");
}

// ============================================================
// HtmlDecode tests - Edge cases
// ============================================================

TEST(HtmlDecode, OnlyAmpersand)
{
	EXPECT_EQ(HtmlDecode("&"), "&");
}

TEST(HtmlDecode, OnlySemicolon)
{
	EXPECT_EQ(HtmlDecode(";"), ";");
}

TEST(HtmlDecode, EmptyEntity)
{
	EXPECT_EQ(HtmlDecode("&;"), "&;");
}

TEST(HtmlDecode, NestedAmpersands)
{
	EXPECT_EQ(HtmlDecode("&amp&gt;"), "&amp>");
}

TEST(HtmlDecode, LongTextWithEntities)
{
	std::string input = "The quick brown fox &lt;jumps&gt; over the lazy dog &amp; says &quot;Hello&quot;";
	std::string expected = "The quick brown fox <jumps> over the lazy dog & says \"Hello\"";
	EXPECT_EQ(HtmlDecode(input), expected);
}

// ============================================================
// HtmlDecode tests - Real-world examples
// ============================================================

TEST(HtmlDecode, HtmlTag)
{
	EXPECT_EQ(HtmlDecode("&lt;div&gt;"), "<div>");
}

TEST(HtmlDecode, HtmlAttribute)
{
	EXPECT_EQ(HtmlDecode("&lt;a href=&quot;url&quot;&gt;"),
		"<a href=\"url\">");
}

TEST(HtmlDecode, XmlExample)
{
	EXPECT_EQ(HtmlDecode("&lt;?xml version=&quot;1.0&quot;?&gt;"),
		"<?xml version=\"1.0\"?>");
}

TEST(HtmlDecode, MathExpression)
{
	EXPECT_EQ(HtmlDecode("5 &lt; 10 &amp;&amp; 10 &gt; 5"),
		"5 < 10 && 10 > 5");
}

TEST(HtmlDecode, QuotedString)
{
	EXPECT_EQ(HtmlDecode("She said &quot;Hi&quot;"),
		"She said \"Hi\"");
}

TEST(HtmlDecode, Apostrophe)
{
	EXPECT_EQ(HtmlDecode("It&apos;s a test"),
		"It's a test");
}

// ============================================================
// HtmlDecode tests - Stress tests
// ============================================================

TEST(HtmlDecode, ManyAmpersands)
{
	EXPECT_EQ(HtmlDecode("&&&&&"), "&&&&&");
}

TEST(HtmlDecode, AllEntitiesSequential)
{
	std::string input = "&lt;&gt;&amp;&quot;&apos;";
	std::string expected = "<>&\"'";
	EXPECT_EQ(HtmlDecode(input), expected);
}

TEST(HtmlDecode, MixedValidInvalid)
{
	EXPECT_EQ(HtmlDecode("&lt;valid&gt; &invalid; &amp;"),
		"<valid> &invalid; &");
}

// ============================================================
// Integration test - Multiline (как в main)
// ============================================================

TEST(Integration, MultipleLines)
{
	// Симуляция построчной обработки
	std::vector<std::string> inputs = {
		"Cat &lt;says&gt; &quot;Meow&quot;",
		"&lt;div&gt;Hello&lt;/div&gt;",
		"M&amp;M&apos;s"
	};

	std::vector<std::string> expected = {
		"Cat <says> \"Meow\"",
		"<div>Hello</div>",
		"M&M's"
	};

	for (size_t i = 0; i < inputs.size(); ++i)
	{
		EXPECT_EQ(HtmlDecode(inputs[i]), expected[i]);
	}
}