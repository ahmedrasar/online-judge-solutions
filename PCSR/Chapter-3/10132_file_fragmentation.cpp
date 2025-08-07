#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    Author: Ahmed R. Asar
    Email: ahmed.ragab.a.asar@gmail.com
    Date: 2025-8-6

    Time complexity: O(n)
        n: the number of fragments.
*/

#define MAX_FILE_SIZE 256

bool valid_file(const string &file, const vector<vector<string>> &fragments)
{
    for (int i = 1; i < MAX_FILE_SIZE / 2; i++)
    {
        if (fragments[i].empty())
            continue;

        for (auto &frag1 : fragments[i])
        {
            if (!any_of(
                    fragments[file.size() - i].begin(),
                    fragments[file.size() - i].end(),
                    [&](const string &frag2)
                    {
                        return frag1 + frag2 == file || frag2 + frag1 == file;
                    }))
                return false;
        }
    }

    return true;
}

string restore_file(const int file_size, const vector<vector<string>> &fragments)
{
    string frag1;
    for (int i = 1; i < MAX_FILE_SIZE; i++)
    {
        if (!fragments[i].empty())
        {
            frag1 = *(fragments[i].begin());
            break;
        }
    }

    const auto &frag2_vec = fragments[file_size - frag1.size()];

    for (auto &frag2 : frag2_vec)
    {
        if (valid_file(frag1 + frag2, fragments))
            return frag1 + frag2;
        else if (valid_file(frag2 + frag1, fragments))
            return frag2 + frag1;
    }

    throw -1;
}

int main()
{

    int N;
    cin >> N;
    cin >> ws;

    while (N--)
    {
        vector<vector<string>> fragments(MAX_FILE_SIZE);
        int bits = 0, number_of_fragments = 0;

        string fragment;
        while (getline(cin, fragment) && !fragment.empty())
        {
            bits += fragment.size();
            ++number_of_fragments;
            fragments[fragment.size()].emplace_back(fragment);
        }

        const auto file_size = 2 * bits / number_of_fragments;

        auto file = restore_file(file_size, fragments);
        cout << file << '\n';

        if (N)
            cout << '\n';
    }

    return 0;
}