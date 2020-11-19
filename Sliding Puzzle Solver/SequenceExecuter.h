#ifndef data
#define data
#include "DataStructures.h"
#endif

bool isNeighbour(std::pair<int, int> &a, std::pair<int, int> &b);
void SlidePiece(std::pair<int, int> p);


bool isNeighbour(std::pair<int, int> &a, std::pair<int, int> &b){
    return ( abs(a.first-b.first) + abs(a.second-b.second) ) <= 1;
}

void InitializeBoard(std::vector<std::vector<int>> _b){
    board = _b;
    N = board.size();
    M = board[0].size();

    locked = std::vector<std::vector<int>>(N, std::vector<int>(M));
    pieceMap = std::vector<std::pair<int, int>>(N*M);
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            int piece = board[i][j];
            pieceMap[piece] = std::make_pair(i, j);
        }
    }
}

void ExecuteSequence(std::vector<std::pair<int, int>> sequence){
    for (auto p : sequence){
        SlidePiece(p);
    }
}

void ExecuteInstructions(std::vector<int> instructions){
    for (auto i : instructions){
        SlidePiece(pieceMap[i]);
    }
}

void SlidePiece(std::pair<int, int> p){
    if (!isNeighbour(p, pieceMap[0])) throw "Invalid slide attempt";
    
    int piece = board[p.first][p.second];
    board[pieceMap[0].first][pieceMap[0].second] = piece;
    board[p.first][p.second] = 0;

    pieceMap[piece] = pieceMap[0];
    pieceMap[0] = p;
}