#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-4-19

    Time complexity: O(n)
*/

string common_permutation(string short_str, string long_str)
{
    if (short_str.empty() || long_str.empty())
        return "";

    if (short_str.size() > long_str.size())
        swap(short_str, long_str);

    unordered_map<char, int> freq_map;
    for (const auto c : short_str)
        ++freq_map[c];

    string result;
    for (const auto c : long_str)
    {
        if (freq_map.find(c) != freq_map.end() && freq_map[c] > 0)
        {
            --freq_map[c];
            result += c;

            if (result.size() == short_str.size())
                break;
        }
    }

    sort(result.begin(), result.end());
    return result;
}

int main()
{
    string first, second;
    while (getline(cin, first) && getline(cin, second))
        cout << common_permutation(first, second) << endl;

    return 0;
}