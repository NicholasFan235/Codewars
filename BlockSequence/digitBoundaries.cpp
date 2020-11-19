#include <bits/stdc++.h>


int main(){
    unsigned long long ans = 0;
    for (int i = 1; i <= 9; i++){
        ans += i;
    }
    std::cout << ans << std::endl;
    
    for (int i = 10; i <= 99; i++){
        ans += 9 + 2*(i-9);
    }
    std::cout << ans << std::endl;

    for (int i = 100; i <= 999; i++){
        ans += 189 + 3*(i-99);
    }
    std::cout << ans << std::endl;

    for (int i = 1000; i <= 9999; i++){
        ans += 2889 + 4*(i-999);
    }
    std::cout << ans << std::endl;

    for (int i = 10000; i <= 99999; i++){
        ans += 38889 + 5*(i-9999);
    }
    std::cout << ans << std::endl;

    for (int i = 100000; i <= 999999; i++){
        ans += 488889 + 6*(i-99999);
    }
    std::cout << ans << std::endl;

    for (int i = 1000000; i <= 9999999; i++){
        ans += 5888889 + 7*(i-999999);
    }
    std::cout << ans << std::endl;

    for (int i = 10000000; i <= 99999999; i++){
        ans += 68888889 + 8*(i-9999999);
    }
    std::cout << ans << std::endl;

    for (int i = 100000000; i <= 999999999; i++){
        ans += 788888889 + 9*(i-99999999);
    }
    std::cout << ans << std::endl;
}