#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

int cycle_in(const int n)
{
    static auto DP = unordered_map<int, int>();
    static auto e = DP.end();

    if (n == 1)
        return 1;
    auto f = DP.find(n);
    if (f != e)
        return f->second;

    const int c = (n % 2 ? cycle_in(3 * n + 1) : cycle_in(n / 2)) + 1;
    DP[n] = c;
    return c;
}

int max_cycle_between(int f, int l)
{
    if (f > l)
        std::swap(f, l);

    if (f < l / 2)
    {
        /*
        Assume l = 2m, and f < m
        Let n be the number with the max cyc le max in range f:m, there exist 2n in range m:2m with cycle = cycles(n) + 1.
        */
        f = l / 2;
    }

    int max_length = 0;
    for (int i = f; i <= l; ++i)
    {
        int t = cycle_in(i);
        max_length = max(max_length, t);
    }
    return max_length;
}

int main()
{
    int f, l; // First, Last
    while (cin >> f >> l)
    {
        cout << f << ' ' << l << ' ';
        cout << max_cycle_between(f, l) << '\n';
    }
}