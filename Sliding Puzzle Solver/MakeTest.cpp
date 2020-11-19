#include <bits/stdc++.h>

int main(){
    int N;
    std::cin >> N;
    
    std::vector<int> board(N*N);
    for (int i = 0; i < N*N; i++){
        board[i] = i;
    }
    std::random_shuffle(board.begin(), board.end());

    std::cout << N << " " << N << std::endl;
    for (int i = 0; i < N; i++){
        if (i>0) std::cout << std::endl;
        for (int j = 0; j < N; j++){
            if (j > 0) std::cout << " ";
            std::cout << board[i*N+j];
        }
    }
}