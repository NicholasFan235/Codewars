#ifndef data
#define data
#include "DataStructures.h"
#endif


void PrintArray2(std::vector<std::vector<int>> &arr){
    for (const auto r : arr){
        for (const auto p : r){
            printf("%d\t", p);
        }
        std::cout << std::endl;
    }
}

void PrintBoard(){
    PrintArray2(board);
}

void PrintLocked(){
    PrintArray2(locked);
}