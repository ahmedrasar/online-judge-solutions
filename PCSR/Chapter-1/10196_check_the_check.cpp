#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(1)
*/

#define GRIDSIDE 8
#define BKCHAR 'k'
#define WKCHAR 'K'
#define EMPTYCHAR '.'
#define BLACKTOP true

auto grid = vector<vector<char>>(GRIDSIDE, vector<char>(GRIDSIDE));

struct Index
{
    int x, y;
    Index(const int x, const int y) : x(x), y(y) {}
    bool in_range() const { return (x >= 0 && y >= 0 && x <= GRIDSIDE - 1 && y <= GRIDSIDE - 1); }
    char get_piece() const { return grid[y][x]; }
};

class Checkmate
{
    const Index k;
    const bool isBlack;
    const char PAWN_TARGET = isBlack ? 'P' : 'p';
    const char KNIGHT_TARGET = isBlack ? 'N' : 'n';
    const char BISHOP_TARGET = isBlack ? 'B' : 'b';
    const char ROCK_TARGET = isBlack ? 'R' : 'r';
    const char QUEEN_TARGET = isBlack ? 'Q' : 'q';
    const char kING_TARGET = isBlack ? 'K' : 'k';
    static constexpr int BPAWNSTEP = BLACKTOP ? +1 : -1;
    static constexpr int WPAWNSTEP = BLACKTOP ? -1 : +1;

public:
    Checkmate(const Index &king_index) : k(king_index),
                                         isBlack(king_index.get_piece() == BKCHAR) {}
    bool is_checked()
    {
        if (is_checked_by_queen() ||
            is_checked_by_knight() ||
            is_checked_by_bishop() ||
            is_checked_by_pawn() ||
            is_checked_by_rock() ||
            is_checked_by_knight())
            return true;
        return false;
    }

private:
    bool is_checked_at(const Index &index, const char target) const
    {
        if (index.in_range() && index.get_piece() == target)
            return true;
        return false;
    }

    bool is_checked_by_pawn() const
    {
        const int y = k.y + (isBlack ? BPAWNSTEP : WPAWNSTEP);

        if (is_checked_at(Index(k.x + 1, y), PAWN_TARGET) ||
            is_checked_at(Index(k.x - 1, y), PAWN_TARGET))
            return true;
        return false;
    }
    bool is_checked_by_knight() const
    {

        if (is_checked_at(Index(k.x - 1, k.y - 2), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x + 1, k.y - 2), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x - 2, k.y - 1), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x + 2, k.y - 1), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x - 2, k.y + 1), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x + 2, k.y + 1), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x - 1, k.y + 2), KNIGHT_TARGET) ||
            is_checked_at(Index(k.x + 1, k.y + 2), KNIGHT_TARGET))
            return true;
        return false;
    }

    bool isCheckedByRegularMove(const char target, const int xs, const int ys) const
    {
        auto index = Index(k.x + xs, k.y + ys);

        while (index.in_range())
        {
            if (is_checked_at(index, target))
                return true;
            else if (index.get_piece() == EMPTYCHAR)
                index.x += xs, index.y += ys;
            else
                return false;
        }
        return false;
    }

    bool is_checked_by_rock(const bool is_queen = false) const
    {
        const char target = is_queen ? QUEEN_TARGET : ROCK_TARGET;
        if (isCheckedByRegularMove(target, 0, 1) ||
            isCheckedByRegularMove(target, 1, 0) ||
            isCheckedByRegularMove(target, 0, -1) ||
            isCheckedByRegularMove(target, -1, 0))
            return true;

        return false;
    }

    bool is_checked_by_bishop(const bool is_queen = false) const
    {
        const char target = is_queen ? QUEEN_TARGET : BISHOP_TARGET;
        if (isCheckedByRegularMove(target, 1, 1) ||
            (isCheckedByRegularMove(target, -1, -1)) ||
            (isCheckedByRegularMove(target, -1, 1)) ||
            (isCheckedByRegularMove(target, 1, -1)))
            return true;

        return false;
    }

    bool isCheckedByKing(const bool is_queen = false) const
    {
        const char target = is_queen ? QUEEN_TARGET : kING_TARGET;
        for (int x = k.x - 1; x <= k.x + 1; ++x)
        {
            for (int y = k.y - 1; y <= k.y + 1; ++y)
            {
                if (is_checked_at(Index(x, y), target))
                    return true;
            }
        }
        return false;
    }

    bool is_checked_by_queen() const
    {
        if (isCheckedByKing(true) ||
            is_checked_by_bishop(true) ||
            is_checked_by_rock(true))
            return true;
        return false;
    }
};

int main()
{
    int game_number = 1;
    const auto NULL_INDEX = Index(GRIDSIDE, GRIDSIDE);
    while (true)
    {
        Index black_K = NULL_INDEX, white_K = NULL_INDEX;
        int pieces = 0;
        char c;
        for (int i = 0; i < GRIDSIDE; ++i)
        {
            for (int j = 0; j < GRIDSIDE; ++j)
            {
                cin >> c;
                if (c == BKCHAR)
                    black_K.y = i, black_K.x = j;
                else if (c == WKCHAR)
                    white_K.y = i, white_K.x = j;

                if (c != EMPTYCHAR)
                    ++pieces;
                grid[i][j] = c;
            }
        }

        if (!pieces) // Empty board
            return 0;
        Checkmate checkmateWK(white_K), checkmateBK(black_K);
        if (checkmateWK.is_checked())
            cout << "Game #" << game_number << ": white king is in check." << endl;
        else if (checkmateBK.is_checked())
            cout << "Game #" << game_number << ": black king is in check." << endl;
        else
            cout << "Game #" << game_number << ": no king is in check." << endl;
        ++game_number;
    }
    cout << '\n';
}