#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

#define is_holiday(d) (d % 7 == 6 || d % 7 == 0)

int read_hartls(const int ps, const int ds)
{
    bool is_hartl[ds + 1];
    memset(is_hartl, false, sizeof(is_hartl));

    int hartal = 0;
    for (int i = 0; i < ps; ++i)
    {
        int p;
        cin >> p;

        int d = p;
        while (d <= ds)
        {
            if (!is_holiday(d) && !is_hartl[d])
            {
                is_hartl[d] = true;
                ++hartal;
            }
            d += p;
        }
    }
    return hartal;
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int d, p;
        cin >> d >> p;
        cout << read_hartls(p, d) << '\n';
    }
}