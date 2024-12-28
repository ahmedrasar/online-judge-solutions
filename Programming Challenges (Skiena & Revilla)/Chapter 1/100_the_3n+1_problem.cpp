#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int cycleIn(const int n)
{
    static auto DP = unordered_map<int, int>();
    static auto e = DP.end();

    if (n == 1)
        return 1;
    auto f = DP.find(n);
    if (f != e)
        return f->second;

    const int c = (n % 2 ? cycleIn(3 * n + 1) : cycleIn(n / 2)) + 1;
    DP[n] = c;
    return c;
}

int maxCycleBetween(int f, int l)
{
    if (f > l)
        std::swap(f, l);

    if (f < l / 2)
        /*
        assume l = 2m, and f < m
        let n be the number with the max cyc le max in range f:m,
        there exist 2n in range m:2m with cycle = cycles(n) + 1
        */
        f = l / 2;

    int maxLength = 0;
    for (int i = f; i <= l; ++i)
    {
        int t = cycleIn(i);
        maxLength = max(maxLength, t);
    }
    return maxLength;
}

int main()
{
    int f, l; // first, last
    while (cin >> f >> l)
    {
        cout << f << ' ' << l << ' ';
        cout << maxCycleBetween(f, l) << '\n';
    }
}