#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

#define MAXWORDS 16
#define CHARSINENGLISH 26
#define indexOfChar(c) (c - 'a')
#define NACHAR '*'
#define ENCODE 0
#define DECODE 1

auto dict = vector<unordered_set<string>>(MAXWORDS + 1);

int _get_mapping_state(const vector<vector<char>> &charmap, const string &iword)
{
    string dword;
    for (const char c : iword)
    {
        const auto dchar = charmap[DECODE][indexOfChar(c)];
        if (dchar == NACHAR)
            return 0;
        dword += dchar;
    }

    static const auto e = dict[iword.size()].end();
    return (dict[dword.size()].find(dword) != e ? 1 : -1);
}

bool _is_mapped_word(const string &iword, const string &dword, vector<vector<char>> &charmap)
{
    for (int i = 0; i < iword.size(); ++i)
    {
        if ((charmap[DECODE][indexOfChar(iword[i])] != dword[i]) &&
            (charmap[ENCODE][indexOfChar(dword[i])] != NACHAR || charmap[DECODE][indexOfChar(iword[i])] != NACHAR))
            return false;

        charmap[DECODE][indexOfChar(iword[i])] = dword[i];
        charmap[ENCODE][indexOfChar(dword[i])] = iword[i];
    }

    return true;
}

bool _decrypt_words(const vector<string> &words, const int index, vector<vector<char>> &pcharmap)
{
    if (index == words.size())
        return true;

    const string iword = words[index];
    const int mapping_sate = _get_mapping_state(pcharmap, iword);
    if (mapping_sate == 1)
        return _decrypt_words(words, index + 1, pcharmap);
    else if (mapping_sate == -1)
        return false;

    const static auto e = dict[iword.size()].end();
    for (auto b = dict[iword.size()].begin(); b != e; ++b)
    {
        auto charmap = pcharmap;
        if (_is_mapped_word(iword, *b, charmap) && _decrypt_words(words, index + 1, charmap))
        {
            pcharmap = charmap;
            return true;
        }
    }
    return false;
}

string decrypt(const string &line)
{
    vector<string> words;
    istringstream _lstream(line);
    string _word;
    while (_lstream >> _word)
        words.push_back(_word);

    auto charmap = vector<vector<char>>(2, vector<char>(CHARSINENGLISH, NACHAR)); // encode, decode
    _decrypt_words(words, 0, charmap);

    string dline;
    dline.reserve(line.size());
    for (const char c : line)
        dline += (c == ' ' ? ' ' : charmap[DECODE][indexOfChar(c)]);
    return dline;
}

int main()
{

    int sz;
    cin >> sz;
    for (int i = 0; i < sz; ++i)
    {
        string word;
        cin >> word;
        dict[word.size()].emplace(word);
    }
    cin.get();

    string line;
    while (getline(cin, line))
        cout << decrypt(line) << '\n';
}
