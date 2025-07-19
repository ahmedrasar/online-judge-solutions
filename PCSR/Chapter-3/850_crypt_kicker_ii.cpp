#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-7-20

    Time complexity: O(n)
*/

const string ptl = "the quick brown fox jumps over the lazy dog";

vector<int> extract_words_sizes(const vector<string> &words);
vector<string> split(const string &line);
string decipher(string line, vector<char> cipher_map);

vector<char> deduce_cipher_map(const string &line)
{
    static const auto ptl_words = split(ptl);
    static const auto ptl_words_sizes = extract_words_sizes(ptl_words);
    const auto words = split(line);
    const auto words_sizes = extract_words_sizes(words);
    if (ptl_words_sizes != words_sizes)
        return {};

    static auto UNKOWN_CHAR = '?';
    vector<char> cipher_map(26, UNKOWN_CHAR);
    for (int i = 0; i < ptl_words.size(); i++)
    {
        for (int j = 0; j < ptl_words[i].size(); j++)
        {
            auto &c = cipher_map[words[i][j] - 'a'];
            if (c != UNKOWN_CHAR && c != ptl_words[i][j])
                return {};
            c = ptl_words[i][j];
        }
    }

    return cipher_map;
}

int main()
{

    int N;
    cin >> N;
    cin >> ws;

    while (N--)
    {
        vector<string> lines;
        string _line;
        while (getline(cin, _line) && !_line.empty())
            lines.emplace_back(_line);

        vector<char> cipher_map;
        for (const auto line : lines)
        {
            cipher_map = deduce_cipher_map(line);
            if (!cipher_map.empty())
                break;
        }

        if (cipher_map.empty())
        {
            cout << "No solution.\n";
        }
        else
        {
            for (const auto line : lines)
                cout << decipher(line, cipher_map) << '\n';
        }

        if (N)
            cout << '\n';
    }

    return 0;
}

string decipher(string line, vector<char> cipher_map)
{
    string dline;
    for (auto const c : line)
        dline += c == ' ' ? ' ' : cipher_map[c - 'a'];
    return dline;
}

vector<string> split(const string &line)
{
    vector<string> words;
    istringstream iss(line);
    string word;

    while (iss >> word)
        words.push_back(word);

    return words;
}

vector<int> extract_words_sizes(const vector<string> &words)
{
    vector<int> wsizes;
    transform(words.begin(), words.end(),
              std::back_inserter(wsizes),
              [](const std::string &word)
              {
                  return word.size();
              });
    return wsizes;
}