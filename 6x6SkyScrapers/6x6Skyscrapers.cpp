#include <bits/stdc++.h>


std::vector<std::vector<int>> map;
std::array<std::array<std::set<int>, 6>, 6> possibles;
std::map<std::pair<int, int>, std::vector<std::set<int>>> impTable({
{{1, 1}, {{ 1, 2, 3, 4, 5, 6, }, { 1, 2, 3, 4, 5, 6, }, { 1, 2, 3, 4, 5, 6, }, { 1, 2, 3, 4, 5, 6, }, { 1, 2, 3, 4, 5, 6, }, { 1, 2, 3, 4, 5, 6, }, }},
{{1, 2}, {{ 1, 2, 3, 4, 5, }, { 5, 6, }, { 5, 6, }, { 5, 6, }, { 5, 6, }, { 1, 2, 3, 4, 6, }, }},
{{1, 3}, {{ 1, 2, 3, 4, 5, }, { 6, }, { 6, }, { 6, }, { 4, 6, }, { 5, 6, }, }},
{{1, 4}, {{ 1, 2, 3, 4, 5, }, { 6, }, { 6, }, { 6, }, { 5, 6, }, { 4, 5, 6, }, }},
{{1, 5}, {{ 1, 2, 3, 4, 5, }, { 6, }, { 6, }, { 5, 6, }, { 4, 5, 6, }, { 3, 4, 5, 6, }, }},
{{1, 6}, {{ 1, 2, 3, 4, 5, }, { 1, 2, 3, 4, 6, }, { 1, 2, 3, 5, 6, }, { 1, 2, 4, 5, 6, }, { 1, 3, 4, 5, 6, }, { 2, 3, 4, 5, 6, }, }},
{{2, 1}, {{ 1, 2, 3, 4, 6, }, { 5, 6, }, { 5, 6, }, { 5, 6, }, { 5, 6, }, { 1, 2, 3, 4, 5, }, }},
{{2, 2}, {{ 6, }, { 5, }, { 5, }, { 5, }, { 5, }, { 6, }, }},
{{2, 3}, {{ 6, }, { 5, }, { }, { }, { 6, }, { 5, 6, }, }},
{{2, 4}, {{ 6, }, { 5, }, { }, { 6, }, { 5, 6, }, { 4, 5, 6, }, }},
{{2, 5}, {{ 6, }, { 1, 2, 3, 4, 5, }, { 1, 2, 3, 6, }, { 1, 2, 5, 6, }, { 1, 4, 5, 6, }, { 3, 4, 5, 6, }, }},
{{3, 1}, {{ 5, 6, }, { 4, 6, }, { 6, }, { 6, }, { 6, }, { 1, 2, 3, 4, 5, }, }},
{{3, 2}, {{ 5, 6, }, { 6, }, { }, { }, { 5, }, { 6, }, }},
{{3, 3}, {{ 5, 6, }, { 6, }, { }, { }, { 6, }, { 5, 6, }, }},
{{3, 4}, {{ 5, 6, }, { 1, 6, }, { 1, 2, 3, 4, 5, }, { 1, 2, 6, }, { 1, 5, 6, }, { 4, 5, 6, }, }},
{{4, 1}, {{ 4, 5, 6, }, { 5, 6, }, { 6, }, { 6, }, { 6, }, { 1, 2, 3, 4, 5, }, }},
{{4, 2}, {{ 4, 5, 6, }, { 5, 6, }, { 6, }, { }, { 5, }, { 6, }, }},
{{4, 3}, {{ 4, 5, 6, }, { 1, 5, 6, }, { 1, 2, 6, }, { 1, 2, 3, 4, 5, }, { 1, 6, }, { 5, 6, }, }},
{{5, 1}, {{ 3, 4, 5, 6, }, { 4, 5, 6, }, { 5, 6, }, { 6, }, { 6, }, { 1, 2, 3, 4, 5, }, }},
{{5, 2}, {{ 3, 4, 5, 6, }, { 1, 4, 5, 6, }, { 1, 2, 5, 6, }, { 1, 2, 3, 6, }, { 1, 2, 3, 4, 5, }, { 6, }, }},
{{6, 1}, {{ 2, 3, 4, 5, 6, }, { 1, 3, 4, 5, 6, }, { 1, 2, 4, 5, 6, }, { 1, 2, 3, 5, 6, }, { 1, 2, 3, 4, 6, }, { 1, 2, 3, 4, 5, }, }},
});
std::vector<int> clues;
std::queue<std::pair<int, int>> checkQueue;

