#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define MAX 10000000
#define PRIMES_IN_MAX 664579

void initprimes();
bool isprime(const int);
int primes[PRIMES_IN_MAX];

vector<int> fourPrimesSum(int n)
{
    static const auto emtpyvec = vector<int>();
    if (n < 8)
        return emtpyvec;
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
        if (isprime(n - primes[i]))
        {
            vec[2] = primes[i], vec[3] = n - primes[i];
            return vec;
        }
    }
    return emtpyvec;
}

int main()
{
    initprimes();
    int n;
    while (scanf("%d", &n) != EOF)
    {
        auto ans = fourPrimesSum(n);
        if (!ans.empty())
            printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
        else
            printf("%s\n", "Impossible.");
    }
}

bool _isOddPrime[MAX / 2];
void initprimes()
{
    for (auto &p : _isOddPrime)
        p = true;
    _isOddPrime[0] = false;

    primes[0] = 2;
    int primeIndex = 1;
    const int limit(sqrt(MAX));
    for (int i = 3; i <= limit; i += 2)
    {
        if (_isOddPrime[i / 2])
        {
            primes[primeIndex++] = i;
            for (int w = i * i; w < MAX; w += 2 * i)
                _isOddPrime[w / 2] = false;
        }
    }
}

bool isprime(const int n)
{
    if (n == 2)
        return true;
    else if (n % 2)
        return _isOddPrime[n / 2];
    else
        return false;
}