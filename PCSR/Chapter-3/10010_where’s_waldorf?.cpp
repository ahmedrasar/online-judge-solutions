#include <iostream>
#include <vector>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-4-19

    Time complexity: O(m+n)
*/

bool word_in(const vector<vector<char>> &grid, const string &word, int i, int j, const int di, const int dj)
{
    const int m = grid.size();
    const int n = grid[0].size();
    const int size = word.size();

    if (i + (size - 1) * di >= m || i + (size - 1) * di < 0 ||
        j + (size - 1) * dj >= n || j + (size - 1) * dj < 0)
        return false;

    for (int k = 0; k < size; ++k)
    {
        if (grid[i][j] != word[k])
            return false;
        i += di;
        j += dj;
    }

    return true;
}

pair<int, int> search(const vector<vector<char>> &grid, const string &word)
{
    const int m = grid.size();
    const int n = grid[0].size();
    const int size = word.size();

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] == word[0])
            {
                for (int di = -1; di < 2; ++di)
                {
                    for (int dj = -1; dj < 2; ++dj)
                    {
                        if (di == 0 && dj == 0)
                            continue;
                        if (word_in(grid, word, i, j, di, dj))
                            return {i + 1, j + 1};
                    }
                }
            }
        }
    }

    throw -1;
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int m, n;
        cin >> m >> n;
        vector<vector<char>> grid(m, vector<char>(n));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> grid[i][j];
                grid[i][j] = tolower(grid[i][j]);
            }
        }

        int searchs;
        cin >> searchs;
        while (searchs--)
        {
            string word;
            cin >> word;
            for (auto &c : word)
                c = tolower(c);
            const auto index = search(grid, word);
            cout << index.first << ' ' << index.second << '\n';
        }

        if (N)
            cout << '\n';
    }

    return 0;
}