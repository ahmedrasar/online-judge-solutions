#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
using namespace std;

#define MAXWORDS 16
#define CHARSINENGLISH 26
#define indexOfChar(c) (c - 'a')
#define NACHAR '*'
#define ENCODE 0
#define DECODE 1

auto dict = vector<unordered_set<string>>(MAXWORDS + 1);

int _getMappedState(const vector<vector<char>> &charmap, const string &iword)
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

bool _mapWord(const string &iword, const string &dword, vector<vector<char>> &charmap)
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

bool _decryptWords(const vector<string> &words, const int wIndex, vector<vector<char>> &pcharmap)
{
    if (wIndex == words.size())
        return true;

    const string iword = words[wIndex];
    const int mappedSate = _getMappedState(pcharmap, iword);
    if (mappedSate == 1)
        return _decryptWords(words, wIndex + 1, pcharmap);
    else if (mappedSate == -1)
        return false;

    const static auto e = dict[iword.size()].end();
    for (auto b = dict[iword.size()].begin(); b != e; ++b)
    {
        auto charmap = pcharmap;
        if (_mapWord(iword, *b, charmap) && _decryptWords(words, wIndex + 1, charmap))
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
    _decryptWords(words, 0, charmap);

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
