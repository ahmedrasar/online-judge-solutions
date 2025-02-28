#include <iostream>
#include <fstream>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-2-24

    Time Complexity: O(n)
*/

#define LINELIMIT 72

void trim_front(string &line);
void trim_back(string &line);

enum Tokens
{
    none,
    word,
    big_word,
    space,
    line_break,
};

struct Token
{
    Tokens type;
    string value;
    Token(Tokens type, string value = "") : type(type), value(value) {}
};

Token read_token(istream &in)
{

    const char ch = in.get();
    if (!in)
        return Token(none);

    if (ch == '\n')
    {
        if (!isspace(in.peek()))
            return Token{space, " "};
        else if (in.peek() == ' ')
            return Token{line_break, "\n"};
        else
        {
            string value = "\n";
            while (in.get() == '\n')
                value += '\n';
            in.unget();
            return Token{line_break, value};
        }
    }
    else if (ch == ' ')
    {
        string spaces = " ";
        while (in.get() == ' ')
            spaces += ' ';
        in.unget();
        return Token{space, spaces};
    }
    else
    {
        in.unget();
        string value;
        in >> value;
        return Token{value.length() >= LINELIMIT ? big_word : word, value};
    }
}

int main()
{
    string line, fmt;
    for (Token t = read_token(cin); t.type != none; t = read_token(cin))
    {
        if (t.type == big_word)
        {
            trim_back(line);
            if (!line.empty())
                fmt += line + '\n';
            read_token(cin);
            line.clear();
            fmt += t.value + '\n';
        }
        else if (t.type == line_break)
        {
            trim_back(line);
            fmt += line + t.value;
            line.clear();
        }
        else
        {
            line += t.value;
            if (line.length() > LINELIMIT)
            {

                const int break_pos = line.find_last_of(' ', LINELIMIT);
                string fmt_line = line.substr(0, break_pos + 1);
                trim_back(fmt_line);
                fmt += fmt_line + '\n';
                line = line.substr(break_pos + 1);
                trim_front(line);
            }
        }
    }
    trim_back(line);
    fmt += line;
    if (fmt.back() != '\n')
        fmt += '\n';
    cout << fmt;

    return 0;
}

void trim_back(string &line)
{
    if (line.empty())
        return;
    while (line.back() == ' ')
        line.pop_back();
}

void trim_front(string &line)
{
    if (line.empty())
        return;
    int i = 0;
    while (line[i] == ' ')
        ++i;
    line = line.substr(i);
    return;
}
