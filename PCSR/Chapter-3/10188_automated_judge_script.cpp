#include <iostream>
#include <vector>
using namespace std;

/*s
    Author: Ahmed R. Asar
    Date: 2025-8-6

    Time complexity: O(n)
        n: min(number_of_characters(expected_ans), number_of_characters(actual_ans)).
*/

string extract_digits(const vector<string> &);

int main()
{
    int N;

    int n;
    while (cin >> n && n)
    {
        vector<string> expected(n);
        cin.get();
        for (auto &line : expected)
            getline(cin, line);

        int m;
        cin >> m;
        vector<string> actual(m);
        cin.get();
        for (auto &line : actual)
            getline(cin, line);

        cout << "Run #" << ++N << ": ";
        if (expected == actual)
            cout << "Accepted";
        else if (extract_digits(expected) == extract_digits(actual))
            cout << "Presentation Error";
        else
            cout << "Wrong Answer";
        cout << '\n';
    }

    return 0;
}

string extract_digits(const vector<string> &vec)
{
    string digits;
    for (const auto &s : vec)
    {
        for (char c : s)
        {
            if (isdigit(c))
                digits += c;
        }
    }
    return digits;
}