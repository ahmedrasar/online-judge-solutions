#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-2-24

    Time Complexity: O(n)
*/

vector<string> find_doublets(const string &bword, const string &eword, const vector<string> &dict)
{
    if (bword.length() != eword.length())
        return vector<string>();

    if (bword == eword)
        return vector<string>{bword};
    const int word_length = bword.length();
    const int n = dict.size();
    unordered_map<string, int> word_map;
    for (int i = 0; i < n; ++i)
    {
        if (dict[i].length() == word_length)
            word_map.emplace(dict[i], i);
    }

    const auto end = word_map.end();
    if (word_map.find(bword) == end || word_map.find(eword) == end)
        return vector<string>();
    const int ew_id = word_map[eword];
    const int bw_id = word_map[bword];

    // BFS
    int prev_word[n];
    memset(prev_word, -1, sizeof(prev_word));
    prev_word[ew_id] = ew_id;

    queue<int> qu;
    qu.emplace(ew_id);

    while (!qu.empty())
    {
        const auto id = qu.front();
        for (int i = 0; i < word_length; ++i)
        {
            auto word = dict[id];
            for (char c = 'a'; c <= 'z'; ++c)
            {
                word[i] = c;
                if (word_map.find(word) == end)
                    continue;

                const int next_id = word_map[word];
                if (prev_word[next_id] != -1)
                    continue;

                prev_word[next_id] = id;
                if (next_id == bw_id)
                    break;

                qu.emplace(next_id);
            }
        }

        qu.pop();
    }
    if (prev_word[bw_id] == -1)
        return vector<string>();

    vector<string> dls;
    for (int i = bw_id; i != ew_id; i = prev_word[i])
        dls.emplace_back(dict[i]);
    dls.emplace_back(eword);
    return dls;
}

int main()
{
    vector<string> dict;

    string line;
    while (getline(cin, line) && !line.empty())
        dict.emplace_back(line);

    while (getline(cin, line) && !line.empty())
    {
        string bword, eword;
        istringstream iss(line);
        iss >> bword >> eword;
        const auto dls = find_doublets(bword, eword, dict);
        if (dls.empty())
            cout << "No solution.\n";
        else
        {
            for (const auto &word : dls)
                cout << word << '\n';
        }
        if (cin.peek() != EOF)
            cout << '\n';
    }
}