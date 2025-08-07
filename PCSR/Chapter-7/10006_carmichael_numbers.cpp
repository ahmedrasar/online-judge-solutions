#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;
// TODO: Remove unused imports.

#include <fstream>
#include <chrono>
#include <cmath>

#include <bitset>
#include <cstdio>
#include <vector>

/*
    Author: Ahmed R. Asar
    Email: ahmed.ragab.a.asar@gmail.com
    Date: 2025-8-7

    Time complexity: O(n*log(log(n))) for initlizing primes
        n: the upper limit of the range.

    Time complexity: O(n*log(n)) for carmichael test
        n: the number of which we try to test.
*/

#define MAX 65000

void init();
bool is_carmichael(const int);

int pow_mod(long long base, int exp, int mod)
{
    long long result = 1;
    while (exp)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main()
{
    init();

    int n;
    while (cin >> n && n)
        cout << (is_carmichael(n) ? "The number " + to_string(n) + " is a Carmichael number." : to_string(n) + " is normal.") << '\n';

    return 0;
}

bool _is_odd_prime[MAX / 2];

void init_primes()
{
    for (auto &p : _is_odd_prime)
        p = true;
    _is_odd_prime[0] = false;

    const int limit(sqrt(MAX));
    for (int i = 3; i <= limit; i += 2)
    {
        if (_is_odd_prime[i / 2])
        {
            for (int w = i * i; w < MAX; w += 2 * i)
                _is_odd_prime[w / 2] = false;
        }
    }
}

bool is_prime(const int n)
{
    if (n == 2)
        return true;
    else if (n % 2)
        return _is_odd_prime[n / 2];
    else
        return false;
}

bool _is_carmichael(const int n)
{
    if (is_prime(n))
        return false;
    for (int i = 2; i < n; i++)
    {
        if (pow_mod(i, n, n) != i)
            return false;
    }
    return true;
}

unordered_set<int> carmichaels;
void init_carmichael()
{
    for (int i = 0; i < MAX; i++)
    {
        if (_is_carmichael(i))
            carmichaels.emplace(i);
    }
}

bool is_carmichael(const int n)
{
    return carmichaels.find(n) != carmichaels.end();
}

void init()
{
    init_primes();
    init_carmichael();
}
