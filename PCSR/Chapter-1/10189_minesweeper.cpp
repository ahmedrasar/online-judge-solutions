#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

class Field
{
public:
    static constexpr char MINESYMBOL = '*';
    using FieldType = vector<vector<char>>;

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
        field[n][m] = MINESYMBOL;
        mines.push_back({n, m});
    }
    void sweep()
    {
        for (const auto &x : mines)
            sweep_mine(x);
    }

private:
    vector<Index> mines;
    FieldType field;
    void incremnet_elemnet(const int n, const int m)
    {
        if (field[n][m] == MINESYMBOL)
            return;
        ++field[n][m];
    }
    void sweep_mine(const Field::Index &mine)
    {
        int n = mine.n;
        int m = mine.m;
        auto size = get_size_index();

        for (int r = n - 1; r < n + 2; ++r)
        {
            if (r == -1 || r == size.n)
                continue;

            for (int c = m - 1; c < m + 2; ++c)
            {
                if (c == -1 || c == size.m)
                    continue;
                incremnet_elemnet(r, c);
            }
        }
    }

public:
    Index get_size_index() const { return Index{int(field.size()), int(field[0].size())}; }
    const vector<Index> &getMines() const { return mines; }
    const FieldType &getField() const { return field; }
};

void read_into_field(Field &f)
{
    auto size = f.get_size_index();
    for (int i = 0; i < size.n; ++i)
    {
        for (int j = 0; j < size.m; ++j)
        {
            char c;
            cin >> c;
            if (c == Field::MINESYMBOL)
                f.addMine(i, j);
        }
    }
}

void print_field(const Field &f)
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
        read_into_field(f);
        f.sweep();
        print_field(f);
    }
}
