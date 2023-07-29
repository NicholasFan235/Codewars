#include "magicCompare.h"
#include <iostream>

int main()
{
    using MagicInt = MagicCompare<int>;
    using MagicFloat = MagicCompare<float>;

    MagicInt a = 3;
    MagicInt b = 4;

    std::cout << a+b << std::endl;

}