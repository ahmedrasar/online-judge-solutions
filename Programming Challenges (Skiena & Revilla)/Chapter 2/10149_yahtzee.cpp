#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

#define DICES 5
#define SIDES 6
#define CATEGORIES 13 // every category needs to be implemented in computeRound
#define ROUNDS 13
#define BCATS 6
#define BTHRESHHOLD 63
#define BPOINTS 35
#define FKPOINTS 50 // five of a kind
#define STPOINTS 25 // short straight
#define LSPOINTS 35 // long straight
#define FHPOINTS 40 // full house

int DP[1 << ROUNDS][BTHRESHHOLD + 1];       // DP[s][b] = max score of set s with bonus sum b
int DP_CR[1 << ROUNDS][BTHRESHHOLD + 1];    // DP_CR[s][b] = chosen round at DP[s][b] (cat can be deduced from s)
int DP_BS[1 << ROUNDS][BTHRESHHOLD + 1];    // DP_BS[s][b] = bs, and DP[s][bs] is the max sum of set s
bool DP_DONE[1 << ROUNDS][BTHRESHHOLD + 1]; // DP_DONE[s][b] = is DP[s][b] calculated before

int sumOf(const vector<int> &round, const int target)
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

int ofAkind(const vector<int> &round, const int nkind)
{
    int sideInRound[SIDES];
    for (auto &n : sideInRound)
        n = 0;

    int s = 0;
    for (int dice : round)
        ++sideInRound[dice - 1], s += dice;

    s = (nkind == 5 ? FKPOINTS : s);

    for (const int n : sideInRound)
        if (n >= nkind)
            return s;

    return 0;
}

int straight(const vector<int> &round, const int straight)
{
    bool sideInRound[SIDES];
    for (auto &side : sideInRound)
        side = false;

    for (const int dice : round)
        sideInRound[dice - 1] = true;

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
    for (int i = 0; i < SIDES - straight || sideInRound[i]; ++i)
    {
        thrust = (sideInRound[i] ? thrust + 1 : 0);
        if (thrust == straight)
            return points;
    }
    return 0;
}

int fullH(const vector<int> &round)
{
    int sideInRound[SIDES];
    for (auto &n : sideInRound)
        n = 0;

    for (const int dice : round)
        ++sideInRound[dice - 1];

    for (const int n : sideInRound)
        if (n != 2 && n != 3 && n != 0)
            return 0;

    return FHPOINTS;
}

int _findHighest(const vector<vector<int>> &table, const int curSet, const int catIndex, const int bSum)
{
    // dynamic programming with bitmasking
    int maxScore = -1;
    int bStateOfMax = 0; // for bonus sum

    if (catIndex >= BCATS && DP_DONE[curSet][0])
        return 0; // no bouns sum
    else if (DP_DONE[curSet][min(bSum, BTHRESHHOLD)])
        return DP_BS[curSet][min(bSum, BTHRESHHOLD)];

    for (int i = 0; i < ROUNDS; ++i)
    {
        if (((1 << i) & curSet) == 0) // if round not in set
            continue;
        const int exSet = curSet ^ (1 << i);

        int nBSum = bSum;
        if (catIndex < BCATS)
            nBSum += table[i][catIndex];

        int bState = _findHighest(table, exSet, catIndex + 1, nBSum);
        int score = DP[exSet][min(bState, BTHRESHHOLD)];
        score += table[i][catIndex];

        const int pbState = bState;
        if (catIndex < BCATS)
            bState = bState + table[i][catIndex];
        if (pbState < BTHRESHHOLD)
            score += (bState >= BTHRESHHOLD ? BPOINTS : 0);

        if (DP[curSet][min(bState, BTHRESHHOLD)] < score)
        {
            DP[curSet][min(bState, BTHRESHHOLD)] = score;
            DP_CR[curSet][min(bState, BTHRESHHOLD)] = i;
        }

        if (catIndex < BCATS)
        {
            int nScore = score;
            if (bState < BTHRESHHOLD)
                nScore += ((bSum + bState) >= BTHRESHHOLD ? BPOINTS : 0);

            if (maxScore < nScore)
            {
                maxScore = nScore;
                bStateOfMax = bState;
            }
        }
    }

    DP_DONE[curSet][catIndex < BCATS ? min(bSum, BTHRESHHOLD) : 0] = true;
    return bStateOfMax;
}

vector<int> findHighest(const vector<vector<int>> &table)
{
    memset(DP, -1, sizeof(DP));
    memset(DP_DONE, false, sizeof(DP_DONE));
    DP[0][0] = 0;
    DP_DONE[0][0] = true;

    const int fullSet = (1 << ROUNDS) - 1;
    const int bState = _findHighest(table, fullSet, 0, 0);
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

void computeRound(vector<vector<int>> &table, const vector<int> round, const int i)
{
    // round i, cat j

    int j = 0;
    table[i][j++] = sumOf(round, 1);
    table[i][j++] = sumOf(round, 2);
    table[i][j++] = sumOf(round, 3);
    table[i][j++] = sumOf(round, 4);
    table[i][j++] = sumOf(round, 5);
    table[i][j++] = sumOf(round, 6);
    table[i][j++] = chance(round);
    table[i][j++] = ofAkind(round, 3);
    table[i][j++] = ofAkind(round, 4);
    table[i][j++] = ofAkind(round, 5);
    table[i][j++] = straight(round, 4); // short straing
    table[i][j++] = straight(round, 5); // long straight
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
            computeRound(table, rounds[i], i);

        vector<int> highestRow = findHighest(table);
        for (int i = 0; i < highestRow.size() - 1; ++i)
            cout << highestRow[i] << ' ';
        cout << highestRow[highestRow.size() - 1] << '\n';
    }
}