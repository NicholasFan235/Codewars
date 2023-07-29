#include "solution.h"

int main()
{
    char start;
    int length;
    std::cin >> start >> length;
    std::cout << countPatternsFrom(start, length) << std::endl;
}

