#ifndef DEMO_TDD_CXX_REPOSITORY_H_
#define DEMO_TDD_CXX_REPOSITORY_H_

#include <list>
#include <set>
#include <string>

using std::list;
using std::set;
using std::string;

namespace demo_tdd_cxx
{

  class ZhWord
  {
  public:
    ZhWord(const string &name, const string &pinyin1, const string &pinyin2) : name_(name)
    {
      set_pinyin_.insert(pinyin1);
      set_pinyin_.insert(pinyin2);
    }

    string name() const
    {
      return name_;
    }

    const set<string, std::less<> > &set_pinyin() const
    {
      return set_pinyin_;
    }

    int count() const
    {
      return count_;
    }

    void AddCount()
    {
      count_++;
    }

    bool operator<(const ZhWord &other) const
    {
      return count_ > other.count_;
    }

    bool operator==(const ZhWord &other) const
    {
      return (name_ == other.name_) && (set_pinyin_ == other.set_pinyin_);
    }

  private:
    string name_;                          // 中文词语名
    set<string, std::less<> > set_pinyin_; // 保存拼音
    int count_ = 0;                        // 使用计数
  };

  void InitLexicon();
  list<string> GetWordsFromPinyin(const string &pinyin);
  ZhWord *GetZhWordByName(const string &name);
  void AddUsageCount(const string &name);
  void AddZhWord(const ZhWord &zh_word);

} // namespace demo_tdd_cxx

#endif // DEMO_TDD_CXX_REPOSITORY_H_