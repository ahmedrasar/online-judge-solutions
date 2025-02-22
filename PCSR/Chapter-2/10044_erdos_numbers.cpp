#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

#define NAMEDIVIDER ','
#define ENDCHAR ':'
#define ERDOSNAME "Erdos, P."

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int p, n;
        cin >> p >> n;
        cin.get();

        unordered_map<string, int> index_of_author;
        const static auto e = index_of_author.end();
        int _author_id = 0;
        unordered_map<int, unordered_set<int>> co_authors;
        for (int j = 0; j < p; ++j)
        {
            vector<string> authors;
            string _author;
            string paper;
            getline(cin, paper);
            istringstream iss(paper);
            bool _fname_read = false;
            char _c;

            // Read names
            while (iss.get(_c))
            {
                if (_c == NAMEDIVIDER || _c == ENDCHAR)
                {
                    if (_fname_read)
                    {
                        if (index_of_author.find(_author) == e)
                            index_of_author[_author] = _author_id++;
                        authors.push_back(_author);
                        _author.clear();
                    }
                    _fname_read = !_fname_read;
                    if (_c == ENDCHAR)
                        break;
                    if (!_fname_read)
                    {
                        iss.get(); // Consumes the ' ' after the ','
                        continue;
                    }
                }
                _author += _c;
            }

            for (const auto &author : authors)
            {
                for (const auto &coAuthor : authors)
                {
                    if (author == coAuthor)
                        continue;
                    co_authors[index_of_author[author]].emplace(index_of_author[coAuthor]);
                }
            }
        }
        unordered_set<int> is_visited;
        const static auto is_visited_end = is_visited.end();
        queue<pair<int, int>> BFS;
        BFS.emplace(index_of_author[ERDOSNAME], 0);
        is_visited.insert(index_of_author[ERDOSNAME]);
        unordered_map<int, int> erdos;
        const static auto erdo_end = erdos.end();
        while (!BFS.empty())
        {
            const auto index_erdos = BFS.front();
            const int author_index = index_erdos.first;
            const int author_erdos = index_erdos.second;
            erdos[author_index] = author_erdos;
            for (const int co_author_index : co_authors[author_index])
            {
                if (is_visited.find(co_author_index) != is_visited_end)
                    continue;
                BFS.emplace(co_author_index, author_erdos + 1);
                is_visited.insert(co_author_index);
            }
            BFS.pop();
        }

        const static auto index_of_author_end = index_of_author.end();
        cout << "Scenario " << i + 1 << '\n';
        for (int i = 0; i < n; ++i)
        {
            string name;
            getline(cin, name);
            cout << name << ' ';
            auto _f = index_of_author.find(name);
            int index = (_f != index_of_author_end ? _f->second : -1);
            auto f = erdos.find(index);
            if (f == erdo_end)
                cout << "infinity";
            else
                cout << f->second;
            cout << '\n';
        }
    }
}