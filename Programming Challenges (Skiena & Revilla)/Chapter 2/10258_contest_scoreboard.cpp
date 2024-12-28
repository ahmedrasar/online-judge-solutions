#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

#define TEAMS 100
#define PROBLEMS 9
#define CORRECT 'C'
#define INCORRECT 'I'
#define PENALTYTIME 20

struct Team
{
    bool inContest;
    int number, solved, penalty;
    Team() : inContest(false), number(0), solved(0), penalty(0) {}
};

bool operator<(const Team &rs, const Team &ls)
{
    if (rs.inContest && !ls.inContest)
        return false;
    else if (!rs.inContest && ls.inContest)
        return true;

    if (rs.solved != ls.solved)
        return rs.solved < ls.solved;
    else if (rs.penalty != ls.penalty)
        return rs.penalty > ls.penalty;
    else
        return rs.number > ls.number;
}

int main()
{
    int caseN;
    scanf("%d\n\n", &caseN);

    while (caseN--)
    {
        int incorrectAttempts[TEAMS][PROBLEMS];
        bool isSolved[TEAMS][PROBLEMS];
        memset(incorrectAttempts, 0, sizeof(incorrectAttempts));
        memset(isSolved, false, sizeof(isSolved));
        vector<Team> scoreboard(TEAMS);

        string line;
        while (getline(cin, line) && !line.empty())
        {
            istringstream iss(line);
            int team, prob, time;
            char state;
            iss >> team >> prob >> time >> state;
            --team, --prob;

            if (isSolved[team][prob])
                continue;
            if (!scoreboard[team].inContest)
            {
                scoreboard[team].inContest = true;
                scoreboard[team].number = team + 1;
            }

            if (state == INCORRECT)
                ++incorrectAttempts[team][prob];
            else if (state == CORRECT)
            {
                isSolved[team][prob] = true;
                ++scoreboard[team].solved;
                scoreboard[team].penalty += (time + incorrectAttempts[team][prob] * PENALTYTIME);
            }
        }

        sort(scoreboard.begin(), scoreboard.end(), [](const Team &rs, const Team &ls)
             { return ls < rs; });
        for (const Team &t : scoreboard)
        {
            if (!t.inContest)
                break;
            cout << t.number << ' ' << t.solved << ' ' << t.penalty << '\n';
        }
        if (caseN)
            cout << '\n';
    }
}