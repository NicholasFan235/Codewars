#include <bits/stdc++.h>

bool checkRow(const std::array<int, 6> &row, int c1, int c2){
    int s1 = 0; int s2 = 0;
    int max1 = 0; int max2 = 0;
    for (int i = 0; i < row.size(); i++){
        if (row[i] > max1){
            s1++;
            max1 = row[i];
        }
        if (row[row.size()-1-i] > max2){
            s2++;
            max2 = row[row.size()-1-i];
        }
    }
    return c1==s1 && c2==s2;
}

void addToPossibles(const std::array<int, 6> &row, std::vector<std::set<int>> &possibles){
    for (int i = 0; i < row.size(); i++){
        possibles[i].insert(row[i]);
    }
}

void permute(std::array<int, 6> &row, std::vector<std::set<int>> &possibles, int l, int r, int c1, int c2){
    if (l==r){
        if (checkRow(row, c1, c2)){
            addToPossibles(row, possibles);
            //printRow(row);
        }
    }
    else{
        for (int i = l; i <= r; i++){
            std::swap(row[l], row[i]);
            permute(row, possibles, l+1, r, c1, c2);
            std::swap(row[l], row[i]);
        }
    }
}

void printPossibles(const std::vector<std::set<int>> &possibles){
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

void convPoss2Imposs(const std::vector<std::set<int>> &possibles, std::vector<std::set<int>> &impossibles){
    for (int i = 0; i < 6; i++){
        for (int j = 1; j <= 6; j++){
            if (!possibles[i].count(j)) impossibles[i].insert(j);
        }
    }
}

std::vector<std::set<int>> calcImpossibles(int c1, int c2){
    std::vector<std::set<int>> possibles(6, std::set<int>());
    std::array<int, 6> row = {1, 2, 3, 4, 5, 6};
    permute(row, possibles, 0, 5, c1, c2);
    
    std::vector<std::set<int>> impossibles(6, std::set<int>());
    convPoss2Imposs(possibles, impossibles);

    //printPossibles(impossibles);
    return impossibles;
}

void printVectorSet(const std::vector<std::set<int>> &vs){
    for (const auto p : vs){
        printf("{ ");
        for (const auto i : p){
            printf("%d, ", i);
        }
        printf("}, ");
    }
}

void printTable(const std::map<std::pair<int, int>, std::vector<std::set<int>>> table){
    printf("{\n");
    for (const auto p : table){
        printf("{{%d, %d}, {", p.first.first, p.first.second);
        printVectorSet(p.second);
        printf("}},\n");
    }
    printf("}\n");
}

int main(){
    std::map<std::pair<int, int>, std::vector<std::set<int>>> impTable;
    for (int c1 = 1; c1 <= 6; c1++){
        for (int c2 = 1; c2 <= 6; c2++){
            if (c1+c2 > 7) continue;
            std::pair<int, int> key = std::make_pair(c1, c2);
            impTable[key] = calcImpossibles(c1, c2);
        }
    }

    printTable(impTable);
}
