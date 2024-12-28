#include <iostream>
using namespace std;

#define MAX 3000

bool readJolly(const int n)
{
    static bool diff[MAX];
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
        cout << (readJolly(n) ? "Jolly" : "Not jolly") << '\n';
        string tline;
        getline(cin, tline);
    }
}
