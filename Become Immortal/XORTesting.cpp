#include <bits/stdc++.h>


int main(){
    int N, M;
    std::cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            int ij = i^j;
            std::cout << ij << '\t';
        }
        std::cout << std::endl;
    }
}