void reset(){
    std::vector<int> r(6);
    map = std::vector<std::vector<int>>(6, r);
    std::array<std::set<int>, 6> row;
    row.fill({1, 2, 3, 4, 5, 6});
    possibles.fill(row);
}

void removePossible(int i, int j, int value){
    if (possibles[i][j].count(value)){
        possibles[i][j].erase(value);
        if (possibles[i][j].size() == 1){
            checkQueue.push(std::make_pair(i, j));
        }
    }
}

void fillMapValue(int i, int j, int value){
    map[i][j] = value;
    for (int k = 0; k < 6; k++){
        removePossible(k, j, value);
        removePossible(i, k, value);
    }
}

void impossiblesPass1(){
    // for each row
    for (int i = 0; i < 6; i++){
        int c1 = clues[23-i], c2 = clues[6+i];
        std::pair<int, int> key = std::make_pair(c1, c2);
        for (int j = 0; j < 6; j++){
            for (const int imp : impTable[key][j]){
                removePossible(i, j, imp);
            }
        }
    }

    // for each column
    for (int i = 0; i < 6; i++){
        int c1 = clues[i], c2 = clues[17-i];
        std::pair<int, int> key = std::make_pair(c1, c2);
        for (int j = 0; j < 6; j++){
            for (const int imp : impTable[key][j]){
                removePossible(j, i, imp);
            }
        }
    }
}

void lastResortPass(){
    // for each row
    for (int i = 0; i < 6; i++){
        // for each number
        for (int n = 1; n <= 6; n++){
            int possiblePosition = 6;
            for (int j = 0; j < 6; j++){
                if (possibles[i][j].count(n)){
                    if (possiblePosition == 6) possiblePosition = j;
                    else { possiblePosition = 6; break; }
                }
            }
            if (possiblePosition != 6){
                printf("Filling (%d, %d) with %d\n", i, possiblePosition, n);
                fillMapValue(i, possiblePosition, n);
            }
        }
    }
    // for each column
    for (int j = 0; j < 6; j++){
        // for each number
        for (int n = 1; n <= 6; n++){
            int possiblePosition = 6;
            for (int i = 0; i < 6; i++){
                if (possibles[i][j].count(n)){
                    if (possiblePosition == 6) possiblePosition = i;
                    else { possiblePosition = 6; break; }
                }
            }
            if (possiblePosition != 6){
                printf("Filling (%d, %d) with %d\n", possiblePosition, j, n);
                fillMapValue(possiblePosition, j, n);
            }
        }
    }
}

void processQueue(){
    while (!checkQueue.empty()){
        std::pair<int, int> key = checkQueue.front();
        checkQueue.pop();
        fillMapValue(key.first, key.second, *possibles[key.first][key.second].begin());
    }
}

void printPossibles(){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            std::cout << possibles[i][j].size() << " ";
        }
        printf("\n");
    }
}

void printPossiblesDetailed(){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            for (const int p : possibles[i][j]){
                printf("%d ", p);
            }
            printf("\n");
        }
    }
}

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &_c){
    reset();
    clues = _c;
    impossiblesPass1();
    processQueue();
    lastResortPass();
    processQueue();
    lastResortPass();
    return map;
}

std::vector<std::vector<int>> queries = {
  { 3, 2, 2, 3, 2, 1,
    1, 2, 3, 3, 2, 2,
    5, 1, 2, 2, 4, 3,
    3, 2, 1, 2, 2, 4 },
  { 0, 0, 0, 2, 2, 0,
    0, 0, 0, 6, 3, 0,
    0, 4, 0, 0, 0, 0,
    4, 4, 0, 3, 0, 0 },
  { 0, 3, 0, 5, 3, 4, 
    0, 0, 0, 0, 0, 1,
    0, 3, 0, 3, 2, 3,
    3, 2, 0, 3, 1, 0}  
};

int main(){
    std::vector<std::vector<int>> answer = SolvePuzzle(queries[0]);

    for (const auto r : answer){
        for (const int val : r){
            printf("%d ", val);
        }
        printf("\n");
    }
}


