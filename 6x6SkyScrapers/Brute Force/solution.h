#include <bits/stdc++.h>

namespace sln
{

std::vector<int> clues;
std::vector<std::vector<int>> board;
std::array<std::array<std::set<int>,6>,2> used;

void printBoard()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int numSeen(int i)
{
    int seen = 0;
    int max = 0;
    for (int j = 0; j < 6; j++)
    {
        int curr;
        if (i%12 < 6)
        {
            // vertical
            if (i < 6)
            {
                curr = board[j][i];
            }
            else
            {
                curr = board[5-j][17-i];
            }
        }
        else
        {
            // horiz
            if (i < 12)
            {
                curr = board[i-6][5-j];
            }
            else
            {
                curr = board[23-i][j];
            }
        }
        if (curr > max)
        {
            max = curr; seen++;
        }
    }

    return seen;
}

int numSpaces(int i)
{
    int spaces = 0;
    for (int j = 0; j < 6; j++)
    {
        if (i%12 < 6)
        {
            // vertical
            if (i < 6) {
                if (board[j][i] == 0) spaces++;
            }
            else {
                if (board[5-j][17-i] == 0) spaces++;
            }
        }
        else
        {
            // horizontal
            if (i < 12) {
                if (board[i-6][5-j] == 0) spaces++;
            }
            else {
                if (board[23-i][j] == 0) spaces++;
            }
        }
    }
    return spaces;
}

bool isPossible()
{
    for (int i = 0; i < 24; i++)
    {
        if (clues[i] != 0)
        {
            int spaces = numSpaces(i);
            if (spaces == 0)
            {
                if (numSeen(i) != clues[i])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool canFillCell(int cell, int i)
{
    if (used[0][cell%6].find(i) != used[0][cell%6].end()) return false;
    if (used[1][cell/6].find(i) != used[1][cell/6].end()) return false;
    return true;
}

void fillCell(int cell, int i)
{
    board[cell%6][cell/6] = i;
    used[0][cell%6].insert(i);
    used[1][cell/6].insert(i);
}

void removeCell(int cell)
{
    int i = board[cell%6][cell/6];
    if (i==0) return;
    board[cell%6][cell/6] = 0;
    used[0][cell%6].erase(i);
    used[1][cell/6].erase(i);
}

bool tryFillCell(int cell)
{
    if (cell == 36) return true;
    for (int i = 1; i <= 6; i++)
    {
        if (canFillCell(cell, i))
        {
            removeCell(cell);
            fillCell(cell, i);
            if (!isPossible())
            {
                removeCell(cell);
                continue;
            }
            if (tryFillCell(cell+1))
            {
                return true;
            }
        }
    }
    removeCell(cell);
    return false;
}

}

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &c)
{
    sln::clues = c;
    sln::board = std::vector<std::vector<int>>(6, std::vector<int>(6));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            sln::used[i][j].clear();
        }
    }
    bool canSolve = sln::tryFillCell(0);
    std::cout << (canSolve ? "success" : "failed") << std::endl;
    sln::printBoard();
    return sln::board;
}

