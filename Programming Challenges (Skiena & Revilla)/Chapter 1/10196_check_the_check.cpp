#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

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
    bool inRange() const { return (x >= 0 && y >= 0 && x <= GRIDSIDE - 1 && y <= GRIDSIDE - 1); }
    char getPiece() const { return grid[y][x]; }
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
    Checkmate(const Index &kingIndex) : k(kingIndex),
                                        isBlack(kingIndex.getPiece() == BKCHAR) {}
    bool isCheck()
    {
        if (isCheckedByQueen() ||
            isCheckedByKnight() ||
            isCheckedByBishop() ||
            isCheckedByPawn() ||
            isCheckedByRock() ||
            isCheckedByKnight())
            return true;
        return false;
    }

private:
    bool isCheckedBy(const Index &index, const char target) const
    {
        if (index.inRange() && index.getPiece() == target)
            return true;
        return false;
    }

    bool isCheckedByPawn() const
    {
        const int y = k.y + (isBlack ? BPAWNSTEP : WPAWNSTEP);

        if (isCheckedBy(Index(k.x + 1, y), PAWN_TARGET) ||
            isCheckedBy(Index(k.x - 1, y), PAWN_TARGET))
            return true;
        return false;
    }
    bool isCheckedByKnight() const
    {

        if (isCheckedBy(Index(k.x - 1, k.y - 2), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x + 1, k.y - 2), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x - 2, k.y - 1), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x + 2, k.y - 1), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x - 2, k.y + 1), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x + 2, k.y + 1), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x - 1, k.y + 2), KNIGHT_TARGET) ||
            isCheckedBy(Index(k.x + 1, k.y + 2), KNIGHT_TARGET))
            return true;
        return false;
    }

    bool isCheckedByRegularMove(const char target, const int xs, const int ys) const
    {
        auto index = Index(k.x + xs, k.y + ys);

        while (index.inRange())
        {
            if (isCheckedBy(index, target))
                return true;
            else if (index.getPiece() == EMPTYCHAR)
                index.x += xs, index.y += ys;
            else
                return false;
        }
        return false;
    }

    bool isCheckedByRock(const bool isQueenFlag = false) const
    {
        const char target = isQueenFlag ? QUEEN_TARGET : ROCK_TARGET;
        if (isCheckedByRegularMove(target, 0, 1) ||
            isCheckedByRegularMove(target, 1, 0) ||
            isCheckedByRegularMove(target, 0, -1) ||
            isCheckedByRegularMove(target, -1, 0))
            return true;

        return false;
    }

    bool isCheckedByBishop(const bool isQueenFlag = false) const
    {
        const char target = isQueenFlag ? QUEEN_TARGET : BISHOP_TARGET;
        if (isCheckedByRegularMove(target, 1, 1) ||
            (isCheckedByRegularMove(target, -1, -1)) ||
            (isCheckedByRegularMove(target, -1, 1)) ||
            (isCheckedByRegularMove(target, 1, -1)))
            return true;

        return false;
    }

    bool isCheckedByKing(const bool isQueenFlag = false) const
    {
        const char target = isQueenFlag ? QUEEN_TARGET : kING_TARGET;
        for (int x = k.x - 1; x <= k.x + 1; ++x)
        {
            for (int y = k.y - 1; y <= k.y + 1; ++y)
            {
                if (isCheckedBy(Index(x, y), target))
                    return true;
            }
        }
        return false;
    }

    bool isCheckedByQueen() const
    {
        if (isCheckedByKing(true) ||
            isCheckedByBishop(true) ||
            isCheckedByRock(true))
            return true;
        return false;
    }
};

int main()
{
    int gameN = 1;
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

        if (!pieces) // empty board
            return 0;
        Checkmate checkmateWK(white_K), checkmateBK(black_K);
        if (checkmateWK.isCheck())
            cout << "Game #" << gameN << ": white king is in check." << endl;
        else if (checkmateBK.isCheck())
            cout << "Game #" << gameN << ": black king is in check." << endl;
        else
            cout << "Game #" << gameN << ": no king is in check." << endl;
        ++gameN;
    }
    cout << '\n';
}