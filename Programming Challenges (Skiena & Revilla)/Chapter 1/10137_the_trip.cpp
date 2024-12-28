#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

int lowestExpenes(const vector<int> &students, const int sum)
{
    double avg = sum / double(students.size());
    int avgCeil = ceil(avg);
    int avgFloor = floor(avg);

    int chargeCeil = 0, chargeFloor = 0;
    for (const int x : students)
    {
        if (x > avgCeil)
            chargeCeil += (x - avgCeil);
        if (x > avgFloor)
            chargeFloor += (x - avgFloor);
    }

    return max(chargeCeil, chargeFloor);
}

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (!n)
            break;

        vector<int> studentsCents(n);
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int d, c;
            char t;
            cin >> d >> t >> c; // d.c
            studentsCents[i] = d * 100 + c;
            sum += studentsCents[i];
        }

        int expenxes = lowestExpenes(studentsCents, sum);
        int d = expenxes / 100;
        int c = expenxes % 100;
        cout << '$' << d << '.' << setw(2) << setfill('0') << c << '\n';
    }
}