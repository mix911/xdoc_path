#include <iostream>
#include <string>
#include <list>

#include <gtest/gtest.h>

using namespace std;

std::string letters_in_word_inversion(const std::string& s)
{
    auto reverse = [](std::string::iterator bit, std::string::iterator eit)
    {
        for (; bit != eit && eit - bit != 1; ++bit, --eit)
        {
            std::swap(*bit, *(eit - 1));
        }
    };
    std::string r = s;
    if (s.empty())
    {
        return "";
    }
    auto bit = r.begin();
    for (auto eit = r.begin() + 1; eit != r.end(); ++eit)
    {
        if (*eit == ' ')
        {
            reverse(bit, eit);
            bit = eit + 1;
            eit = bit;
            continue;
        }
        if (*eit == '.')
        {
            reverse(bit, eit);
            bit = eit + 1;
            if (bit != r.end())
            {
                ++bit;
                eit = bit;
            }
            continue;
        }
    }
    return r;
}

std::string words_inversion(const std::string& s)
{
    std::string r;
    size_t old_size = 0;
    auto bit = s.begin();
    auto eit = std::find(bit, s.end(), '.');
    auto find_space = [](std::string::const_iterator beg, std::string::const_iterator it)
    {
        for (; it != beg && *(it - 1) != ' '; --it)
        {
        }
        return it;
    };
    for (; 
         eit != s.end(); 
         bit = std::find_if(eit, s.end(), [](char ch) { return ch != '.' && ch != ' '; }), eit = std::find(bit, s.end(), '.'))
    {
        auto word_eit = eit;
        auto word_bit = find_space(bit, word_eit);
        for (; word_bit != bit; word_eit = word_bit - 1, word_bit = find_space(bit, word_eit - 1))
        {
            r += std::string(word_bit, word_eit);
            r += ' ';
        }
        r += std::string(word_bit, word_eit);
        r += ". ";
    }
    if (r.empty() == false && r.back() == ' ')
    {
        r.pop_back();
    }
    return r;
}

TEST(LettersCase, LettersTest)
{
    ASSERT_EQ(letters_in_word_inversion(""), "");
    ASSERT_EQ(letters_in_word_inversion("a."), "a.");
    ASSERT_EQ(letters_in_word_inversion("abcd."), "dcba.");
    ASSERT_EQ(letters_in_word_inversion("a b c. d f g."), "a b c. d f g.");
    ASSERT_EQ(letters_in_word_inversion("ab cd. ef gh."), "ba dc. fe hg.");
    ASSERT_EQ(letters_in_word_inversion("abc def ghi."), "cba fed ihg.");
    ASSERT_EQ(letters_in_word_inversion("abc def ghi. ABC DEF GHI."), "cba fed ihg. CBA FED IHG.");
    ASSERT_EQ(letters_in_word_inversion("abc def ghi. ABC DEFGHI."), "cba fed ihg. CBA IHGFED.");

    ASSERT_EQ(words_inversion("a."), "a.");
    ASSERT_EQ(words_inversion("abcd."), "abcd.");
    ASSERT_EQ(words_inversion("a b c. d f g."), "c b a. g f d.");
    ASSERT_EQ(words_inversion("ab cd. ef gh."), "cd ab. gh ef.");
    ASSERT_EQ(words_inversion("abc def ghi."), "ghi def abc.");
    ASSERT_EQ(words_inversion("abc def ghi. ABC DEF GHI."), "ghi def abc. GHI DEF ABC.");
    ASSERT_EQ(words_inversion("abc def ghi. ABC DEFGHI."), "ghi def abc. DEFGHI ABC.");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}