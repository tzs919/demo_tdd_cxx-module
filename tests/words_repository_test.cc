#include "include/repository.h"

#include <gtest/gtest.h>

using namespace demo_tdd_cxx;

class WordsRepository : public testing::Test
{
protected:
  void SetUp() override
  {
    printf("------SetUp-------\n");
    InitLexicon();
  }

  void TearDown() override
  {
    printf("------TearDown---\n");
  }
};

TEST_F(WordsRepository, ShouldReturnEmptyIfPinyinIsNotExist)
{
  list<string> result = GetWordsFromPinyin("noword");
  EXPECT_TRUE(result.empty());
}

TEST_F(WordsRepository, ShouldReturnOneWordIfJianPinIsExist)
{
  list<string> result = GetWordsFromPinyin("hwjs");
  EXPECT_EQ(result.size(), 1);
  EXPECT_TRUE(result.front() == "华为技术");
}

TEST_F(WordsRepository, ShouldReturnOneWordIfQuanPinIsExist1)
{
  list<string> result = GetWordsFromPinyin("huaweijishu");
  EXPECT_EQ(result.size(), 1);
  EXPECT_TRUE(result.front() == "华为技术");
}

TEST_F(WordsRepository, ShouldReturnOneWordIfQuanPinIsExist2)
{
  list<string> result = GetWordsFromPinyin("chunfeng");
  EXPECT_EQ(result.size(), 1);
  EXPECT_TRUE(result.front() == "春风");
}

TEST_F(WordsRepository, ShouldReturnMultiWordsIfJianPinIsExist)
{
  list<string> result = GetWordsFromPinyin("cf");
  EXPECT_GT(result.size(), 1);

  list<string> expected = {"采访", "财富", "厨房", "春风", "赤峰"};
  EXPECT_EQ(result, expected);
}

TEST_F(WordsRepository, ShouldReturnMultiWordsIfQuanPinIsExist)
{
  list<string> result = GetWordsFromPinyin("gaoxiao");
  EXPECT_GT(result.size(), 1);

  list<string> expected = {"高校", "高效", "高小"};
  EXPECT_EQ(result, expected);
}

TEST_F(WordsRepository, ShouldEnabledUsageCount)
{
  const ZhWord *p_zh_word = GetZhWordByName("厨房");
  EXPECT_EQ(p_zh_word->count(), 0);

  AddUsageCount("厨房");
  EXPECT_EQ(p_zh_word->count(), 1);

  AddUsageCount("厨房");
  EXPECT_EQ(p_zh_word->count(), 2);
}

TEST_F(WordsRepository, ShouldReturnSortedMultiWordsIfJianpinIsExist)
{
  AddUsageCount("厨房");
  AddUsageCount("厨房");
  AddUsageCount("厨房");
  AddUsageCount("春风");
  AddUsageCount("春风");
  AddUsageCount("财富");

  list<string> result = GetWordsFromPinyin("cf");
  EXPECT_GT(result.size(), 1);

  list<string> expected = {"厨房", "春风", "财富", "采访", "赤峰"};
  EXPECT_EQ(result, expected);
}

TEST_F(WordsRepository, ShouldEnabledAddNewZhWord)
{
  ZhWord zh_word_new("祖国", "zg", "zuguo");
  AddZhWord(zh_word_new);

  const ZhWord *p_zh_word_new = GetZhWordByName("祖国");
  EXPECT_EQ(*p_zh_word_new, zh_word_new);
}

TEST_F(WordsRepository, ShouldOverrideOldZhWordByAdd)
{
  ZhWord zh_word_new("南宁", "nn", "nanning");
  const ZhWord *p_zh_word_old = GetZhWordByName("南宁");

  EXPECT_FALSE(p_zh_word_old == nullptr);
  EXPECT_FALSE(*p_zh_word_old == zh_word_new);

  AddZhWord(zh_word_new);

  const ZhWord *p_zh_word_new = GetZhWordByName("南宁");
  EXPECT_TRUE(*p_zh_word_new == zh_word_new);
}