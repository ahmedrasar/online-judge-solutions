#include <iostream>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-4-19

    Time complexity: O(n)
*/

const string QEWERYLAYOUT = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

char qwerty_left_shift(const char c)
{
    for (int i = 0; i < QEWERYLAYOUT.length(); ++i)
    {
        if (QEWERYLAYOUT[i] == c)
            return QEWERYLAYOUT[i - 1];
    }

    throw -1;
}

int main()
{
    string output;
    char c;
    while (cin.get(c))
    {
        if (!isspace(c))
            c = qwerty_left_shift(c);
        output += c;
    }

    cout << output;
    return 0;
}