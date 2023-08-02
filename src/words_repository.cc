#include "include/repository.h"

namespace demo_tdd_cxx
{
  list<ZhWord> g_lexicon;

  void InitLexicon()
  {
    g_lexicon.clear();
    g_lexicon.emplace_back("华为技术", "hwjs", "huaweijishu");
    g_lexicon.emplace_back("采访", "cf", "caifang"); // 简拼相同
    g_lexicon.emplace_back("财富", "cf", "caifu");
    g_lexicon.emplace_back("厨房", "cf", "chufang");
    g_lexicon.emplace_back("春风", "cf", "chunfeng");
    g_lexicon.emplace_back("赤峰", "cf", "chifeng");
    g_lexicon.emplace_back("深圳", "sz", "shenzhen");
    g_lexicon.emplace_back("华为", "hw", "huawei");
    g_lexicon.emplace_back("技术", "js", "jishu");
    g_lexicon.emplace_back("南京", "nj", "nanjing");
    g_lexicon.emplace_back("雨花台", "yht", "yuhuatai");
    g_lexicon.emplace_back("新闻", "xw", "xinwen");
    g_lexicon.emplace_back("大厦", "ds", "dasha");
    g_lexicon.emplace_back("高楼", "gl", "gaolou");
    g_lexicon.emplace_back("高校", "gx", "gaoxiao"); // 全拼、简拼都相同
    g_lexicon.emplace_back("高效", "gx", "gaoxiao");
    g_lexicon.emplace_back("高小", "gx", "gaoxiao");
    g_lexicon.emplace_back("美丽", "ml", "meili");
    g_lexicon.emplace_back("上下", "sx", "shangxiao");
    g_lexicon.emplace_back("南宁", "nl", "nanling"); // 错误拼音
  }

  list<string> GetWordsFromPinyin(const string &pinyin)
  {
    list<ZhWord> found_zh_words;

    for (auto const &zh_word : g_lexicon)
    {
      auto set_pinyin = zh_word.set_pinyin();

      if (set_pinyin.find(pinyin) != set_pinyin.end())
      {
        found_zh_words.push_back(zh_word);
      }
    }

    found_zh_words.sort();

    list<string> words;

    for (auto const &zh_word : found_zh_words)
    {
      words.push_back(zh_word.name());
    }

    return words;
  }

  ZhWord *GetZhWordByName(const string &name)
  {
    for (auto &zh_word : g_lexicon)
    {
      string _name = zh_word.name();

      if (_name == name)
      {
        return &zh_word;
      }
    }

    return nullptr;
  }

  void AddUsageCount(const string &name)
  {
    ZhWord *p_zh_word = GetZhWordByName(name);
    if (p_zh_word != nullptr)
    {
      p_zh_word->AddCount();
    }
  }

  void AddZhWord(const ZhWord &zh_word)
  {
    g_lexicon.remove_if([&zh_word](const ZhWord &_zh_word)
                        { return _zh_word.name() == zh_word.name(); });
    g_lexicon.push_back(zh_word);
  }
} // namespace demo_tdd_cxx