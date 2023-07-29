#include <bits/stdc++.h>


namespace nQueens
{
    const int MAX_ITER = 500;
    const int NUM_RETRIES = 10;

    std::vector<int> cols;
    std::vector<int> rows;
    std::vector<int> dia1;
    std::vector<int> dia2;

    int N;
    int collisions;
    std::pair<int, int> mandatory;

    std::vector<std::vector<bool>> queens;
    std::set<std::pair<int, int>> queenPositions;
    
    std::string makeBoard()
    {
        std::stringstream board;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                board << (queens[i][j] ? "Q" : ".");
            }
            board << "\n";
        }
        return board.str();
    }
    
    std::pair<int, int> diag(int col, int row)
    {
        return std::make_pair(col+row, col-row+N);
    }

    void placeQueen(int col, int row)
    {
        if (queens[row][col] == true) printf("Queen already exists in position (%d, %d)\n", col, row);
        queens[row][col] = true;
        if (cols[col]++ > 0) collisions++;
        if (rows[row]++ > 0) collisions++;
        std::pair<int, int> dCoords = diag(col, row);
        if (dia1[dCoords.first]++ > 0) collisions++;
        if (dia2[dCoords.second]++ > 0) collisions++;
        queenPositions.insert(std::make_pair(col, row));
    }

    void removeQueen(int col, int row)
    {
        if (queens[row][col] == false) printf("No queen exists in position (%d, %d)\n", col, row);
        queens[row][col] = false;
        if(--cols[col] > 0) collisions--;
        if(--rows[row] > 0) collisions--;
        std::pair<int, int> dCoords = diag(col, row);
        if(--dia1[dCoords.first] > 0) collisions--;
        if(--dia2[dCoords.second] > 0) collisions--;
        queenPositions.erase(std::make_pair(col, row));
    }

    void swapQueens(int c1, int r1, int c2, int r2)
    {
        removeQueen(c1, r1);
        placeQueen(c2, r2);
    }

    int evalQueen(int col, int row)
    {
        std::pair<int, int> dCoords = diag(col, row);
        return (cols[col]-1) + (rows[row]-1) + (dia1[dCoords.first]-1) + (dia2[dCoords.second]-1);
    }
    int evalQueen(std::pair<int, int> pos) { return evalQueen(pos.first, pos.second); }

    int evalPosition()
    {
        return collisions;
    }

    std::pair<int, int> getMostConflicting()
    {
        std::set<std::pair<int, int>> worstPos = {};
        int worstCs = 0;
        for (const std::pair<int, int> pos : queenPositions)
        {
            if (pos == mandatory) continue;
            int c = evalQueen(pos);
            if (c > worstCs)
            {
                worstPos = {pos};
                worstCs = c;
            }
            else if (c == worstCs)
            {
                worstPos.insert(pos);
            }
        }
        auto it = worstPos.begin();
        std::advance(it, std::rand()%worstPos.size());
        return *it;
    }

    void iterSingle()
    {
        std::pair<int, int> worst = getMostConflicting();
        
        std::set<int> bestRow = {worst.second};
        int bestCs = collisions;

        int currPos = worst.second;
        for (int i = 0; i < N; i++)
        {
            swapQueens(worst.first, currPos, worst.first, i);
            currPos = i;

            if (collisions < bestCs)
            {
                bestRow = {i};
                bestCs = collisions;
            }
            else if (collisions == bestCs)
            {
                bestRow.insert(i);
            }
        }
        //std::cout << bestPos.size() << " equally good positions to move queen to" << std::endl;
        auto it = bestRow.begin();
        std::advance(it, rand()%bestRow.size());
        swapQueens(worst.first, currPos, worst.first, *it);
        //std::cout << "Moved queen on row " << worst.first << " from " << originalPos << "->" << *it << std::endl;
    }

    void placeRandomQueens()
    {
        placeQueen(mandatory.first, mandatory.second);
        std::vector<int> possibleJs = std::vector<int>(N-1);
        for (int j = 0; j < N-1; j++)
        {
            possibleJs[j] = j + (j >= mandatory.second ? 1 : 0);
        }
        std::random_shuffle(possibleJs.begin(), possibleJs.end());
        for (int i = 0; i < N; i++)
        {
            if (i==mandatory.first) continue;
            placeQueen(i, possibleJs.back());
            possibleJs.pop_back();
        }
    }

    void initialize()
    {
        collisions = 0;
        queens = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));
        cols = std::vector<int>(N, 0);
        rows = std::vector<int>(N, 0);
        dia1 = std::vector<int>(2*N, 0);
        dia2 = std::vector<int>(2*N, 0);
        queenPositions.clear();
        placeRandomQueens();
        //std::cout << "Initial: " << std::endl << makeBoard() << std::endl;
    }

    bool performIterativeRepair()
    {
        initialize();
        for (int i = 0; i < MAX_ITER; i++)
        {
            iterSingle();
            if (collisions == 0)
            {
                return true;
            }
        }
        return collisions == 0;
    }

    std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoords)
    {
        std::cout << "Solving " << n << "x" << n << " board with mandatory position: (" << mandatoryQueenCoords.first << ", " << mandatoryQueenCoords.second << ")" << std::endl;

        if (n==1) return "Q\n";
        if (n==2 || n==3) return "";

        N = n;
        mandatory = mandatoryQueenCoords;

        for (int tryNum = 0; tryNum < NUM_RETRIES; tryNum++)
        {
            bool success = performIterativeRepair();
            if (success)
            {
                std::cout << "Solved on try #" << tryNum << std::endl;
                return makeBoard();
            }
            std::cout << "Failed try #" << tryNum << " with " << collisions << " collisions." << std::endl;
        }
        return "";
    }

}