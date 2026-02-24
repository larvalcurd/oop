#include "UrlParser.h"
#include <gtest/gtest.h>

// Вспомогательная структура — хранит все выходные параметры ParseURL
struct ParseResult
{
	bool success;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
};

ParseResult Parse(const std::string& url)
{
	ParseResult r{};
	r.success = ParseURL(url, r.protocol, r.port, r.host, r.document);
	return r;
}

// ==================== Примеры из задания ====================

TEST(Examples, HttpNoPortNoDoc)
{
	// http://example.com → HOST: example.com, PORT: 80, DOC: ""
	auto r = Parse("http://example.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTP);
	EXPECT_EQ(r.host, "example.com");
	EXPECT_EQ(r.port, 80);
	EXPECT_EQ(r.document, "");
}

TEST(Examples, HttpMixedCaseWithPortAndDoc)
{
	// htTp://example.com:8080/index.html
	auto r = Parse("htTp://example.com:8080/index.html");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTP);
	EXPECT_EQ(r.host, "example.com");
	EXPECT_EQ(r.port, 8080);
	EXPECT_EQ(r.document, "index.html");
}

TEST(Examples, InvalidProtocol)
{
	// htp://example.com → ERROR
	auto r = Parse("htp://example.com");
	EXPECT_FALSE(r.success);
}

TEST(Examples, ComplexDocument)
{
	// http://www.mysite.com/docs/document1.html?page=30&lang=en#title
	auto r = Parse("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTP);
	EXPECT_EQ(r.host, "www.mysite.com");
	EXPECT_EQ(r.port, 80);
	EXPECT_EQ(r.document, "docs/document1.html?page=30&lang=en#title");
}

// ==================== Протоколы ====================

TEST(Protocol, HttpLowercase)
{
	auto r = Parse("http://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTP);
}

TEST(Protocol, HttpUppercase)
{
	auto r = Parse("HTTP://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTP);
}

TEST(Protocol, HttpMixedCase)
{
	auto r = Parse("HtTp://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTP);
}

TEST(Protocol, HttpsLowercase)
{
	auto r = Parse("https://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTPS);
}

TEST(Protocol, HttpsUppercase)
{
	auto r = Parse("HTTPS://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::HTTPS);
}

TEST(Protocol, FtpLowercase)
{
	auto r = Parse("ftp://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::FTP);
}

TEST(Protocol, FtpUppercase)
{
	auto r = Parse("FTP://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.protocol, Protocol::FTP);
}

// ==================== Порты по умолчанию ====================

TEST(DefaultPort, Http)
{
	auto r = Parse("http://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 80);
}

TEST(DefaultPort, Https)
{
	auto r = Parse("https://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 443);
}

TEST(DefaultPort, Ftp)
{
	auto r = Parse("ftp://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 21);
}

// ==================== Пользовательские порты ====================

TEST(CustomPort, MinPort)
{
	auto r = Parse("http://host.com:1");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 1);
}

TEST(CustomPort, MaxPort)
{
	auto r = Parse("http://host.com:65535");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 65535);
}

TEST(CustomPort, TypicalPort)
{
	auto r = Parse("http://host.com:8080");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 8080);
}

TEST(CustomPort, PortWithDocument)
{
	auto r = Parse("http://host.com:3000/api/v1");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.port, 3000);
	EXPECT_EQ(r.document, "api/v1");
}

// ==================== Хост ====================

TEST(Host, SimpleDomain)
{
	auto r = Parse("http://example.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.host, "example.com");
}

TEST(Host, SubDomain)
{
	auto r = Parse("http://www.example.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.host, "www.example.com");
}

TEST(Host, IpAddress)
{
	auto r = Parse("http://192.168.1.1");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.host, "192.168.1.1");
}

TEST(Host, Localhost)
{
	auto r = Parse("http://localhost");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.host, "localhost");
}

TEST(Host, SingleChar)
{
	auto r = Parse("http://a");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.host, "a");
}

// ==================== Документ ====================

TEST(Document, NoDocument)
{
	auto r = Parse("http://host.com");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "");
}

TEST(Document, TrailingSlashEmptyDoc)
{
	auto r = Parse("http://host.com/");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "");
}

TEST(Document, SimpleFile)
{
	auto r = Parse("http://host.com/index.html");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "index.html");
}

TEST(Document, NestedPath)
{
	auto r = Parse("http://host.com/a/b/c/file.txt");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "a/b/c/file.txt");
}

TEST(Document, WithQueryString)
{
	auto r = Parse("http://host.com/search?q=test&lang=en");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "search?q=test&lang=en");
}

TEST(Document, WithFragment)
{
	auto r = Parse("http://host.com/page#section");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "page#section");
}

TEST(Document, WithQueryAndFragment)
{
	auto r = Parse("http://host.com/page?id=1#top");
	ASSERT_TRUE(r.success);
	EXPECT_EQ(r.document, "page?id=1#top");
}

// ==================== Невалидные URL ====================

TEST(Invalid, EmptyString)
{
	EXPECT_FALSE(Parse("").success);
}

TEST(Invalid, NoProtocol)
{
	EXPECT_FALSE(Parse("example.com").success);
}

TEST(Invalid, WrongProtocol)
{
	EXPECT_FALSE(Parse("htp://example.com").success);
}

TEST(Invalid, TelnetProtocol)
{
	EXPECT_FALSE(Parse("telnet://example.com").success);
}

TEST(Invalid, MissingColonSlashSlash)
{
	EXPECT_FALSE(Parse("http:example.com").success);
}

TEST(Invalid, MissingSingleSlash)
{
	EXPECT_FALSE(Parse("http:/example.com").success);
}

TEST(Invalid, EmptyHost)
{
	EXPECT_FALSE(Parse("http:///document").success);
}

TEST(Invalid, EmptyHostWithPort)
{
	EXPECT_FALSE(Parse("http://:8080/doc").success);
}

TEST(Invalid, OnlyProtocol)
{
	EXPECT_FALSE(Parse("http://").success);
}

TEST(Invalid, PortZero)
{
	EXPECT_FALSE(Parse("http://host.com:0").success);
}

TEST(Invalid, PortAboveMax)
{
	EXPECT_FALSE(Parse("http://host.com:65536").success);
}

TEST(Invalid, PortWayAboveMax)
{
	EXPECT_FALSE(Parse("http://host.com:99999").success);
}

TEST(Invalid, PortOverflow)
{
	EXPECT_FALSE(Parse("http://host.com:99999999999999999999").success);
}

TEST(Invalid, PortNonNumeric)
{
	EXPECT_FALSE(Parse("http://host.com:abc").success);
}

TEST(Invalid, PortEmptyAfterColon)
{
	EXPECT_FALSE(Parse("http://host.com:/doc").success);
}

TEST(Invalid, RandomString)
{
	EXPECT_FALSE(Parse("not a url at all").success);
}