#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(nlg(n))
*/

#define TEAMS 100
#define PROBLEMS 9
#define CORRECT 'C'
#define INCORRECT 'I'
#define PENALTYTIME 20

struct Team
{
    bool in_contest;
    int number, solved, penalty;
    Team() : in_contest(false), number(0), solved(0), penalty(0) {}
};

bool operator<(const Team &rs, const Team &ls)
{
    if (rs.in_contest && !ls.in_contest)
        return false;
    else if (!rs.in_contest && ls.in_contest)
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
    int N;
    scanf("%d\n\n", &N);

    while (N--)
    {
        int incorrect_attempts[TEAMS][PROBLEMS];
        bool is_solved[TEAMS][PROBLEMS];
        memset(incorrect_attempts, 0, sizeof(incorrect_attempts));
        memset(is_solved, false, sizeof(is_solved));
        vector<Team> scoreboard(TEAMS);

        string line;
        while (getline(cin, line) && !line.empty())
        {
            istringstream iss(line);
            int team, prob, time;
            char state;
            iss >> team >> prob >> time >> state;
            --team, --prob;

            if (is_solved[team][prob])
                continue;
            if (!scoreboard[team].in_contest)
            {
                scoreboard[team].in_contest = true;
                scoreboard[team].number = team + 1;
            }

            if (state == INCORRECT)
                ++incorrect_attempts[team][prob];
            else if (state == CORRECT)
            {
                is_solved[team][prob] = true;
                ++scoreboard[team].solved;
                scoreboard[team].penalty += (time + incorrect_attempts[team][prob] * PENALTYTIME);
            }
        }

        sort(scoreboard.begin(), scoreboard.end(), [](const Team &rs, const Team &ls)
             { return ls < rs; });
        for (const Team &t : scoreboard)
        {
            if (!t.in_contest)
                break;
            cout << t.number << ' ' << t.solved << ' ' << t.penalty << '\n';
        }
        if (N)
            cout << '\n';
    }
}