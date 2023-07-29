#include "Vector2.h"
#include <bits/stdc++.h>

int main(){
    geo::Vector2 a(1, 2);
    geo::Vector2 b(3, 4);
    
    auto c = a + b;
    auto d = a*2;
    auto e = 2*a;

    d = a+2;
    e = 2+a;

    std::cout << (a!=b) << std::endl << (a==a) << std::endl;

}