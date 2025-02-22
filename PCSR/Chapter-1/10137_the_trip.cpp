#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

int calc_lowest_expenes(const vector<int> &students, const int sum)
{
    const double avg = sum / double(students.size());

    int charge_ceil = 0, charge_floor = 0;
    for (const int x : students)
    {
        if (x > avg)
            charge_ceil += floor(x - avg);
        else if (x < avg)
            charge_floor += floor(avg - x);
    }

    return max(charge_ceil, charge_floor);
}

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (!n)
            break;

        vector<int> students_cents(n);
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int d, c;
            char t;
            cin >> d >> t >> c; // Input format: d.c
            students_cents[i] = d * 100 + c;
            sum += students_cents[i];
        }

        int expenxes = calc_lowest_expenes(students_cents, sum);
        int d = expenxes / 100;
        int c = expenxes % 100;
        cout << '$' << d << '.' << setw(2) << setfill('0') << c << '\n';
    }
}