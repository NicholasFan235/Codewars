
#include <bits/stdc++.h>

namespace nQueens
{
    int N;

    std::set<int> freeCols;
    std::set<int> freeRows;
    std::set<int> usedDiag1;
    std::set<int> usedDiag2;

    std::vector<std::vector<bool>> queenPositions;

    std::pair<int, int> diagCoords(int col, int row)
    {
        return std::make_pair(col-row, col+row);
    }
    std::pair<int, int> diagCoords(std::pair<int, int>& p) { return diagCoords(p.first, p.second); }

    bool diagPossible(std::pair<int, int>& diags)
    {
        if (usedDiag1.find(diags.first) != usedDiag1.end()) return false;
        if (usedDiag2.find(diags.second) != usedDiag2.end()) return false;
        return true;
    }

    void placeQueen(int col, int row, std::pair<int, int> diags)
    {
        queenPositions[col][row] = true;
        freeCols.erase(col);
        freeRows.erase(row);
        usedDiag1.insert(diags.first);
        usedDiag2.insert(diags.second);
    }
    void placeQueen(std::pair<int, int> pos) { placeQueen(pos.first, pos.second, diagCoords(pos)); }

    void removeQueen(int col, int row, std::pair<int, int> diags)
    {
        queenPositions[col][row] = false;
        freeCols.insert(col);
        freeRows.insert(row);
        usedDiag1.erase(diags.first);
        usedDiag2.erase(diags.second);
    }

    bool recurse(int remainingQueens)
    {
        if (remainingQueens == 0) return true;
        // Try all possible positions
        // If positions not possible return false
        std::set<int> checkCols = freeCols;
        std::set<int> checkRows = freeRows;

        for (const int col : checkCols)
        {
            for (const int row : checkRows)
            {
                std::pair<int, int> diags = diagCoords(col, row);
                if (diagPossible(diags))
                {
                    placeQueen(col, row, diags);

                    bool possible = recurse(remainingQueens-1);
                    if (possible) return true;

                    removeQueen(col, row, diags);
                }
            }
        }
        return false;
    }

    void reset(int n)
    {
        queenPositions = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));

        freeCols = std::set<int>();
        freeRows = std::set<int>();
        usedDiag1 = std::set<int>();
        usedDiag2 = std::set<int>();
        for (int i = 0; i < n; i++)
        {
            freeCols.insert(i);
            freeRows.insert(i);
        }
    }

    std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoords)
    {
        std::cout << "Solving " << n << "x" << n << " board with mandatory position: (" << mandatoryQueenCoords.first << ", " << mandatoryQueenCoords.second << ")" << std::endl;
        reset(n);
        placeQueen(mandatoryQueenCoords);

        bool possible = recurse(n-1);

        if (!possible) return "";

        std::stringstream board;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                board << (queenPositions[i][j] ? "Q" : ".");
            }
            board << "\n";
        }

        return board.str();
    }

}


