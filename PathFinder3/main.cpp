#include "solution.h"

int main()
{
    std::stringstream m;
    std::string s;
    std::cin >> s;
    int N = s.length();
    m << s;
    for (int i = 1; i < N; i++)
    {
        std::string si;
        std::cin >> si;
        m << '\n' << si;
    }
    std::cout << path_finder(m.str()) << std::endl;
}

