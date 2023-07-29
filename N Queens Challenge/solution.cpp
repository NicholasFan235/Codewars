#include "solution.h"




int main()
{

    int n, x, y;
    std::cin >> n >> x >> y;

    std::string board = nQueens::solveNQueens(n, std::make_pair(x, y));
    std::cout << board << std::endl;
}
