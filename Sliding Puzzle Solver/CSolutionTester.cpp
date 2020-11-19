#include "CodeWarsSolution.h"

int main(){
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> board(N, std::vector<int>(M));

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            std::cin >> board[i][j];
        }
    }

    auto tic = std::chrono::system_clock::now();
    auto result = slide_puzzle(board);
    auto toc = std::chrono::system_clock::now();

    printf("Solved in %luu\nSolution length %lu\n",
        std::chrono::duration_cast<std::chrono::microseconds>(toc-tic).count(),
        result.size());
}