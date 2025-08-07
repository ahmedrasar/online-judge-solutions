#include <iostream>
using namespace std;

/*
    Author: Ahmed R. Asar
    Email: ahmed.ragab.a.asar@gmail.com
    Date: 2025-8-7

    Time complexity: O(n)
        n: the number of digits in the biggest nubmer.
*/

int carries_op(int x, int y)
{
    // Ensure x <= y
    if (x > y)
        swap(x, y);

    auto xstr = to_string(x), ystr = to_string(y);
    xstr = string(xstr.rbegin(), xstr.rend()), ystr = string(ystr.rbegin(), ystr.rend());

    int carries = 0;
    bool has_carry = false;
    for (int i = 0; i < ystr.size(); i++)
    {
        int sum = ystr[i] - '0' + has_carry;
        if (i < xstr.size())
            sum += xstr[i] - '0';

        has_carry = sum >= 10 ? true : false;
        if (has_carry)
            ++carries;
        else if (i > xstr.size())
            break;
    }
    return carries;
}

int main()
{

    int n, m;
    while (cin >> n >> m && (n | m))
    {
        auto carries = carries_op(n, m);
        if (carries == 0)
            cout << "No carry operation.";
        else if (carries == 1)
            cout << to_string(carries) + " carry operation.";
        else
            cout << to_string(carries) + " carry operations.";
        cout << '\n';
    }

    return 0;
}