#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(2^n)
*/

#define DICES 5
#define SIDES 6
#define CATEGORIES 13
#define ROUNDS 13
#define BCATS 6
#define BTHRESHHOLD 63
#define BPOINTS 35
#define FKPOINTS 50 // Five of a Kind
#define STPOINTS 25 // Short Straight
#define LSPOINTS 35 // Long Straight
#define FHPOINTS 40 // Full House

int DP[1 << ROUNDS][BTHRESHHOLD + 1];       // DP[s][b] = max score of set s with bonus sum b
int DP_CR[1 << ROUNDS][BTHRESHHOLD + 1];    // DP_CR[s][b] = chosen round at DP[s][b] (cat can be deduced from s)
int DP_BS[1 << ROUNDS][BTHRESHHOLD + 1];    // DP_BS[s][b] = bs, and DP[s][bs] is the max sum of set s
bool DP_DONE[1 << ROUNDS][BTHRESHHOLD + 1]; // DP_DONE[s][b] = is DP[s][b] calculated before

int sum_of(const vector<int> &round, const int target)
{
    int s = 0;
    for (const int dice : round)
    {
        if (dice == target)
            s += target;
    }
    return s;
}

int chance(const vector<int> &round)
{
    int s = 0;
    for (const int dice : round)
        s += dice;

    return s;
}

int of_akind(const vector<int> &round, const int nkind)
{
    int side_in_round[SIDES];
    for (auto &n : side_in_round)
        n = 0;

    int s = 0;
    for (int dice : round)
        ++side_in_round[dice - 1], s += dice;

    s = (nkind == 5 ? FKPOINTS : s);

    for (const int n : side_in_round)
        if (n >= nkind)
            return s;

    return 0;
}

int straight(const vector<int> &round, const int straight)
{
    bool side_in_round[SIDES];
    for (auto &side : side_in_round)
        side = false;

    for (const int dice : round)
        side_in_round[dice - 1] = true;

    int points = 0;
    switch (straight)
    {
    case 4:
        points = STPOINTS;
        break;
    case 5:
        points = LSPOINTS;
        break;
    }

    int thrust = 0;
    for (int i = 0; i < SIDES - straight || side_in_round[i]; ++i)
    {
        thrust = (side_in_round[i] ? thrust + 1 : 0);
        if (thrust == straight)
            return points;
    }
    return 0;
}

int fullH(const vector<int> &round)
{
    int side_in_round[SIDES];
    for (auto &n : side_in_round)
        n = 0;

    for (const int dice : round)
        ++side_in_round[dice - 1];

    for (const int n : side_in_round)
        if (n != 2 && n != 3 && n != 0)
            return 0;

    return FHPOINTS;
}

int _find_highest(const vector<vector<int>> &table, const int cur_set, const int index, const int bsum)
{
    int max_score = -1;
    int b_state_of_max = 0; // For bonus sum

    if (index >= BCATS && DP_DONE[cur_set][0])
        return 0; // No bouns sum
    else if (DP_DONE[cur_set][min(bsum, BTHRESHHOLD)])
        return DP_BS[cur_set][min(bsum, BTHRESHHOLD)];

    for (int i = 0; i < ROUNDS; ++i)
    {
        if (((1 << i) & cur_set) == 0) // If round not in set
            continue;
        const int ex_set = cur_set ^ (1 << i);

        int nb_sum = bsum;
        if (index < BCATS)
            nb_sum += table[i][index];

        int bstate = _find_highest(table, ex_set, index + 1, nb_sum);
        int score = DP[ex_set][min(bstate, BTHRESHHOLD)];
        score += table[i][index];

        const int pb_state = bstate;
        if (index < BCATS)
            bstate = bstate + table[i][index];
        if (pb_state < BTHRESHHOLD)
            score += (bstate >= BTHRESHHOLD ? BPOINTS : 0);

        if (DP[cur_set][min(bstate, BTHRESHHOLD)] < score)
        {
            DP[cur_set][min(bstate, BTHRESHHOLD)] = score;
            DP_CR[cur_set][min(bstate, BTHRESHHOLD)] = i;
        }

        if (index < BCATS)
        {
            int nscore = score;
            if (bstate < BTHRESHHOLD)
                nscore += ((bsum + bstate) >= BTHRESHHOLD ? BPOINTS : 0);

            if (max_score < nscore)
            {
                max_score = nscore;
                b_state_of_max = bstate;
            }
        }
    }

    DP_DONE[cur_set][index < BCATS ? min(bsum, BTHRESHHOLD) : 0] = true;
    return b_state_of_max;
}

vector<int> find_highest(const vector<vector<int>> &table)
{
    memset(DP, -1, sizeof(DP));
    memset(DP_DONE, false, sizeof(DP_DONE));
    DP[0][0] = 0;
    DP_DONE[0][0] = true;

    const int fullSet = (1 << ROUNDS) - 1;
    const int bState = _find_highest(table, fullSet, 0, 0);
    const int maxScore = DP[fullSet][min(bState, BTHRESHHOLD)];

    vector<int> sheet(CATEGORIES + 2);
    int bonus = bState;
    int set = fullSet;
    for (int cat = 0; cat < CATEGORIES; ++cat)
    {
        int r = DP_CR[set][min(bonus, BTHRESHHOLD)];
        sheet[cat] = table[r][cat];
        bonus -= (cat < BCATS ? sheet[cat] : 0);
        set = set ^ (1 << r);
    }
    sheet[CATEGORIES] = (bState >= BTHRESHHOLD ? BPOINTS : 0);
    sheet[CATEGORIES + 1] = maxScore;

    return sheet;
}

void compute_round(vector<vector<int>> &table, const vector<int> round, const int i)
{
    // Round i, Cat j

    int j = 0;
    table[i][j++] = sum_of(round, 1);
    table[i][j++] = sum_of(round, 2);
    table[i][j++] = sum_of(round, 3);
    table[i][j++] = sum_of(round, 4);
    table[i][j++] = sum_of(round, 5);
    table[i][j++] = sum_of(round, 6);
    table[i][j++] = chance(round);
    table[i][j++] = of_akind(round, 3);
    table[i][j++] = of_akind(round, 4);
    table[i][j++] = of_akind(round, 5);
    table[i][j++] = straight(round, 4); // Short Staight
    table[i][j++] = straight(round, 5); // Long Straight
    table[i][j++] = fullH(round);
}

int main()
{

    while (true)
    {
        vector<vector<int>> rounds(ROUNDS, vector<int>(DICES));
        for (int i = 0; i < ROUNDS; ++i)
        {
            for (int j = 0; j < DICES; ++j)
                if (!(cin >> rounds[i][j]))
                    break;
        }
        if (!cin)
            break;

        vector<vector<int>> table(ROUNDS, vector<int>(CATEGORIES));
        for (int i = 0; i < ROUNDS; ++i)
            compute_round(table, rounds[i], i);

        vector<int> highestRow = find_highest(table);
        for (int i = 0; i < highestRow.size() - 1; ++i)
            cout << highestRow[i] << ' ';
        cout << highestRow[highestRow.size() - 1] << '\n';
    }
}