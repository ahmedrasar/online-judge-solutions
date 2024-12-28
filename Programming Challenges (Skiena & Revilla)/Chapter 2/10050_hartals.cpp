#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define isHoliday(d) (d % 7 == 6 || d % 7 == 0)

int readHartls(const int ps, const int ds)
{
    bool isHartl[ds + 1];
    memset(isHartl, false, sizeof(isHartl));

    int hartal = 0;
    for (int i = 0; i < ps; ++i)
    {
        int p;
        cin >> p;

        int d = p;
        while (d <= ds)
        {
            if (!isHoliday(d) && !isHartl[d])
            {
                isHartl[d] = true;
                ++hartal;
            }
            d += p;
        }
    }
    return hartal;
}

int main()
{
    int caseN;
    cin >> caseN;
    while (caseN--)
    {
        int d, p;
        cin >> d >> p;
        cout << readHartls(p, d) << '\n';
    }
}