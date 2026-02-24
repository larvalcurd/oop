#include "Dictionary.h"
#include "StringUtils.h"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

std::string createTempFile(const std::string& content)
{
	std::string filename = "test_dict_tmp.txt";
	std::ofstream fout(filename);
	fout << content;
	fout.close();
	return filename;
}

void removeTempFile(const std::string& filename)
{
	std::remove(filename.c_str());
}

// ==================== addEntry ====================

TEST(AddEntry, SingleEntry)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");

	auto result = translateEngToRus(dict, "cat");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "кот");
}

TEST(AddEntry, MultipleTranslations)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");
	addEntry(dict, "cat", "кошка");

	auto result = translateEngToRus(dict, "cat");
	ASSERT_EQ(result.size(), 2);
	EXPECT_TRUE(result.count("кот"));
	EXPECT_TRUE(result.count("кошка"));
}

TEST(AddEntry, SetsModifiedFlag)
{
	DictionaryData dict;
	EXPECT_FALSE(dict.modified);

	addEntry(dict, "cat", "кот");
	EXPECT_TRUE(dict.modified);
}

TEST(AddEntry, StoresOriginalEntry)
{
	DictionaryData dict;
	addEntry(dict, "The Red Square", "Красная Площадь");

	ASSERT_EQ(dict.entries.size(), 1);
	EXPECT_EQ(dict.entries[0].first, "The Red Square");
	EXPECT_EQ(dict.entries[0].second, "Красная Площадь");
}

// ==================== translateEngToRus ====================

TEST(TranslateEngToRus, ExistingWord)
{
	DictionaryData dict;
	addEntry(dict, "dog", "собака");

	auto result = translateEngToRus(dict, "dog");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "собака");
}

TEST(TranslateEngToRus, NonExistingWord)
{
	DictionaryData dict;
	auto result = translateEngToRus(dict, "xyz");
	EXPECT_TRUE(result.empty());
}

TEST(TranslateEngToRus, CaseInsensitive)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");

	EXPECT_FALSE(translateEngToRus(dict, "CAT").empty());
	EXPECT_FALSE(translateEngToRus(dict, "Cat").empty());
	EXPECT_FALSE(translateEngToRus(dict, "cAt").empty());
	EXPECT_FALSE(translateEngToRus(dict, "cat").empty());
}

TEST(TranslateEngToRus, PreservesTranslationCase)
{
	DictionaryData dict;
	addEntry(dict, "the red square", "Красная Площадь");

	auto result = translateEngToRus(dict, "THE RED SQUARE");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "Красная Площадь");
}

TEST(TranslateEngToRus, EmptyDictionary)
{
	DictionaryData dict;
	auto result = translateEngToRus(dict, "anything");
	EXPECT_TRUE(result.empty());
}

// ==================== translateRusToEng ====================

TEST(TranslateRusToEng, ExistingWord)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");

	auto result = translateRusToEng(dict, "кот");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "cat");
}

TEST(TranslateRusToEng, NonExistingWord)
{
	DictionaryData dict;
	auto result = translateRusToEng(dict, "абракадабра");
	EXPECT_TRUE(result.empty());
}

TEST(TranslateRusToEng, CaseInsensitiveCyrillic)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");

	EXPECT_FALSE(translateRusToEng(dict, "кот").empty());
	EXPECT_FALSE(translateRusToEng(dict, "КОТ").empty());
	EXPECT_FALSE(translateRusToEng(dict, "Кот").empty());
}

TEST(TranslateRusToEng, MultipleRussianToSameEnglish)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");
	addEntry(dict, "cat", "кошка");

	auto fromKot = translateRusToEng(dict, "кот");
	auto fromKoshka = translateRusToEng(dict, "кошка");

	ASSERT_EQ(fromKot.size(), 1);
	EXPECT_EQ(*fromKot.begin(), "cat");

	ASSERT_EQ(fromKoshka.size(), 1);
	EXPECT_EQ(*fromKoshka.begin(), "cat");
}

TEST(TranslateRusToEng, PreservesOriginalCase)
{
	DictionaryData dict;
	addEntry(dict, "The Red Square", "Красная Площадь");

	auto result = translateRusToEng(dict, "красная площадь");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "The Red Square");
}

