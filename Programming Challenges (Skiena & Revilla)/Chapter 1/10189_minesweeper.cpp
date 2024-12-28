#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Field
{
public:
    static constexpr char mineSymbol = '*';
    using fieldType = vector<vector<char>>;

    struct Index
    {
        int n, m;
    };

    Field(const int n, const int m)
    {
        field.resize(n, vector<char>(m, '0'));
    }

    void addMine(const int n, const int m)
    {
        field[n][m] = mineSymbol;
        mines.push_back({n, m});
    }
    void sweep()
    {
        for (const auto &x : mines)
            sweepMine(x);
    }

private:
    vector<Index> mines;
    fieldType field;
    void incremnetElemnet(const int n, const int m)
    {
        if (field[n][m] == mineSymbol)
            return;
        ++field[n][m];
    }
    void sweepMine(const Field::Index &mine)
    {
        int n = mine.n;
        int m = mine.m;
        auto size = getSizeIndex();

        for (int r = n - 1; r < n + 2; ++r)
        {
            if (r == -1 || r == size.n)
                continue;

            for (int c = m - 1; c < m + 2; ++c)
            {
                if (c == -1 || c == size.m)
                    continue;
                incremnetElemnet(r, c);
            }
        }
    }

public:
    Index getSizeIndex() const { return Index{int(field.size()), int(field[0].size())}; }
    const vector<Index> &getMines() const { return mines; }
    const fieldType &getField() const { return field; }
};

void readIntoField(Field &f)
{
    auto size = f.getSizeIndex();
    for (int i = 0; i < size.n; ++i)
    {
        for (int j = 0; j < size.m; ++j)
        {
            char c;
            cin >> c;
            if (c == Field::mineSymbol)
                f.addMine(i, j);
        }
    }
}

void printField(const Field &f)
{
    static int fieldN = 0;
    if (fieldN != 0)
        cout << '\n';
    cout << "Field #" << ++fieldN << ":\n";
    for (auto &row : f.getField())
    {
        for (const char element : row)
            cout << element;
        cout << '\n';
    }
}

int main()
{
    int n, m;
    while (cin >> n >> m && n != 0)
    {
        auto f = Field(n, m);
        readIntoField(f);
        f.sweep();
        printField(f);
    }
}
