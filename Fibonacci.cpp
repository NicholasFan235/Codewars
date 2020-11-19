#include <bits/stdc++.h>


int main(){
    
    long long int c = 1;
    long long int p = 1;

    while (c < LONG_LONG_MAX/2){
        long long int n = c+p;
        p = c;
        c = n;
        std::cout << n << std::endl;
    }
}