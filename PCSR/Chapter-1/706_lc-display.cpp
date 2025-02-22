#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

class LCD
{
public:
    static constexpr char EMPTYFILL = ' ';
    static constexpr char HFILL = '-'; // Horizantal fill
    static constexpr char VFILL = '|'; // Vertical fill
    static constexpr char SPACE = ' ';
    void display(const int n, const int s)
    {
        digit_size = s;
        lcd_buffer = to_string(n);
        print_buffer();
    };

private:
    using r_type = bool;
    using c_type = pair<bool, bool>;

    struct Digit
    {
        /*
            R0
        C00     C01
            R1
        C10     C11
            R2
        */
        static const Digit digits[10];
        static const Digit &from_char(const char c) { return digits[c - '0']; }

        r_type rs[3];
        c_type cs[2];

    private:
        Digit(const int s);
    };

    void print_buffer()
    {
        /*
        The command line prints line by line, hence the horizontal line of the whole number must be printed before getting to the next one.
        Print the row/column of all numbers at once then go the the next row/column.
        */

        cout << row_as_string(0);
        cout << column_as_string(0);
        cout << row_as_string(1);
        cout << column_as_string(1);
        cout << row_as_string(2);
        cout << '\n';
    }

    int digit_size;
    string lcd_buffer;

    string get_column(const int column_index)
    {
        string line;
        for (int j = 0; j < lcd_buffer.size(); ++j)
        {
            if (Digit::from_char(lcd_buffer[j]).cs[column_index].first)
                line += VFILL;
            else
                line += EMPTYFILL;
            for (int i = 0; i < digit_size; i++)
                line += EMPTYFILL;
            if (Digit::from_char(lcd_buffer[j]).cs[column_index].second)
                line += VFILL;
            else
                line += EMPTYFILL;
            if (j != lcd_buffer.size() - 1)
                line += SPACE;
        }

        line += '\n';
        return line;
    }

    string row_as_string(const int row_index)
    {
        string row;
        for (int j = 0; j < lcd_buffer.size(); ++j)
        {
            row += EMPTYFILL;
            char ch = Digit::from_char(lcd_buffer[j]).rs[row_index] ? HFILL : EMPTYFILL;
            string str(digit_size, ch);
            row += str;
            row += EMPTYFILL;

            if (j != lcd_buffer.size() - 1)
                row += SPACE;
        }

        row += '\n';
        return row;
    }

    string column_as_string(const int column_index)
    {
        string single_line = get_column(column_index);
        string column;
        for (int i = 0; i < digit_size; ++i)
            column += single_line;

        return column;
    }
};

const LCD::Digit LCD::Digit::digits[10] = {
    // R0R1R2C0C1C2C3
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