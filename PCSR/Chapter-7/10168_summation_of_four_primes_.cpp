#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

#define MAX 10000000
#define PRIMES_IN_MAX 664579

void init_primes();
bool is_prime(const int);
int primes[PRIMES_IN_MAX];

vector<int> get_sum_numbers(int n)
{
    static const auto emtpy_vec = vector<int>();
    if (n < 8)
        return emtpy_vec;
    auto vec = vector<int>(4);

    if (n % 2)
    {
        vec[0] = 2, vec[1] = 3;
        n -= 5;
    }
    else
    {
        vec[0] = 2, vec[1] = 2;
        n -= 4;
    }

    for (int i = 0; primes[i] < n; ++i)
    {
        if (is_prime(n - primes[i]))
        {
            vec[2] = primes[i], vec[3] = n - primes[i];
            return vec;
        }
    }
    return emtpy_vec;
}

int main()
{
    init_primes();
    int n;
    while (scanf("%d", &n) != EOF)
    {
        auto ans = get_sum_numbers(n);
        if (!ans.empty())
            printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
        else
            printf("%s\n", "Impossible.");
    }
}

bool _is_odd_prime[MAX / 2];
void init_primes()
{
    for (auto &p : _is_odd_prime)
        p = true;
    _is_odd_prime[0] = false;

    primes[0] = 2;
    int primeIndex = 1;
    const int limit(sqrt(MAX));
    for (int i = 3; i <= limit; i += 2)
    {
        if (_is_odd_prime[i / 2])
        {
            primes[primeIndex++] = i;
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