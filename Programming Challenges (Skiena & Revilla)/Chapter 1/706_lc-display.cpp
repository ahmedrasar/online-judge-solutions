#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LCD
{
public:
    static constexpr char emptyFill = ' ';
    static constexpr char horizontalFill = '-';
    static constexpr char verticalFill = '|';
    static constexpr const char *spaceBeweenDigits = " ";
    void display(const int n, const int s)
    {
        digitSize = s;
        lcdBuffer = to_string(n);
        printBuffer();
    };

private:
    using r_type = bool;
    using c_type = pair<bool, bool>;

    struct Digit
    {
        /*
            r0
        c00     c01
            r1
        c10     c11
            r2
        */
        static const Digit Digits[10];
        static const Digit &digitFromChar(const char c) { return Digits[c - '0']; }

        r_type rs[3];
        c_type cs[2];

    private:
        Digit(const int s);
    };

    void printBuffer()
    {
        /*
        the command line prints line by line, hence we must print the horizontal line of the whole number before getting to the one next one
        we print the row/column of all numbers at once then go the the next row/column
        */

        cout << rowAsString(0);
        cout << columnAsString(0);
        cout << rowAsString(1);
        cout << columnAsString(1);
        cout << rowAsString(2);
        cout << '\n';
    }
    int digitSize;

    string lcdBuffer;

    string getColumnLine(const int columnIndex)
    {
        string line;
        for (int j = 0; j < lcdBuffer.size(); ++j)
        {
            if (Digit::digitFromChar(lcdBuffer[j]).cs[columnIndex].first)
                line += verticalFill;
            else
                line += emptyFill;
            for (int i = 0; i < digitSize; i++)
                line += emptyFill;
            if (Digit::digitFromChar(lcdBuffer[j]).cs[columnIndex].second)
                line += verticalFill;
            else
                line += emptyFill;
            if (j != lcdBuffer.size() - 1)
                line += spaceBeweenDigits;
        }

        line += '\n';
        return line;
    }

    string rowAsString(const int rowIndex)
    {
        string row;
        for (int j = 0; j < lcdBuffer.size(); ++j)
        {
            row += emptyFill;
            char ch = Digit::digitFromChar(lcdBuffer[j]).rs[rowIndex] ? horizontalFill : emptyFill;
            string str(digitSize, ch);
            row += str;
            row += emptyFill;

            if (j != lcdBuffer.size() - 1)
                row += spaceBeweenDigits;
        }

        row += '\n';
        return row;
    }

    string columnAsString(const int columnIndex)
    {
        string singleLine = getColumnLine(columnIndex);
        string column;
        for (int i = 0; i < digitSize; ++i) // for every line
            column += singleLine;

        return column;
    }
};

const LCD::Digit LCD::Digit::Digits[10] = {
    // r0c0r1c1r2
    // r b, c bb
    0b1011111, // 0
    0b0000101, // 1
    0b1110110, // 2
    0b1110101, // 3
    0b0101101, // 4
    0b1111001, // 5
    0b1111011, // 6
    0b1000101, // 7
    0b1111111, // 8
    0b1111101, // 9
};

LCD::Digit::Digit(int s)
{
    for (int j = 1; j >= 0; --j)
    {
        bool b1 = s % 2;
        s /= 2;
        bool b2 = s % 2;
        s /= 2;
        cs[j].second = b1;
        cs[j].first = b2;
    }
    for (int j = 2; j >= 0; --j)
    {
        bool b = s % 2;
        s /= 2;
        rs[j] = b;
    }
}

int main()
{
    int s, n;

    LCD lcd;
    while (cin >> s >> n && s != 0)
        lcd.display(n, s);
}