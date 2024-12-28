#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define CARDSNUM 52
#define SUITSIZE 13

string cardName(const int card)
{
    string suit;
    const int _suit = card / SUITSIZE; // cards per suit
    switch (_suit)
    {
    case 0:
        suit = "Clubs";
        break;
    case 1:
        suit = "Diamonds";
        break;
    case 2:
        suit = "Hearts";
        break;
    case 3:
        suit = "Spades";
        break;
    }

    string value;
    const int _value = card % SUITSIZE;
    switch (_value)
    {
    case 8:
        value = "10";
        break;
    case 9:
        value = "Jack";
        break;
    case 10:
        value = "Queen";
        break;
    case 11:
        value = "King";
        break;
    case 12:
        value = "Ace";
        break;
    default:
        value += _value + '2';
    }

    return value + " of " + suit;
}

vector<int> shuffleDeck(const vector<int> deck, const vector<int> shuffle)
{
    vector<int> ndeck(CARDSNUM);
    ndeck.resize(CARDSNUM);
    for (int j = 0; j < CARDSNUM; ++j)
        ndeck[j] = deck[shuffle[j]];
    return ndeck;
}

int main()
{
    int caseN;
    cin >> caseN;
    while (caseN--)
    {
        int n;
        cin >> n;

        vector<int> shuffle[n];
        for (auto &shf : shuffle)
            shf.resize(CARDSNUM);

        for (auto &shf : shuffle)
        {
            for (auto &card : shf)
            {
                cin >> card;
                --card;
            }
        }
        cin.get(); // consumes the last '\n'

        auto deck = vector<int>(CARDSNUM);
        for (int i = 0; i < CARDSNUM; ++i)
            deck[i] = i;

        string _line;
        while (getline(cin, _line) && !_line.empty())
        {
            istringstream iss(_line);
            int id;
            iss >> id;
            --id;
            deck = shuffleDeck(deck, shuffle[id]);
        }

        for (const int card : deck)
            cout << cardName(card) << '\n';
        if (caseN)
            cout << '\n';
    }
}