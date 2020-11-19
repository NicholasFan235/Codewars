#include <bits/stdc++.h>


std::vector<std::pair<int, int>> updatePossible(std::array<int, 6> row, int c1, int c2){
    // returns vector of not possible (position, value)
    std::vector<std::pair<int, int>> impossibles;
    // 6 has to be at least clue away from edge
    for (int i = 0; i < c1-1; i++){
        impossibles.push_back(std::make_pair(i, 6));
    }
    for (int i = 5; i > 6-c2; i--){
        impossibles.push_back(std::make_pair(i, 6));
    }
    // triangular fill (if c == 3, 1st can't be 456, 2nd can't be 56) (ignore 6 since already done)
    for (int i = 5; i >= 8-c1; i--){
        for (int j = 0; j <= i+c1-8; j++){
            impossibles.push_back(std::make_pair(j, i));
        }
    }
    for (int i = 5; i >= c2-3; i--){
        for (int j = 5; j >= 13-c2-i; j--){
            impossibles.push_back(std::make_pair(j, i));
        }
    }
    return impossibles;
}

void printPossibles(std::vector<std::set<int>> &possibles){
    for (int i = 1; i <= 6; i++){
        for (int j = 0; j < 6; j++){
            if (possibles[j].count(i)){
                printf("%d ", i);
            }
            else{
                printf("  ");
            }
        }
        std::cout << std::endl;
    }
}

int main(){
    std::vector<std::set<int>> possibles(6, {1, 2, 3, 4, 5, 6});
    
    std::vector<std::pair<int, int>> impossibles = updatePossible({1, 2, 3, 4, 5, 6}, 1, 2);

    for (const auto imp : impossibles){
        //std::cout << imp.first << ", " << imp.second << std::endl;
        possibles[imp.first].erase(imp.second);
    }

    printPossibles(possibles);
}

