#include <iostream>
#include <vector>
using namespace std;
vector<vector<char>> editor;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

void draw_horizontal(const int x1, const int x2, const int y, const char c)
{
    int l, h;
    l = min(x1, x2);
    h = max(x1, x2);

    while (l <= h)
    {
        editor[y][l] = c;
        ++l;
    }
}
void draw_vertical(const int x, const int y1, const int y2, const char c)
{
    int l, h;
    l = min(y1, y2);
    h = max(y1, y2);

    while (l <= h)
    {
        editor[l][x] = c;
        ++l;
    }
}

void fill_region(const int x, const int y, const char oc, const char nc)
{
    if (y == -1 || y == editor.size() || x == -1 || x == editor[0].size() || editor[y][x] != oc)
        return;
    editor[y][x] = nc;
    fill_region(x - 1, y, oc, nc);
    fill_region(x + 1, y, oc, nc);
    fill_region(x, y - 1, oc, nc);
    fill_region(x, y + 1, oc, nc);
}

int main()
{
    while (true)
    {
        char op;
        cin >> op;
        switch (op)
        {
        case 'I':
        {
            int m, n;
            cin >> m >> n;
            editor = vector<vector<char>>(n, vector<char>(m, 'O'));
        }
        break;
        case 'C':
            for (auto &row : editor)
            {
                for (auto &c : row)
                    c = 'O';
            }
            break;
        case 'L':
        {
            int x, y;
            char c;
            cin >> x >> y >> c;
            --x, --y;
            editor[y][x] = c;
        }
        break;
        case 'V':
        {
            int x, y1, y2;
            char c;
            cin >> x >> y1 >> y2 >> c;
            --x, --y1, --y2;
            draw_vertical(x, y1, y2, c);
        }
        break;
        case 'H':
        {

            int x1, x2, y;
            char c;
            cin >> x1 >> x2 >> y >> c;
            --x1, --x2, --y;
            draw_horizontal(x1, x2, y, c);
        }
        break;
        case 'K':
        {
            int x1, y1, x2, y2;
            char c;
            cin >> x1 >> y1 >> x2 >> y2 >> c;
            --x1, --y1, --x2, --y2;
            /*
                x1 y1
                        x2 y2
            */
            int l = min(y1, y2);
            const int h = max(y1, y2);

            while (l <= h)
            {
                draw_horizontal(x1, x2, l, c);
                ++l;
            }
        }
        break;
        case 'F':
        {
            int x, y;
            char c;
            cin >> x >> y >> c;
            --x, --y;
            if (c != editor[y][x])
                fill_region(x, y, editor[y][x], c);
        }
        break;
        case 'S':
        {
            string s;
            cin >> s;
            cout << s << '\n';
            for (const auto &row : editor)
            {
                for (const auto c : row)
                    cout << c;
                cout << '\n';
            }
        }
        break;
        case 'X':
            return 0;
        default:
        {
            string tline;
            getline(cin, tline);
        }
        }
    }
    cout << '\n';
}