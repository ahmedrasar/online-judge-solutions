#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(1)
*/

#define HSIZE 5
#define MAXVAL 12
#define NULLRANK ""
using card_t = pair<char, char>;
using hand_t = vector<card_t>;
using rank_t = string;

char get_char_Code(const char c)
{
    switch (c)
    {
    case 'T':
        return 'I';
    case 'J':
        return 'J';
    case 'Q':
        return 'K';
    case 'K':
        return 'L';
    case 'A':
        return 'M';
    default: // 2:9 -> A:H
        return c - '2' + 'A';
    }
}

rank_t hcard(const hand_t &h)
{
    // Code: 0 + c1..c5

    rank_t rank;
    rank.resize(1 + HSIZE);
    rank[0] = '0';

    for (int i = 0; i < HSIZE; ++i)
        rank[i + 1] = h[i].first;

    return rank;
}

rank_t pairc(const hand_t &h)
{
    // Code: 1 + p + c1..c3

    rank_t rank;
    rank.resize(1 + HSIZE - 1);
    rank[0] = '1';

    char pVal = 0;
    char _prev = h[0].first;
    for (int i = 1; i < HSIZE; ++i)
    {
        if (h[i].first == _prev)
        {
            pVal = h[i].first;
            break;
        }
        _prev = h[i].first;
    }
    if (!pVal)
        return NULLRANK;

    rank[1] = pVal;
    int i = 2;
    for (const auto &c : h)
    {
        if (c.first != pVal)
            rank[i++] = c.first;
    }

    return rank;
}

rank_t two_pairc(const hand_t &h)
{
    // Code: 2 + p1 + p2 + c1

    rank_t rank;
    rank.resize(1 + HSIZE - 2);
    rank[0] = '2';

    if ((h[1].first != h[0].first && h[1].first != h[2].first) ||
        (h[3].first != h[2].first && h[3].first != h[4].first))
        return NULLRANK;

    rank[1] = h[1].first;
    rank[2] = h[3].first;
    for (const auto &c : h)
    {
        if (c.first != h[1].first && c.first != h[3].first)
        {
            rank[3] = c.first;
            break;
        }
    }
    return rank;
}

rank_t three_ok(const hand_t &h)
{
    // Code: 3 + s

    rank_t rank;
    rank.resize(2);
    rank[0] = '3';

    if (h[0].first != h[2].first && h[1].first != h[3].first && h[2].first != h[4].first)
        return NULLRANK;

    rank[1] = h[2].first;
    return rank;
}

rank_t straight(const hand_t &h)
{
    // Code: 4 + s

    rank_t rank;
    rank.resize(2);
    rank[0] = '4';

    for (int i = 1; i < HSIZE; ++i)
    {
        if (h[i - 1].first - h[i].first != 1)
            return NULLRANK;
    }

    rank[1] = h[0].first;
    return rank;
}

rank_t flush(const hand_t &h)
{
    // Code: 5 + c1..c5

    rank_t rank;
    rank.resize(1 + HSIZE);

    const char skind = h[0].second;
    for (const auto &c : h)
    {
        if (c.second != skind)
            return NULLRANK;
    }

    rank = hcard(h);
    rank[0] = '5';
    return rank;
}

rank_t fhouse(const hand_t &h)
{
    // Code: 6 + s

    rank_t rank;
    rank.resize(2);
    rank[0] = '6';

    if (h[0].first != h[2].first && h[2].first != h[4].first)
        return NULLRANK;
    if ((h[0].first != h[1].first || h[0].first == h[2].first) &&
        (h[3].first != h[4].first || h[3].first == h[2].first))
        return NULLRANK;

    rank[1] = h[2].first;
    return rank;
}

rank_t four_ok(const hand_t &h)
{
    // Code: 8 + s

    rank_t rank;
    rank.resize(2);
    rank[0] = '8';

    if (h[0].first != h[3].first && h[1].first != h[4].first)
        return NULLRANK;
    rank[1] = h[1].first;
    return rank;
}

rank_t sflush(const hand_t &h)
{
    // Code: 9 + h

    rank_t rank;
    rank.resize(2);
    rank[0] = '9';

    const char skind = h[0].second;
    for (int i = 1; i < HSIZE; ++i)
    {
        if (h[i - 1].first - h[i].first != 1 || h[i].second != skind)
            return NULLRANK;
    }

    rank[1] = h[0].first;
    return rank;
}

rank_t get_rank_of_hand(const hand_t &h)
{
    rank_t rank;
    rank = sflush(h);
    if (!rank.empty())
        return rank;
    rank = four_ok(h);
    if (!rank.empty())
        return rank;
    rank = fhouse(h);
    if (!rank.empty())
        return rank;
    rank = flush(h);
    if (!rank.empty())
        return rank;
    rank = straight(h);
    if (!rank.empty())
        return rank;
    rank = three_ok(h);
    if (!rank.empty())
        return rank;
    rank = two_pairc(h);
    if (!rank.empty())
        return rank;
    rank = pairc(h);
    if (!rank.empty())
        return rank;
    return hcard(h);
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        istringstream lstream(line);
        hand_t hands[2];
        for (auto &h : hands)
        {
            h.resize(HSIZE);
            for (auto &c : h)
            {
                char v, k;
                lstream >> v >> k;
                c.first = get_char_Code(v);
                c.second = k;
            }
            sort(h.begin(), h.end(), [](const card_t &ls, const card_t &rs)
                 { return ls.first > rs.first; });
        }

        const auto brank = get_rank_of_hand(hands[0]);
        const auto wrank = get_rank_of_hand(hands[1]);

        if (brank == wrank)
            cout << "Tie.\n";
        else if (brank > wrank)
            cout << "Black wins.\n";
        else
            cout << "White wins.\n";
    }
}