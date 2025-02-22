#include <iostream>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

#define MAX 3000

bool read_jolly(const int n)
{
    bool diff[n];
    for (int i = 0; i < n; ++i)
        diff[i] = false;

    int cur, prev;
    cin >> prev;
    for (int i = 1; i < n; ++i)
    {
        cin >> cur;
        int d = abs(cur - prev);
        if (d >= n || diff[d])
            return false;
        diff[d] = true;
        prev = cur;
    }
    return true;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        cout << (read_jolly(n) ? "Jolly" : "Not jolly") << '\n';
        string tline;
        getline(cin, tline);
    }
}