// ==================== Двунаправленный перевод ====================

TEST(Bidirectional, EngToRusAndBack)
{
	DictionaryData dict;
	addEntry(dict, "hello", "привет");

	auto rus = translateEngToRus(dict, "hello");
	ASSERT_FALSE(rus.empty());
	EXPECT_EQ(*rus.begin(), "привет");

	auto eng = translateRusToEng(dict, "привет");
	ASSERT_FALSE(eng.empty());
	EXPECT_EQ(*eng.begin(), "hello");
}

TEST(Bidirectional, MultipleTranslationsBothDirections)
{
	DictionaryData dict;
	addEntry(dict, "cat", "кот");
	addEntry(dict, "cat", "кошка");

	auto rus = translateEngToRus(dict, "cat");
	EXPECT_EQ(rus.size(), 2);
	EXPECT_TRUE(rus.count("кот"));
	EXPECT_TRUE(rus.count("кошка"));

	auto eng1 = translateRusToEng(dict, "кот");
	EXPECT_EQ(eng1.size(), 1);
	EXPECT_TRUE(eng1.count("cat"));

	auto eng2 = translateRusToEng(dict, "кошка");
	EXPECT_EQ(eng2.size(), 1);
	EXPECT_TRUE(eng2.count("cat"));
}

// ==================== loadDictionary ====================

TEST(LoadDictionary, ValidFile)
{
	std::string filename = createTempFile("cat|кот\ndog|собака\n");

	DictionaryData dict;
	loadDictionary(dict, filename);

	EXPECT_FALSE(dict.modified);

	auto cat = translateEngToRus(dict, "cat");
	ASSERT_EQ(cat.size(), 1);
	EXPECT_EQ(*cat.begin(), "кот");

	auto dog = translateEngToRus(dict, "dog");
	ASSERT_EQ(dog.size(), 1);
	EXPECT_EQ(*dog.begin(), "собака");

	removeTempFile(filename);
}

TEST(LoadDictionary, NonExistentFile)
{
	DictionaryData dict;
	loadDictionary(dict, "nonexistent_file_xyz.txt");

	EXPECT_TRUE(dict.engToRus.empty());
	EXPECT_TRUE(dict.rusToEng.empty());
	EXPECT_FALSE(dict.modified);
}

TEST(LoadDictionary, EmptyFile)
{
	std::string filename = createTempFile("");

	DictionaryData dict;
	loadDictionary(dict, filename);

	EXPECT_TRUE(dict.engToRus.empty());

	removeTempFile(filename);
}

TEST(LoadDictionary, MalformedLines)
{
	std::string filename = createTempFile("cat|кот\nbadline\n|empty\ndog|собака\n");

	DictionaryData dict;
	loadDictionary(dict, filename);

	EXPECT_EQ(dict.engToRus.size(), 2);
	EXPECT_FALSE(translateEngToRus(dict, "cat").empty());
	EXPECT_FALSE(translateEngToRus(dict, "dog").empty());

	removeTempFile(filename);
}

TEST(LoadDictionary, MultipleTranslationsInFile)
{
	std::string filename = createTempFile("cat|кот\ncat|кошка\n");

	DictionaryData dict;
	loadDictionary(dict, filename);

	auto result = translateEngToRus(dict, "cat");
	ASSERT_EQ(result.size(), 2);
	EXPECT_TRUE(result.count("кот"));
	EXPECT_TRUE(result.count("кошка"));

	removeTempFile(filename);
}

TEST(LoadDictionary, WhitespaceAroundDelimiter)
{
	std::string filename = createTempFile("  cat  |  кот  \n");

	DictionaryData dict;
	loadDictionary(dict, filename);

	auto result = translateEngToRus(dict, "cat");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "кот");

	removeTempFile(filename);
}

TEST(LoadDictionary, PreservesCase)
{
	std::string filename = createTempFile("The Red Square|Красная Площадь\n");

	DictionaryData dict;
	loadDictionary(dict, filename);

	auto result = translateEngToRus(dict, "the red square");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(*result.begin(), "Красная Площадь");

	auto reverse = translateRusToEng(dict, "красная площадь");
	ASSERT_EQ(reverse.size(), 1);
	EXPECT_EQ(*reverse.begin(), "The Red Square");

	removeTempFile(filename);
}

