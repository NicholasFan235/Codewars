#include <bits/stdc++.h>

std::stringstream iss;

int main(){
    for (int i = 1; i < 2000; i++){
        iss << i;
    }
    std::string s = iss.str();
    int n;
    std::cin >> n;
    std::cout << s.substr(n-1, 10) << std::endl;
}