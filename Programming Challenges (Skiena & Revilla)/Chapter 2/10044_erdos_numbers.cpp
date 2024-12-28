#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define NAMEDIVIDER ','
#define ENDCHAR ':'
#define ERDOSNAME "Erdos, P."

int main()
{
    int caseN;
    cin >> caseN;
    for (int i = 0; i < caseN; ++i)
    {
        int p, n;
        cin >> p >> n;
        cin.get();

        unordered_map<string, int> indexOfAuthor;
        const static auto e = indexOfAuthor.end();
        int _authorID = 0;
        unordered_map<int, unordered_set<int>> coAuthors;
        for (int j = 0; j < p; ++j)
        {
            vector<string> authors;
            string _author;
            string paper;
            getline(cin, paper);
            istringstream iss(paper);
            bool _fnameRead = false;
            char _c;
            while (iss.get(_c)) // read names
            {
                if (_c == NAMEDIVIDER || _c == ENDCHAR)
                {
                    if (_fnameRead)
                    {
                        if (indexOfAuthor.find(_author) == e)
                            indexOfAuthor[_author] = _authorID++;
                        authors.push_back(_author);
                        _author.clear();
                    }
                    _fnameRead = !_fnameRead;
                    if (_c == ENDCHAR)
                        break;
                    if (!_fnameRead)
                    {
                        iss.get(); // consumes the ' ' after ','
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
                    coAuthors[indexOfAuthor[author]].emplace(indexOfAuthor[coAuthor]);
                }
            }
        }
        unordered_set<int> isVisited;
        const static auto isVisitedEnd = isVisited.end();
        queue<pair<int, int>> BFS;
        BFS.emplace(indexOfAuthor[ERDOSNAME], 0);
        isVisited.insert(indexOfAuthor[ERDOSNAME]);
        unordered_map<int, int> erdos;
        const static auto erdoEnd = erdos.end();
        while (!BFS.empty())
        {
            const auto indexErdos = BFS.front();
            const int authorIndex = indexErdos.first;
            const int authorErdos = indexErdos.second;
            erdos[authorIndex] = authorErdos;
            for (const int coAuthorIndex : coAuthors[authorIndex])
            {
                if (isVisited.find(coAuthorIndex) != isVisitedEnd)
                    continue;
                BFS.emplace(coAuthorIndex, authorErdos + 1);
                isVisited.insert(coAuthorIndex);
            }
            BFS.pop();
        }

        const static auto indexOfAuthorEnd = indexOfAuthor.end();
        cout << "Scenario " << i + 1 << '\n';
        for (int i = 0; i < n; ++i)
        {
            string name;
            getline(cin, name);
            cout << name << ' ';
            auto _f = indexOfAuthor.find(name);
            int index = (_f != indexOfAuthorEnd ? _f->second : -1);
            auto f = erdos.find(index);
            if (f == erdoEnd)
                cout << "infinity";
            else
                cout << f->second;
            cout << '\n';
        }
    }
}