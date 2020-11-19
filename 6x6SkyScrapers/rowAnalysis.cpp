#include <bits/stdc++.h>

int c1 = 2, c2 = 2;

std::array<std::set<int>, 6> possibles;

bool checkRow(const std::array<int, 6> &row){
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

void printRow(const std::array<int, 6> &row){
    for (int i = 0; i < row.size(); i++){
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
}

void printPossibles(){
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

void addToPossibles(const std::array<int, 6> &row){
    for (int i = 0; i < row.size(); i++){
        possibles[i].insert(row[i]);
    }
}

void permute(std::array<int, 6> &row, int l, int r){
    if (l==r){
        if (checkRow(row)){
            addToPossibles(row);
            //printRow(row);
        }
    }
    else{
        for (int i = l; i <= r; i++){
            std::swap(row[l], row[i]);
            permute(row, l+1, r);
            std::swap(row[l], row[i]);
        }
    }
}

int main(){
    std::array<int, 6> row = {1, 2, 3, 4, 5, 6};
    possibles.fill({});

    /*
    for (int i = 1; i < 7; i++){
        c2 = i;
        permute(row, 0, row.size()-1);
    }*/
    permute(row, 0, row.size()-1);

    printPossibles();
}