// ==================== saveDictionary ====================

TEST(SaveDictionary, SaveAndReload)
{
	std::string filename = "test_save_tmp.txt";

	{
		DictionaryData dict;
		addEntry(dict, "cat", "кот");
		addEntry(dict, "dog", "собака");
		saveDictionary(dict, filename);
	}

	{
		DictionaryData dict;
		loadDictionary(dict, filename);

		auto cat = translateEngToRus(dict, "cat");
		ASSERT_EQ(cat.size(), 1);
		EXPECT_EQ(*cat.begin(), "кот");

		auto dog = translateEngToRus(dict, "dog");
		ASSERT_EQ(dog.size(), 1);
		EXPECT_EQ(*dog.begin(), "собака");
	}

	removeTempFile(filename);
}

TEST(SaveDictionary, PreservesCaseOnSaveReload)
{
	std::string filename = "test_case_tmp.txt";

	{
		DictionaryData dict;
		addEntry(dict, "The Red Square", "Красная Площадь");
		saveDictionary(dict, filename);
	}

	{
		DictionaryData dict;
		loadDictionary(dict, filename);

		auto result = translateRusToEng(dict, "красная площадь");
		ASSERT_EQ(result.size(), 1);
		EXPECT_EQ(*result.begin(), "The Red Square");
	}

	removeTempFile(filename);
}

TEST(SaveDictionary, MultipleTranslationsPreserved)
{
	std::string filename = "test_multi_tmp.txt";

	{
		DictionaryData dict;
		addEntry(dict, "cat", "кот");
		addEntry(dict, "cat", "кошка");
		saveDictionary(dict, filename);
	}

	{
		DictionaryData dict;
		loadDictionary(dict, filename);

		auto result = translateEngToRus(dict, "cat");
		ASSERT_EQ(result.size(), 2);
		EXPECT_TRUE(result.count("кот"));
		EXPECT_TRUE(result.count("кошка"));
	}

	removeTempFile(filename);
}

// ==================== Комплексные сценарии ====================

TEST(Integration, FullWorkflow)
{
	DictionaryData dict;

	addEntry(dict, "cat", "кот");
	addEntry(dict, "cat", "кошка");
	addEntry(dict, "dog", "собака");
	addEntry(dict, "The Red Square", "Красная Площадь");

	auto catResult = translateEngToRus(dict, "CaT");
	EXPECT_EQ(catResult.size(), 2);

	auto kotResult = translateRusToEng(dict, "КОТ");
	ASSERT_EQ(kotResult.size(), 1);
	EXPECT_EQ(*kotResult.begin(), "cat");

	auto squareResult = translateEngToRus(dict, "the red square");
	ASSERT_EQ(squareResult.size(), 1);
	EXPECT_EQ(*squareResult.begin(), "Красная Площадь");

	auto unknown = translateEngToRus(dict, "xyz");
	EXPECT_TRUE(unknown.empty());

	EXPECT_TRUE(dict.modified);
}

TEST(Integration, SaveLoadRoundTrip)
{
	std::string filename = "test_roundtrip_tmp.txt";

	{
		DictionaryData dict;
		addEntry(dict, "cat", "кот");
		addEntry(dict, "cat", "кошка");
		addEntry(dict, "Hello World", "Привет Мир");
		saveDictionary(dict, filename);
	}

	{
		DictionaryData dict;
		loadDictionary(dict, filename);
		EXPECT_FALSE(dict.modified);

		addEntry(dict, "dog", "собака");
		EXPECT_TRUE(dict.modified);

		saveDictionary(dict, filename);
	}

	{
		DictionaryData dict;
		loadDictionary(dict, filename);

		EXPECT_EQ(translateEngToRus(dict, "cat").size(), 2);
		EXPECT_EQ(translateEngToRus(dict, "dog").size(), 1);
		EXPECT_EQ(translateEngToRus(dict, "hello world").size(), 1);
	}

	removeTempFile(filename);
}