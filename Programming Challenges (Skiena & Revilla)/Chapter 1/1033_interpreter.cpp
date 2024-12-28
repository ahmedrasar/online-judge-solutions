#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

int reg[10];
int ram[1000];

int exe()
{
    int pc = 0;
    int steps = 0;
    while (true)
    {
    PC:
        ++steps;
        int w = ram[pc]; // w = op d s
        int s = w % 10;
        w /= 10;
        int d = w % 10;
        w /= 10;
        int op = w % 10;
        switch (op)
        {
            int t;
        case 0:
            if (reg[s])
            {
                pc = reg[d];
                goto PC;
            }
            break;
        case 1:
            return steps;
        case 2:
            reg[d] = s;
            break;
        case 3:
            t = reg[d] + s;
            reg[d] = t % 1000;
            break;
        case 4:
            t = reg[d] * s;
            reg[d] = t % 1000;
            break;
        case 5:
            reg[d] = reg[s];
            break;
        case 6:
            t = reg[d] + reg[s];
            reg[d] = t % 1000;
            break;
        case 7:
            t = reg[d] * reg[s];
            reg[d] = t % 1000;
            break;
        case 8:
            reg[d] = ram[reg[s]];
            break;
        case 9:
            ram[reg[s]] = reg[d];
            break;
        }

        ++pc;
    }
}

int main()
{

    int caseN;
    cin >> caseN >> ws;
    while (caseN--)
    {
        for (auto &r : reg)
            r = 0;

        int n = 0;
        char c;
        while (cin.get(c) && c != '\n')
        {
            cin.unget();
            cin >> ram[n++];
            cin.get(c); // reads the '\n' at the end
        }

        cout << exe() << '\n';
        if (caseN)
            cout << '\n';
    }
}