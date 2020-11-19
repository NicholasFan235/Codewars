#ifndef data
#define data
#include "DataStructures.h"
#endif


std::vector<std::pair<int, int>> GetNeighbours(std::pair<int, int>);
bool GeneratePath(std::pair<int, int> start, std::pair<int, int> target, std::vector<std::pair<int, int>> &path);
std::vector<int> ConvertToInstructions(std::vector<std::pair<int, int>>);



std::vector<int> ConvertToInstructions(std::vector<std::pair<int, int>> path){
    std::vector<int> ret;
    for (const auto p : path){
        ret.push_back(board[p.first][p.second]);
    }
    return ret;
}

bool GeneratePath(std::pair<int, int> start, std::pair<int, int> target, std::vector<std::pair<int, int>> &path){
    //printf("(%d, %d) -> (%d, %d)\n", start.second, start.first, target.second, target.first);
    if (locked[target.first][target.second]) return false;
    if (start == target) return true;

    locked[target.first][target.second] = 1;

    auto neighbours = GetNeighbours(target);
    for (int i = 0; i < neighbours.size(); i++){
        if (GeneratePath(start, neighbours[i], path)){
            path.push_back(target);
            locked[target.first][target.second] = 0;
            return true;
        }
    }

    locked[target.first][target.second] = 0;

    return false;
}



std::vector<std::pair<int, int>> GetNeighbours(std::pair<int, int> p){
    std::vector<std::pair<int, int>> ret;
    int x = p.second; int y = p.first;
    if (y > 0) ret.push_back(std::make_pair(y-1, x));
    if (x > 0) ret.push_back(std::make_pair(y, x-1));
    if (y < N-1) ret.push_back(std::make_pair(y+1, x));
    if (x < M-1) ret.push_back(std::make_pair(y, x+1));
    return ret;
}




