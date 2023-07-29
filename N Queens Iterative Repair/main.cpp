#include "solution.h"


int main()
{
    
    int N, x, y;
    std::cin >> N >> x >> y;

    std::string board = nQueens::solveNQueens(N, std::make_pair(x, y));
    std::cout << board << std::endl;
}
